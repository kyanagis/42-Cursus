#include "Account.hpp"

#include <climits>
#include <ctime>

#include <iostream>
#include <new>

namespace {

struct CloseInfo {
	int		amount;
	bool	is_recorded;
};

CloseInfo	*g_closed_infos = 0;
int			g_closed_infos_capacity = 0;

void display_timestamp(void) {
	std::time_t	now = std::time(0);
	std::tm		*tm_info = std::localtime(&now);
	char		buffer[20];

	if (tm_info != 0
		&& std::strftime(
			buffer,
			sizeof(buffer),
			"[%Y%m%d_%H%M%S] ",
			tm_info
		) != 0) {
		std::cout << buffer;
		return;
	}
	std::cout << "[00000000_000000] ";
}

bool can_add_int(int lhs, int rhs) {
	if (rhs > 0 && lhs > INT_MAX - rhs) {
		return false;
	}
	if (rhs < 0 && lhs < INT_MIN - rhs) {
		return false;
	}
	return true;
}

bool can_increment_int(int value) {
	return value < INT_MAX;
}

bool can_sub_int(int lhs, int rhs) {
	if (rhs > 0 && lhs < INT_MIN + rhs) {
		return false;
	}
	if (rhs < 0 && lhs > INT_MAX + rhs) {
		return false;
	}
	return true;
}

int get_initial_amount(int total_amount, int initial_deposit) {
	if (initial_deposit < 0 || !can_add_int(total_amount, initial_deposit)) {
		return 0;
	}
	return initial_deposit;
}

bool ensure_close_capacity(int account_index) {
	int			new_capacity;
	int			i;
	CloseInfo	*new_infos;

	if (account_index < 0) {
		return false;
	}
	if (account_index < g_closed_infos_capacity) {
		return true;
	}
	new_capacity = g_closed_infos_capacity;
	if (new_capacity == 0) {
		new_capacity = 8;
	}
	while (new_capacity <= account_index) {
		if (new_capacity > INT_MAX / 2) {
			if (account_index == INT_MAX) {
				return false;
			}
			new_capacity = account_index + 1;
			break;
		}
		new_capacity *= 2;
	}
	new_infos = new (std::nothrow) CloseInfo[new_capacity];
	if (new_infos == 0) {
		return false;
	}
	for (i = 0; i < new_capacity; ++i) {
		new_infos[i].amount = 0;
		new_infos[i].is_recorded = false;
	}
	for (i = 0; i < g_closed_infos_capacity; ++i) {
		new_infos[i] = g_closed_infos[i];
	}
	delete [] g_closed_infos;
	g_closed_infos = new_infos;
	g_closed_infos_capacity = new_capacity;
	return true;
}

void record_close(int account_index, int amount) {
	if (account_index < 0 || account_index >= g_closed_infos_capacity) {
		return;
	}
	g_closed_infos[account_index].amount = amount;
	g_closed_infos[account_index].is_recorded = true;
}

void flush_recorded_closes(void) {
	int	i;

	for (i = 0; i < g_closed_infos_capacity; ++i) {
		if (!g_closed_infos[i].is_recorded) {
			continue;
		}
		display_timestamp();
		std::cout << "index:" << i
			<< ";amount:" << g_closed_infos[i].amount
			<< ";closed\n";
		g_closed_infos[i].is_recorded = false;
	}
}

}

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

int Account::getNbAccounts(void) {
	return _nbAccounts;
}

int Account::getTotalAmount(void) {
	return _totalAmount;
}

int Account::getNbDeposits(void) {
	return _totalNbDeposits;
}

int Account::getNbWithdrawals(void) {
	return _totalNbWithdrawals;
}

void Account::_displayTimestamp(void) {
	display_timestamp();
}

void Account::displayAccountsInfos(void) {
	_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts
		<< ";total:" << _totalAmount
		<< ";deposits:" << _totalNbDeposits
		<< ";withdrawals:" << _totalNbWithdrawals
		<< '\n';
}

Account::Account(int initial_deposit)
	: _accountIndex(_nbAccounts),
		_amount(get_initial_amount(_totalAmount, initial_deposit)),
		_nbDeposits(0),
		_nbWithdrawals(0) {
	if (can_increment_int(_nbAccounts)) {
		++_nbAccounts;
	}
	if (!ensure_close_capacity(_accountIndex)) {
		// Close tracking unavailable; destruction order not guaranteed
	}
	_totalAmount += _amount;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
		<< ";amount:" << _amount
		<< ";created\n";
}

Account::~Account(void) {
	record_close(_accountIndex, _amount);
	if (_nbAccounts > 0) {
		--_nbAccounts;
	}
	if (can_sub_int(_totalAmount, _amount)) {
		_totalAmount -= _amount;
	}
	if (_nbAccounts == 0) {
		flush_recorded_closes();
		delete [] g_closed_infos;
		g_closed_infos = 0;
		g_closed_infos_capacity = 0;
	}
}

void Account::makeDeposit(int deposit) {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
		<< ";p_amount:" << _amount;
	if (deposit < 0
		|| !can_add_int(_amount, deposit)
		|| !can_add_int(_totalAmount, deposit)
		|| !can_increment_int(_nbDeposits)
		|| !can_increment_int(_totalNbDeposits)) {
		std::cout << ";deposit:refused\n";
		return;
	}
	_amount += deposit;
	++_nbDeposits;
	++_totalNbDeposits;
	_totalAmount += deposit;
	std::cout << ";deposit:" << deposit
		<< ";amount:" << _amount
		<< ";nb_deposits:" << _nbDeposits
		<< '\n';
}

bool Account::makeWithdrawal(int withdrawal) {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
		<< ";p_amount:" << _amount;
	if (withdrawal <= 0
		|| withdrawal > _amount
		|| !can_sub_int(_amount, withdrawal)
		|| !can_sub_int(_totalAmount, withdrawal)
		|| !can_increment_int(_nbWithdrawals)
		|| !can_increment_int(_totalNbWithdrawals)) {
		std::cout << ";withdrawal:refused\n";
		return false;
	}
	_amount -= withdrawal;
	++_nbWithdrawals;
	++_totalNbWithdrawals;
	_totalAmount -= withdrawal;
	std::cout << ";withdrawal:" << withdrawal
		<< ";amount:" << _amount
		<< ";nb_withdrawals:" << _nbWithdrawals
		<< '\n';
	return true;
}

int Account::checkAmount(void) const {
	return _amount;
}

void Account::displayStatus(void) const {
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
		<< ";amount:" << _amount
		<< ";deposits:" << _nbDeposits
		<< ";withdrawals:" << _nbWithdrawals
		<< '\n';
}

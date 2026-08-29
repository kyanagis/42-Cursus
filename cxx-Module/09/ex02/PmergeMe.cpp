#include "PmergeMe.hpp"

#include <cerrno>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <sys/time.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace {

typedef std::pair<int, int> IntPair;

// Compares two pairs by their first element only (the "winner" of a pair).
struct FirstLess {
	bool operator()(const IntPair& a, const IntPair& b) const {
		return a.first < b.first;
	}
};

double now_us() {
	timeval tv;
	gettimeofday(&tv, 0);
	return static_cast<double>(tv.tv_sec) * 1000000.0
		+ static_cast<double>(tv.tv_usec);
}

int parse_positive_int(const std::string& token) {
	if (token.empty()) {
		throw std::invalid_argument("empty token");
	}
	for (std::string::size_type i = 0; i < token.size(); ++i) {
		if (token[i] < '0' || token[i] > '9') {
			throw std::invalid_argument("not a positive integer");
		}
	}
	errno = 0;
	char* end = 0;
	long value = std::strtol(token.c_str(), &end, 10);
	if (*end != '\0' || errno == ERANGE || value > INT_MAX) {
		throw std::invalid_argument("integer out of range");
	}
	return static_cast<int>(value);
}

// Insertion order derived from the Jacobsthal numbers 1, 3, 5, 11, 21, ...
// Returns 0-based positions of the pending elements, grouped so that binary
// insertion stays within a power-of-two-sized window.
template <typename Seq>
Seq jacobsthal_order(std::size_t m) {
	Seq order;
	std::size_t prev_bound = 0;
	std::size_t t_prev = 1;
	std::size_t t_cur = 1;
	while (prev_bound < m) {
		std::size_t hi = t_cur;
		if (hi > m) {
			hi = m;
		}
		std::size_t q = hi;
		while (q > prev_bound) {
			order.push_back(q - 1);
			--q;
		}
		prev_bound = t_cur;
		std::size_t next = t_cur + 2 * t_prev;
		t_prev = t_cur;
		t_cur = next;
	}
	return order;
}

// ---- std::vector implementation -------------------------------------------

void insert_int_vec(std::vector<int>& chain, int value, int bound) {
	std::vector<int>::iterator hi =
		std::lower_bound(chain.begin(), chain.end(), bound);
	std::vector<int>::iterator pos = std::lower_bound(chain.begin(), hi, value);
	chain.insert(pos, value);
}

void insert_pair_vec(std::vector<IntPair>& chain, const IntPair& elem,
		int bound) {
	IntPair probe = std::make_pair(bound, 0);
	std::vector<IntPair>::iterator hi = std::lower_bound(
		chain.begin(), chain.end(), probe, FirstLess());
	std::vector<IntPair>::iterator pos =
		std::lower_bound(chain.begin(), hi, elem, FirstLess());
	chain.insert(pos, elem);
}

void sort_pairs_vec(std::vector<IntPair>& records) {
	std::size_t k = records.size();
	if (k < 2) {
		return;
	}
	std::vector<IntPair> winners;
	std::vector<IntPair> pend;
	std::vector<int> partner;
	bool odd = (k % 2 == 1);
	for (std::size_t i = 0; i + 1 < k; i += 2) {
		if (records[i].first > records[i + 1].first) {
			winners.push_back(records[i]);
			pend.push_back(records[i + 1]);
		} else {
			winners.push_back(records[i + 1]);
			pend.push_back(records[i]);
		}
		partner.push_back(winners.back().first);
	}
	sort_pairs_vec(winners);
	std::vector<std::size_t> order =
		jacobsthal_order<std::vector<std::size_t> >(pend.size());
	for (std::size_t o = 0; o < order.size(); ++o) {
		insert_pair_vec(winners, pend[order[o]], partner[order[o]]);
	}
	if (odd) {
		insert_pair_vec(winners, records[k - 1], records[k - 1].first);
	}
	records.swap(winners);
}

void sort_vector(std::vector<int>& v) {
	std::size_t n = v.size();
	if (n < 2) {
		return;
	}
	std::vector<IntPair> records;
	bool odd = (n % 2 == 1);
	for (std::size_t i = 0; i + 1 < n; i += 2) {
		if (v[i] > v[i + 1]) {
			records.push_back(std::make_pair(v[i], v[i + 1]));
		} else {
			records.push_back(std::make_pair(v[i + 1], v[i]));
		}
	}
	sort_pairs_vec(records);
	std::vector<int> chain;
	chain.reserve(n);
	chain.push_back(records[0].second);
	for (std::size_t i = 0; i < records.size(); ++i) {
		chain.push_back(records[i].first);
	}
	std::vector<std::size_t> order =
		jacobsthal_order<std::vector<std::size_t> >(records.size() - 1);
	for (std::size_t o = 0; o < order.size(); ++o) {
		std::size_t j = order[o] + 1;
		insert_int_vec(chain, records[j].second, records[j].first);
	}
	if (odd) {
		insert_int_vec(chain, v[n - 1], v[n - 1]);
	}
	v.swap(chain);
}

// ---- std::deque implementation --------------------------------------------

void insert_int_deq(std::deque<int>& chain, int value, int bound) {
	std::deque<int>::iterator hi =
		std::lower_bound(chain.begin(), chain.end(), bound);
	std::deque<int>::iterator pos = std::lower_bound(chain.begin(), hi, value);
	chain.insert(pos, value);
}

void insert_pair_deq(std::deque<IntPair>& chain, const IntPair& elem,
		int bound) {
	IntPair probe = std::make_pair(bound, 0);
	std::deque<IntPair>::iterator hi = std::lower_bound(
		chain.begin(), chain.end(), probe, FirstLess());
	std::deque<IntPair>::iterator pos =
		std::lower_bound(chain.begin(), hi, elem, FirstLess());
	chain.insert(pos, elem);
}

void sort_pairs_deq(std::deque<IntPair>& records) {
	std::size_t k = records.size();
	if (k < 2) {
		return;
	}
	std::deque<IntPair> winners;
	std::deque<IntPair> pend;
	std::deque<int> partner;
	bool odd = (k % 2 == 1);
	for (std::size_t i = 0; i + 1 < k; i += 2) {
		if (records[i].first > records[i + 1].first) {
			winners.push_back(records[i]);
			pend.push_back(records[i + 1]);
		} else {
			winners.push_back(records[i + 1]);
			pend.push_back(records[i]);
		}
		partner.push_back(winners.back().first);
	}
	sort_pairs_deq(winners);
	std::deque<std::size_t> order =
		jacobsthal_order<std::deque<std::size_t> >(pend.size());
	for (std::size_t o = 0; o < order.size(); ++o) {
		insert_pair_deq(winners, pend[order[o]], partner[order[o]]);
	}
	if (odd) {
		insert_pair_deq(winners, records[k - 1], records[k - 1].first);
	}
	records.swap(winners);
}

void sort_deque(std::deque<int>& d) {
	std::size_t n = d.size();
	if (n < 2) {
		return;
	}
	std::deque<IntPair> records;
	bool odd = (n % 2 == 1);
	for (std::size_t i = 0; i + 1 < n; i += 2) {
		if (d[i] > d[i + 1]) {
			records.push_back(std::make_pair(d[i], d[i + 1]));
		} else {
			records.push_back(std::make_pair(d[i + 1], d[i]));
		}
	}
	sort_pairs_deq(records);
	std::deque<int> chain;
	chain.push_back(records[0].second);
	for (std::size_t i = 0; i < records.size(); ++i) {
		chain.push_back(records[i].first);
	}
	std::deque<std::size_t> order =
		jacobsthal_order<std::deque<std::size_t> >(records.size() - 1);
	for (std::size_t o = 0; o < order.size(); ++o) {
		std::size_t j = order[o] + 1;
		insert_int_deq(chain, records[j].second, records[j].first);
	}
	if (odd) {
		insert_int_deq(chain, d[n - 1], d[n - 1]);
	}
	d.swap(chain);
}

}  // namespace

PmergeMe::PmergeMe() {
}

PmergeMe::PmergeMe(const PmergeMe& other) : vec_(other.vec_), deq_(other.deq_) {
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		vec_ = other.vec_;
		deq_ = other.deq_;
	}
	return *this;
}

PmergeMe::~PmergeMe() {
}

void PmergeMe::parse(int argc, char** argv) {
	for (int i = 1; i < argc; ++i) {
		std::istringstream stream(argv[i]);
		std::string token;
		while (stream >> token) {
			int value = parse_positive_int(token);
			vec_.push_back(value);
			deq_.push_back(value);
		}
	}
	if (vec_.empty()) {
		throw std::invalid_argument("no numbers provided");
	}
}

void PmergeMe::print_sequence(const std::string& label) const {
	std::cout << label;
	for (std::size_t i = 0; i < vec_.size(); ++i) {
		std::cout << ' ' << vec_[i];
	}
	std::cout << '\n';
}

void PmergeMe::run(int argc, char** argv) {
	parse(argc, argv);
	print_sequence("Before:");

	double vec_start = now_us();
	sort_vector(vec_);
	double vec_us = now_us() - vec_start;

	double deq_start = now_us();
	sort_deque(deq_);
	double deq_us = now_us() - deq_start;

	print_sequence("After: ");
	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << vec_.size()
		<< " elements with std::vector : " << vec_us << " us\n";
	std::cout << "Time to process a range of " << deq_.size()
		<< " elements with std::deque  : " << deq_us << " us\n";
}

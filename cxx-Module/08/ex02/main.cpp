#include "MutantStack.hpp"

#include <deque>
#include <iostream>
#include <list>
#include <stack>

namespace {

void subject_test() {
	std::cout << "--- subject test ---\n";
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << "top : " << mstack.top() << '\n';
	mstack.pop();
	std::cout << "size: " << mstack.size() << '\n';
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << '\n';
		++it;
	}
	std::stack<int> s(mstack);
	std::cout << "copied into std::stack, size: " << s.size() << '\n';
}

void reverse_and_const() {
	std::cout << "--- reverse + const iteration ---\n";
	MutantStack<int> mstack;
	for (int i = 0; i < 5; ++i) {
		mstack.push(i);
	}
	std::cout << "reverse: ";
	MutantStack<int>::reverse_iterator rit = mstack.rbegin();
	while (rit != mstack.rend()) {
		std::cout << *rit << ' ';
		++rit;
	}
	std::cout << '\n';

	const MutantStack<int> frozen(mstack);
	std::cout << "const  : ";
	MutantStack<int>::const_iterator cit = frozen.begin();
	while (cit != frozen.end()) {
		std::cout << *cit << ' ';
		++cit;
	}
	std::cout << '\n';
}

void stack_interface() {
	std::cout << "--- inherited std::stack interface ---\n";
	std::deque<int> source(3, 7);
	MutantStack<int> built(source);
	std::cout << "from container: size " << built.size()
		<< ", top " << built.top() << ", empty " << built.empty() << '\n';
	built.pop();
	std::cout << "after pop     : size " << built.size() << '\n';

	MutantStack<int> smaller;
	MutantStack<int> bigger;
	smaller.push(1);
	bigger.push(2);
	std::cout << "relational ops: " << (smaller == bigger)
		<< (smaller != bigger) << (smaller < bigger)
		<< (smaller >= bigger) << " (0110)\n";
}

void list_backed() {
	std::cout << "--- list-backed MutantStack ---\n";
	MutantStack<int, std::list<int> > mstack;
	mstack.push(5);
	mstack.push(17);
	mstack.pop();
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	MutantStack<int, std::list<int> >::iterator it = mstack.begin();
	while (it != mstack.end()) {
		std::cout << *it << '\n';
		++it;
	}
}

void list_reference() {
	std::cout << "--- std::list reference ---\n";
	std::list<int> lst;
	lst.push_back(5);
	lst.push_back(17);
	lst.pop_back();
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);

	std::list<int>::iterator it = lst.begin();
	std::list<int>::iterator ite = lst.end();
	while (it != ite) {
		std::cout << *it << '\n';
		++it;
	}
}

}

int main() {
	subject_test();
	reverse_and_const();
	stack_interface();
	list_backed();
	list_reference();
	return 0;
}

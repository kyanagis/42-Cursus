#include "MutantStack.hpp"

#include <cstddef>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <stack>
#include <vector>

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

void print_head() {
	std::cout << "  slot | address        |   offset |  value\n";
	std::cout << "  -----+----------------+----------+--------\n";
}

void print_offset(std::ptrdiff_t offset) {
	std::cout << std::showpos << std::setw(8) << offset << std::noshowpos;
}

const char* slot_mark(std::size_t slot, std::size_t size) {
	if (size == 1) {
		return "  <- top() == bottom";
	}
	if (slot + 1 == size) {
		return "  <- top()";
	}
	if (slot == 0) {
		return "  <- bottom (base)";
	}
	return "";
}

void print_slot(std::size_t slot, const int* element, const int* base,
	std::size_t size) {
	std::ptrdiff_t offset;

	offset = reinterpret_cast<const char*>(element)
		- reinterpret_cast<const char*>(base);
	std::cout << "  [" << std::setw(2) << slot << "] | "
		<< std::setw(14) << element << " | ";
	print_offset(offset);
	std::cout << " | " << std::setw(6) << *element
		<< slot_mark(slot, size) << '\n';
}

template <typename StackType>
void dump_frame(const StackType& mstack, const char* label) {
	std::size_t slot;

	std::cout << "=== stack frame: " << label << " ===\n";
	if (mstack.empty()) {
		std::cout << "  (empty)\n";
		return;
	}
	std::cout << "  base = bottom slot @ " << &*mstack.begin()
		<< ", offsets in bytes (sizeof(int) = " << sizeof(int) << ")\n";
	print_head();
	slot = mstack.size();
	typename StackType::const_reverse_iterator it = mstack.rbegin();
	while (it != mstack.rend()) {
		--slot;
		print_slot(slot, &*it, &*mstack.begin(), mstack.size());
		++it;
	}
}

void frame_view() {
	MutantStack<int> mstack;
	MutantStack<int, std::list<int> > nodes;

	mstack.push(5);
	mstack.push(17);
	mstack.pop();
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	dump_frame(mstack, "MutantStack<int> (deque-backed)");
	std::cout << "offset grows by " << sizeof(int)
		<< " per slot: the deque chunk is one contiguous block\n";

	nodes.push(5);
	nodes.push(3);
	nodes.push(737);
	nodes.push(0);
	dump_frame(nodes, "MutantStack<int, std::list<int> > (node-backed)");
	std::cout << "offsets are arbitrary (even negative): one node per slot, "
		"no frame\n";
}

void print_segment(std::size_t first, std::size_t last, const int* start) {
	std::cout << "  slots [" << std::setw(4) << first << " .. "
		<< std::setw(4) << last << "] @ " << std::setw(14) << start
		<< " : " << std::setw(4) << (last - first + 1) << " elements, "
		<< std::setw(5) << (last - first + 1) * sizeof(int)
		<< " bytes contiguous\n";
}

void fill_interleaved(MutantStack<int>& mstack, MutantStack<int>& noise) {
	for (int i = 0; i < 600; ++i) {
		mstack.push(i);
		noise.push(-i);
	}
}

void deque_segments() {
	MutantStack<int> mstack;
	MutantStack<int> noise;
	std::size_t slot;
	std::size_t first;
	const int* start;

	std::cout << "=== deque block map: 600 pushes, interleaved with a "
		"second stack ===\n";
	fill_interleaved(mstack, noise);
	MutantStack<int>::const_iterator it = mstack.begin();
	start = &*it;
	first = 0;
	slot = 0;
	while (it != mstack.end()) {
		if (slot != 0 && &*it != start + (slot - first)) {
			print_segment(first, slot - 1, start);
			first = slot;
			start = &*it;
		}
		++slot;
		++it;
	}
	print_segment(first, slot - 1, start);
	std::cout << "each segment is one std::deque block: contiguous inside, "
		"unrelated\nacross a boundary, so a deque is not one flat frame\n";
}

void print_relocation(const char* label, const int* before, const int* after) {
	std::cout << "  " << label << " | " << std::setw(14) << before << " | "
		<< std::setw(14) << after << " | ";
	if (before == after) {
		std::cout << "pinned\n";
		return;
	}
	std::cout << "MOVED -> old pointer dangles\n";
}

void address_stability() {
	MutantStack<int> mstack;
	std::vector<int> vec;
	const int* stack_base;
	const int* vector_base;

	std::cout << "=== base relocation check: 100 more pushes ===\n";
	mstack.push(42);
	vec.push_back(42);
	stack_base = &*mstack.begin();
	vector_base = &vec[0];
	for (int i = 0; i < 100; ++i) {
		mstack.push(i);
		vec.push_back(i);
	}
	std::cout << "  container    | base before    | base after     | "
		"verdict\n";
	std::cout << "  -------------+----------------+----------------+"
		"--------\n";
	print_relocation("deque bottom", stack_base, &*mstack.begin());
	print_relocation("vector [ 0] ", vector_base, &vec[0]);
	std::cout << "the vector reallocated, so every saved pointer became a "
		"stale read;\nthe deque kept each slot pinned at its address\n";
}

}

int main() {
	subject_test();
	reverse_and_const();
	stack_interface();
	list_backed();
	list_reference();
	frame_view();
	deque_segments();
	address_stability();
	return 0;
}

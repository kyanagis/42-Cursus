#include "easyfind.hpp"

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <list>
#include <vector>

namespace {

void search_vector(std::vector<int>& numbers, int value) {
	std::cout << "vector: searching for " << value << " -> ";
	try {
		std::vector<int>::iterator it = easyfind(numbers, value);
		std::cout << "found (index " << (it - numbers.begin()) << ")\n";
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}

void search_list(const std::list<int>& numbers, int value) {
	std::cout << "list  : searching for " << value << " -> ";
	try {
		std::list<int>::const_iterator it = easyfind(numbers, value);
		std::cout << "found (" << *it << ")\n";
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}

void print_head() {
	std::cout << "  slot | address        |   offset |  value\n";
	std::cout << "  -----+----------------+----------+--------\n";
}

const char* hit_mark(const int* element, const int* hit) {
	if (element == hit) {
		return "  <- easyfind hit";
	}
	return "";
}

void print_row(std::size_t slot, const int* element, const int* base,
	const char* mark) {
	std::ptrdiff_t offset;

	offset = reinterpret_cast<const char*>(element)
		- reinterpret_cast<const char*>(base);
	std::cout << "  [" << std::setw(2) << slot << "] | "
		<< std::setw(14) << element << " | "
		<< std::showpos << std::setw(8) << offset << std::noshowpos
		<< " | " << std::setw(6) << *element << mark << '\n';
}

template <typename It>
void dump_map(const char* label, It first, It last, const int* hit) {
	std::size_t slot;
	const int* base;

	std::cout << "=== memory map: " << label << " ===\n";
	if (first == last) {
		std::cout << "  (empty)\n";
		return;
	}
	base = &*first;
	std::cout << "  base = slot [ 0] @ " << base
		<< ", offsets in bytes (sizeof(int) = " << sizeof(int) << ")\n";
	print_head();
	slot = 0;
	while (first != last) {
		print_row(slot, &*first, base, hit_mark(&*first, hit));
		++slot;
		++first;
	}
}

void print_ascii(const unsigned char* bytes, std::size_t count) {
	std::size_t i;

	std::cout << " |";
	for (i = 0; i < count; ++i) {
		if (bytes[i] >= 32 && bytes[i] < 127) {
			std::cout << static_cast<char>(bytes[i]);
		} else {
			std::cout << '.';
		}
	}
	std::cout << "|\n";
}

void print_hex_line(std::size_t offset, const unsigned char* bytes,
	std::size_t count) {
	std::size_t i;

	std::cout << "  +" << std::setw(4) << std::setfill('0') << offset
		<< std::setfill(' ');
	for (i = 0; i < 16; ++i) {
		if (i < count) {
			std::cout << ' ' << std::hex << std::setw(2) << std::setfill('0')
				<< static_cast<unsigned int>(bytes[i]) << std::dec
				<< std::setfill(' ');
		} else {
			std::cout << "   ";
		}
	}
	print_ascii(bytes, count);
}

void hexdump(const int* base, std::size_t bytes) {
	const unsigned char* raw;
	std::size_t done;
	std::size_t chunk;

	raw = reinterpret_cast<const unsigned char*>(base);
	done = 0;
	while (done < bytes) {
		chunk = bytes - done;
		if (chunk > 16) {
			chunk = 16;
		}
		print_hex_line(done, raw + done, chunk);
		done += chunk;
	}
}

void reuse_freed_node(std::list<int>& numbers) {
	std::list<int>::iterator it;

	numbers.push_front(-1);
	it = numbers.begin();
	++it;
	++it;
	numbers.erase(it);
	numbers.push_back(99);
}

void show_memory_layout() {
	std::vector<int> contiguous;
	std::list<int> nodes;

	for (int i = 0; i < 5; ++i) {
		contiguous.push_back(i * 11);
		nodes.push_back(i * 11);
	}
	dump_map("std::vector<int> (one contiguous buffer)", contiguous.begin(),
		contiguous.end(), &*easyfind(contiguous, 33));
	std::cout << "offset == slot * " << sizeof(int)
		<< ": easyfind walks a flat array, the hit is at a fixed stride\n";
	std::cout << "=== hexdump: the whole vector buffer ===\n";
	hexdump(&contiguous[0], contiguous.size() * sizeof(int));
	std::cout << "little endian: 33 shows up as 21 00 00 00\n";

	dump_map("std::list<int> (independent nodes)", nodes.begin(), nodes.end(),
		&*easyfind(nodes, 33));
	std::cout << "offsets jump by arbitrary amounts: one heap node per slot, "
		"no stride\n";
	reuse_freed_node(nodes);
	dump_map("std::list<int> after erase + push_back", nodes.begin(),
		nodes.end(), &*easyfind(nodes, 99));
	std::cout << "offsets can go negative and the freed node gets reused: "
		"traversal\norder no longer follows address order\n";
}

}

int main() {
	std::vector<int> numbers;
	for (int i = 0; i < 10; ++i) {
		numbers.push_back(i * 2);
	}

	search_vector(numbers, 8);
	search_vector(numbers, 0);
	search_vector(numbers, 18);
	search_vector(numbers, 7);
	search_vector(numbers, -1);

	std::list<int> letters;
	letters.push_back(42);
	letters.push_back(21);
	letters.push_back(84);
	search_list(letters, 21);
	search_list(letters, 100);

	std::vector<int> empty;
	search_vector(empty, 1);

	show_memory_layout();

	return 0;
}

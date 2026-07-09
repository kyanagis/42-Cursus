#include "Data.hpp"
#include "Serializer.hpp"

#include <iostream>

int main(void) {
	Data data;
	Data* original;
	uintptr_t raw;
	Data* restored;

	data.id = 42;
	data.name = "forty-two";
	data.value = 3.14;

	original = &data;
	raw = Serializer::serialize(original);
	restored = Serializer::deserialize(raw);

	std::cout << "original pointer : " << original << '\n';
	std::cout << "serialized value : " << raw << '\n';
	std::cout << "restored pointer : " << restored << '\n';

	if (restored == original)
		std::cout << "[OK] restored pointer equals the original" << '\n';
	else
		std::cout << "[KO] restored pointer differs" << '\n';

	std::cout << "restored->id    : " << restored->id << '\n';
	std::cout << "restored->name  : " << restored->name << '\n';
	std::cout << "restored->value : " << restored->value << '\n';

	return 0;
}

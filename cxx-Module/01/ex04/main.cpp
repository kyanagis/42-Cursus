#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static std::string replaceAll(const std::string& content,
							  const std::string& s1, const std::string& s2) {
	if (s1.empty()) {
		return content;
	}

	std::string result;
	std::string::size_type pos = 0;
	std::string::size_type found = content.find(s1, pos);

	while (found != std::string::npos) {
		result += content.substr(pos, found - pos);
		result += s2;
		pos = found + s1.length();
		found = content.find(s1, pos);
	}
	result += content.substr(pos);
	return result;
}

static bool readFile(const std::string& filename, std::string& out) {
	std::ifstream input(filename.c_str());
	if (!input.is_open()) {
		return false;
	}

	std::stringstream buffer;
	buffer << input.rdbuf();
	out = buffer.str();
	input.close();
	return true;
}

static bool writeFile(const std::string& filename, const std::string& content) {
	std::ofstream output(filename.c_str());
	if (!output.is_open()) {
		return false;
	}

	output << content;
	output.close();
	if (output.fail()) {
		return false;
	}
	return true;
}

int main(int argc, char** argv) {
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0]
				  << " <filename> <s1> <s2>" << std::endl;
		return 1;
	}

	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	if (s1.empty()) {
		std::cerr << "Error: s1 (the string to replace) must not be empty"
				  << std::endl;
		return 1;
	}

	std::string content;
	if (!readFile(filename, content)) {
		std::cerr << "Error: cannot open file '" << filename << "'"
				  << std::endl;
		return 1;
	}

	std::string replaced = replaceAll(content, s1, s2);
	if (!writeFile(filename + ".replace", replaced)) {
		std::cerr << "Error: cannot create file '"
				  << filename << ".replace'" << std::endl;
		return 1;
	}

	return 0;
}

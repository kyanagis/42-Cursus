#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl {
public:
	Harl();
	~Harl();

	void filter(const std::string& level);

private:
	void debug(void);
	void info(void);
	void warning(void);
	void error(void);

	int levelToIndex(const std::string& level) const;
};

#endif

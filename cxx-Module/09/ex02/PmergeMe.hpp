#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <string>
#include <vector>

// PmergeMe sorts a positive integer sequence with the Ford-Johnson
// (merge-insertion) algorithm. The very same algorithm is implemented twice --
// once on std::vector and once on std::deque -- so the two runtimes can be
// compared without any generic code path shared between them, as advised by
// the subject.

class PmergeMe {
public:
	PmergeMe();
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();

	void run(int argc, char** argv);

private:
	std::vector<int> vec_;
	std::deque<int> deq_;

	void parse(int argc, char** argv);
	void print_sequence(const std::string& label) const;
};

#endif

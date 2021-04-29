//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"
std::string currentTitle;
std::string currentPrefix;
int 		currentNum;

#define CLR_GREEN "\033[32m"
#define CLR_RED "\033[91m"
#define CLR_RESET "\033[0m"
#define CLR_DIM "\033[37m"

void	start_batch(const std::string &prefix) {
	if (!currentPrefix.empty())
		std::cout << "\n";
	currentPrefix = prefix;
	std::cout << CLR_DIM << "-- Starting " + currentPrefix + " tests --" << CLR_RESET << std::endl;
}

void	start_test(const std::string &title, int num) {
	currentTitle = title;
	currentNum = num;
	std::cout << CLR_DIM << "Test " << currentNum << " (" << currentTitle << "): ..." << CLR_RESET << "\r" << std::flush;
}

void	fail_test() {
	std::cout << CLR_RED << "Test " << currentNum << " (" << currentTitle << "): KO!" << CLR_RESET << std::endl;
	std::cout << CLR_RED << "\nA test failed, exiting... " << CLR_RESET << std::endl;
	::_exit(1);
}
void	end_test() {
	std::cout << CLR_GREEN << "Test " << currentNum << " (" << currentTitle << "): OK!" << CLR_RESET << std::endl;
}

void	end_of_tests() {
	std::cout << CLR_GREEN << "\nAll tests passed :) " << CLR_RESET << std::endl;
}

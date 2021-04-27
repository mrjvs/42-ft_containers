//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <iostream>

class testType {
public:
	std::string	type;
	bool 		ftOnly;

	testType(const std::string &str, bool ft_only = false): type(str), ftOnly(ft_only) {}
};
struct testTypeCompare {
	bool operator()(const testType &lhs, const testType &rhs) {
		return lhs.type < rhs.type;
	}
};

std::set<testType, testTypeCompare>	types;
static void	createTypes() {
	types.insert(testType("list"));
	types.insert(testType("ordered_list", true));
	types.insert(testType("multimap"));
	types.insert(testType("map"));
	types.insert(testType("multiset"));
	types.insert(testType("set"));
	types.insert(testType("queue"));
	types.insert(testType("stack"));
}

static void printUsage(std::ostream &o) {
	o <<
		"Usage: ./ft_container_tests <type> <tests...>\n"
		"<type>\t\t\tEither 'FT' or 'STD' (case sensitive), to specify which library to test\n"
		"<tests...>\t\ta list of tests, not specifying any tests will run all tests. \nTest options:\n"
		" - list\n"
		" - ordered_list (only FT)\n"
		" - multimap\n"
		" - map\n"
		" - multiset\n"
		" - set\n"
		" - queue\n"
		" - stack\n"
	<< std::endl;
}

static void argParser(int argc, char *argv[]) {
	// arg length check
	if (argc < 2) {
		std::cerr << "not enough arguments!\n\n";
		printUsage(std::cerr);
		return;
	}

	// parse type (or help)
	std::string type = argv[1];
	if (type != "FT" && type != "STD" && type != "help") {
		std::cerr << "Invalid test type\n\n";
		printUsage(std::cerr);
		return;
	}
	if (type == "help") {
		printUsage(std::cout);
		return;
	}

	// parse input tests
	std::vector<std::string>	tests;
	if (argc == 2) {
		for (std::set<testType, testTypeCompare>::iterator it = types.begin(); it != types.end(); ++it) {
			if ((it->ftOnly && type == "FT") || !it->ftOnly)
				tests.push_back(it->type);
		}
	}
	else {
		for (int i = 2; i < argc; ++i) {
			std::set<testType, testTypeCompare>::iterator	test = types.find(std::string(argv[i]));
			if (test == types.end()) {
				std::cerr << "unrecognized test: '" << argv[i] << "'\n\n";
				printUsage(std::cerr);
				return;
			}
		}
	}

	// check for type mismatches
	for (std::vector<std::string>::iterator it = tests.begin(); it != tests.end(); ++it) {
		testType test = *types.find(*it);
		if (test.ftOnly && type != "FT") {
			std::cerr << "test '" << test.type << "' can only be used on FT test type\n\n";
			printUsage(std::cerr);
			return;
		}
	}

	// execute tests
	for (std::vector<std::string>::iterator it = tests.begin(); it != tests.end(); ++it) {
		// execute test
		testType test = *types.find(*it);
		if (type == "STD") {
			if (test.type == "list") list_tests<std::list<int>, std::list<testStruct> >().run();
			else if (test.type == "multimap") multimap_tests<std::multimap<int, int>, std::pair<int, int>, std::pair<std::multimap<int, int>::iterator, std::multimap<int, int>::iterator>, std::pair<std::multimap<int, int>::const_iterator, std::multimap<int, int>::const_iterator> >().run();
			else if (test.type == "map") map_tests<std::map<int, int>, std::pair<int, int>, std::pair<std::map<int, int>::iterator, bool> >().run();
			else if (test.type == "multiset") multiset_tests<std::multiset<int>, std::pair<std::multiset<int, int>::const_iterator, std::multiset<int, int>::const_iterator> >().run();
			else if (test.type == "set") set_tests<std::set<int>, std::pair<std::set<int>::iterator, bool> >().run();
			else if (test.type == "queue") queue_tests<std::queue<int> >().run();
			else if (test.type == "stack") stack_tests<std::stack<int> >().run();
		}
		else if (type == "FT") {
			if (test.type == "list") list_tests<ft::list<int>, ft::list<testStruct> >().run();
			else if (test.type == "ordered_list") ordered_list_tests<ft::orderedList<int> >().run();
			else if (test.type == "multimap") multimap_tests<ft::multimap<int, int>, ft::pair<int, int>, ft::pair<ft::multimap<int, int>::iterator, ft::multimap<int, int>::iterator>, ft::pair<ft::multimap<int, int>::const_iterator, ft::multimap<int, int>::const_iterator> >().run();
			else if (test.type == "map") map_tests<ft::map<int, int>, ft::pair<int, int>, ft::pair<ft::map<int, int>::iterator, bool> >().run();
			else if (test.type == "multiset") multiset_tests<ft::multiset<int>, ft::pair<ft::multiset<int, int>::const_iterator, ft::multiset<int, int>::const_iterator> >().run();
			else if (test.type == "set") set_tests<ft::set<int>, ft::pair<ft::set<int>::iterator, bool> >().run();
			else if (test.type == "queue") queue_tests<ft::queue<int> >().run();
			else if (test.type == "stack") stack_tests<ft::stack<int> >().run();
		}
	}
	end_of_tests();
}

int main(int argc, char *argv[]) {
	createTypes();
	argParser(argc, argv);
    return 0;
}

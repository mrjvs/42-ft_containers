//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"

int 	num2 = 0;
#define test(str) start_test(str, ++num2)

template <class T>
static void compareList(ft::orderedList<T> list, const std::string &result) {
	std::stringstream ss;
	int i = 0;
	for (typename ft::orderedList<T>::iterator it = list.begin(); it != list.end(); ++it) {
		if (i != 0)
			ss << "-";
		ss << *it;
		++i;
	}
	if (ss.str() != result)
		fail_test();
}

static void constructTests() {
	test("Basic constructor tests");
	{
		ft::orderedList<int> l1;
		l1.insert(1);
		l1.insert(2);
		ft::orderedList<int> l2(l1);
		compareList<int>(l1, "1-2");
		compareList<int>(l2, "1-2");
	}
	end_test();
}

static void modifierTests() {
	test("insert tests");
	{
		ft::orderedList<int>	l1;
		compareList<int>(l1, "");

		// insert bunch of stuff
		l1.insert(5);
		l1.insert(2);
		compareList<int>(l1, "2-5");
		l1.insert(42);
		l1.insert(69);
		l1.insert(-5);
		l1.insert(-5);
		l1.insert(-4);
		compareList<int>(l1, "-5--5--4-2-5-42-69");
	}
	end_test();
}

static void accessTests() {
	// TODO range tests
	test("access tests");
	{
		ft::orderedList<int>	l1;
		l1.insert(3);
		l1.insert(1);
		l1.insert(2);

		// not existent
		if (l1.get(4) != l1.end()) fail_test();

		// find keys
		if (l1.get(1) != l1.begin()) fail_test();
		if (l1.get(2) != ++(l1.begin())) fail_test();
		if (l1.get(3) != ++++(l1.begin())) fail_test();

		// has keys
		if (!l1.has(1) || !l1.has(2) || !l1.has(3)) fail_test();
		if (l1.has(42)) fail_test();
	}
	end_test();
}

// only test interesting functions, all fancy stuff is done in ft::list
void ordered_list_tests() {
	start_batch("orderedList");
	constructTests();
	modifierTests();
	accessTests();
	// TODO operations
	// TODO execute unused functions
}

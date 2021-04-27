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
		ft::orderedList<int> l3;
		l3 = l1;
		l1.insert(3);
		compareList<int>(l3, "1-2");
		compareList<int>(l1, "1-2-3");
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
	test("upperbound/lowerbound/equal tests");
	{
		ft::orderedList<int>	l1;
		const ft::orderedList<int>	&l2 = l1;
		l1.insert(3);
		l1.insert(1);
		l1.insert(2);
		l1.insert(2);
		l1.insert(6);
		l1.insert(6);
		l1.insert(5);
		l1.insert(7);
		l1.insert(9);
		l1.insert(9);
		compareList<int>(l1, "1-2-2-3-5-6-6-7-9-9");

		// lower bound
		if (l1.lower_bound(1) != l1.begin()) fail_test();
		if (l1.lower_bound(2) != ++(l1.begin())) fail_test();
		if (l1.lower_bound(9) != ++++++++++++++++(l1.begin())) fail_test(); // first 9
		if (l1.lower_bound(42) != l1.end()) fail_test();
		if (l2.lower_bound(1) != l2.begin()) fail_test();
		if (l2.lower_bound(2) != ++(l2.begin())) fail_test();
		if (l2.lower_bound(9) != ++++++++++++++++(l2.begin())) fail_test();
		if (l2.lower_bound(42) != l2.end()) fail_test();

		// upper bound
		if (l1.upper_bound(1) != ++(l1.begin())) fail_test();
		if (l1.upper_bound(2) != ++++++(l1.begin())) fail_test(); // after last 2
		if (l1.upper_bound(9) != l1.end()) fail_test(); // after last 9
		if (l1.upper_bound(42) != l1.end()) fail_test();
		if (l2.upper_bound(1) != ++(l2.begin())) fail_test();
		if (l2.upper_bound(2) != ++++++(l2.begin())) fail_test(); // after last 2
		if (l2.upper_bound(9) != l2.end()) fail_test(); // after last 9
		if (l2.upper_bound(42) != l2.end()) fail_test();

		// equal range
		std::pair<ft::orderedList<int>::iterator, ft::orderedList<int>::iterator> ret;
		std::pair<ft::orderedList<int>::const_iterator, ft::orderedList<int>::const_iterator> ret_const;
		ret = l1.equal_range(1);
		ret_const = l2.equal_range(1);
		if (l1.lower_bound(1) != ret.first || l1.upper_bound(1) != ret.second) fail_test();
		if (l2.lower_bound(1) != ret_const.first || l2.upper_bound(1) != ret_const.second) fail_test();
		ret = l1.equal_range(2);
		ret_const = l2.equal_range(2);
		if (l1.lower_bound(2) != ret.first || l1.upper_bound(2) != ret.second) fail_test();
		if (l2.lower_bound(2) != ret_const.first || l2.upper_bound(2) != ret_const.second) fail_test();
		ret = l1.equal_range(9);
		ret_const = l2.equal_range(9);
		if (l1.lower_bound(9) != ret.first || l1.upper_bound(9) != ret.second) fail_test();
		if (l2.lower_bound(9) != ret_const.first || l2.upper_bound(9) != ret_const.second) fail_test();
		ret = l1.equal_range(42);
		ret_const = l2.equal_range(42);
		if (l1.lower_bound(42) != ret.first || l1.upper_bound(42) != ret.second) fail_test();
		if (l2.lower_bound(42) != ret_const.first || l2.upper_bound(42) != ret_const.second) fail_test();
	}
	end_test();
}

static void nonExecutingFunctionTests() {
	test("other tests");
	{
		ft::orderedList<int> l1;
		ft::orderedList<int> l2;
		ft::orderedList<int> l3;
		const ft::orderedList<int> &l4 = l3;
		l1.insert(1);
		l1.insert(2);
		l2.insert(42);
		l3.insert(5);
		l3.insert(6);
		l3.insert(8);

		// iterators
		(void)l3.begin();
		(void)l3.rbegin();
		(void)l3.end();
		(void)l3.rend();
		(void)l4.begin();
		(void)l4.rbegin();
		(void)l4.end();
		(void)l4.rend();

		// modifiers
		(void)l1.erase(l1.begin());
		(void)l1.clear();
		(void)l1.swap(l2);

		// access
		(void)l3.front();
		(void)l4.front();
		(void)l3.back();
		(void)l4.back();

		//capacity
		(void)l1.empty();
		(void)l1.size();
		(void)l1.max_size();

		// observers
		(void)l1.value_comp();
		(void)l1.get_allocator();
	}
	end_test();
}

// only test interesting functions, all fancy stuff is done in ft::list
void ordered_list_tests() {
	start_batch("orderedList");
	constructTests();
	modifierTests();
	accessTests();
	nonExecutingFunctionTests();
}

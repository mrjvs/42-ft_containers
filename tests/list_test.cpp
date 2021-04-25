//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"

int 	num = 0;
#define test(str) start_test(str, ++num)

template <class T>
static void compareList(ft::list<T> list, const std::string &result) {
	std::stringstream ss;
	int i = 0;
	for (typename ft::list<T>::iterator it = list.begin(); it != list.end(); ++it) {
		if (i != 0)
			ss << "-";
		ss << *it;
		++i;
	}
	if (ss.str() != result)
		fail_test();
}


template <class iterator>
static void compareList(iterator start, iterator last, const std::string &result) {
	std::stringstream ss;
	int i = 0;
	for (iterator it = start; it != last; ++it) {
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
		std::vector<int> vect;
		vect.push_back(1);
		vect.push_back(2);

		ft::list<int> l1;
		ft::list<int> l2(vect.begin(), vect.end());
		ft::list<int> l3((ft::list<int>::size_type)(5), 42);
		ft::list<int> l4(l2);
	}
	end_test();
	test("Deep copy tests");
	{
		ft::list<int>	l1;
		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);
		ft::list<int>	l2(l1);
		l1.push_back(4);
		l2.push_back(42);
		compareList<int>(l1, "1-2-3-4");
		compareList<int>(l2, "1-2-3-42");

		ft::list<int>	l3;
		l3.push_back(420);
		compareList<int>(l3, "420");

		l3 = l1;
		l1.push_back(5);
		compareList<int>(l1, "1-2-3-4-5");
		compareList<int>(l3, "1-2-3-4");
	}
	end_test();
}

static void iteratorTests() {
	test("iterator type tests");
	{
		ft::list<int>	l1;
		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);
		const ft::list<int>	&l2 = l1;

		compareList<ft::list<int>::iterator>(l1.begin(), l1.end(), "1-2-3");
		compareList<ft::list<int>::reverse_iterator>(l1.rbegin(), l1.rend(), "3-2-1");
		compareList<ft::list<int>::const_iterator>(l2.begin(), l2.end(), "1-2-3");
		compareList<ft::list<int>::const_reverse_iterator>(l2.rbegin(), l2.rend(), "3-2-1");
	}
	end_test();
	test("iterator operator tests");
	{
		ft::list<int>	l1;
		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);
		ft::list<int>::iterator it = l1.begin();
		ft::list<int>::iterator it2;
		it2 = l1.end(); // assignment
		if (*(it++) != 1) fail_test(); // increment
		if (*(it) != 2) fail_test();
		if (*(++it) != 3) fail_test();
		if (*(it--) != 3) fail_test(); // decrement
		if (*(it) != 2) fail_test();
		if (*(--it) != 1) fail_test();

		// comparison
		++++++it; // set to end
		if (it != it2) fail_test();
		if (!(it == it2)) fail_test();
	}
	end_test();
	test("iterator out of bounds tests");
	{
		ft::list<int>	l1;
		l1.push_back(1);
		l1.push_back(2);
		l1.push_back(3);
		ft::list<int>::iterator it = l1.begin();

		// out of bounds check
		try {
			it--; // should throw
			fail_test();
		} catch (const std::exception &e) {}
		++++++it; // set to end
		try {
			it++; // should throw
			fail_test();
		} catch (const std::exception &e) {}
	}
	end_test();
}

static void capacityTests() {
	test("capacity tests");
	{
		ft::list<int>	l1;
		if (!l1.empty()) fail_test();
		if (l1.size() != 0) fail_test();
		l1.push_back(42);
		if (l1.size() != 1) fail_test();
		if (l1.empty()) fail_test();
		if (std::numeric_limits<std::allocator<int>::size_type>::max() != l1.max_size()) fail_test();
	}
	end_test();
}

static void modifierTests() {
	test("push/pop tests");
	{
		ft::list<int>	l1;
		compareList<int>(l1, "");

		// push back
		l1.push_back(1);
		compareList<int>(l1, "1");
		l1.push_back(2);
		compareList<int>(l1, "1-2");

		// push front
		l1.push_front(-1);
		compareList<int>(l1, "-1-1-2");
		l1.push_front(-2);
		compareList<int>(l1, "-2--1-1-2");

		// pop back
		l1.pop_back();
		compareList<int>(l1, "-2--1-1");

		// pop front
		l1.pop_front();
		compareList<int>(l1, "-1-1");
		l1.pop_front();
		compareList<int>(l1, "1");
	}
	end_test();
	test("assign/erase tests");
	{
		ft::list<int>	l1;
		std::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		vec.push_back(3);
		vec.push_back(4);
		vec.push_back(5);

		// assign repeat
		l1.assign((size_t)(5), 42);
		compareList<int>(l1, "42-42-42-42-42");

		// assign iterator
		l1.assign(vec.begin(), vec.end());
		compareList<int>(l1, "1-2-3-4-5");

		// erase single element
		l1.erase(++(l1.begin()));
		compareList<int>(l1, "1-3-4-5");

		// erase iterator
		l1.erase(l1.begin(), l1.end());
		compareList<int>(l1, "");

		// clear
		l1.assign(vec.begin(), vec.end());
		l1.clear();
		compareList<int>(l1, "");
	}
	end_test();
	test("insert/resize/swap tests");
	{
		ft::list<int>	l1;
		ft::list<int>	l2;
		l1.push_back(1);
		l2.push_back(3);
		l2.push_back(4);
		l2.push_back(5);
		compareList<int>(l1, "1");
		compareList<int>(l2, "3-4-5");

		// swap
		l1.swap(l2);
		compareList<int>(l2, "1");
		compareList<int>(l1, "3-4-5");

		// resize
		l2.resize(5, 42);
		l1.resize(2);
		compareList<int>(l2, "1-42-42-42-42");
		compareList<int>(l1, "3-4");

		// insert
		l2.insert(++++(l2.begin()), (size_t)(2), 0);
		compareList<int>(l2, "1-42-42-0-0-42-42");
		ft::list<int>::iterator it = l2.insert(++(l2.begin()), 6);
		compareList<int>(l2, "1-42-6-42-0-0-42-42");
		if (*it != 6 || *(++it) != 42) fail_test();

		// insert iterator
		l1.insert(l1.begin(), l2.begin(), l2.end());
		compareList<int>(l1, "3-1-42-6-42-0-0-42-42-4");
	}
	end_test();
}

static void accessTests() {
	test("access tests");
	{
		ft::list<int>	l1;
		l1.push_back(1);

		if (l1.front() != 1) fail_test();
		if (l1.back() != 1) fail_test();

		l1.push_back(2);

		if (l1.front() != 1) fail_test();
		if (l1.back() != 2) fail_test();
	}
	end_test();
}

static void comparisonTests() {
	test("equality tests");
	{
		ft::list<int>	l1;
		l1.push_back(1);
		l1.push_back(2);

		ft::list<int>	l2;
		l2.push_back(1);
		l2.push_back(2);

		// equality
		if (l1 != l2) fail_test();
		if (l1 < l2) fail_test();
		if (l1 > l2) fail_test();
		if (!(l1 == l2)) fail_test();

		// inequality
		l1.push_back(3);
		if (l1 == l2) fail_test();
		if (!(l1 != l2)) fail_test();

		// greater/lesser than
		if (l1 <= l2) fail_test();
		if (l1 < l2) fail_test();
		l2.push_back(42);
		if (l1 >= l2) fail_test();
		if (l1 > l2) fail_test();
	}
	end_test();
}


static void nonMemberFunctions() {
	test("non member function tests");
	{
		ft::list<int>	l1;
		l1.push_back(1);
		l1.push_back(2);

		ft::list<int>	l2;
		l2.push_back(3);
		l2.push_back(4);
		l2.push_back(5);

		// swap
		ft::swap(l1, l2);
		compareList<int>(l1, "3-4-5");
		compareList<int>(l2, "1-2");
	}
	end_test();
}

void list_tests() {
	start_batch("list");
	constructTests();
	iteratorTests();
	capacityTests();
	modifierTests();
	accessTests();
	comparisonTests();
	nonMemberFunctions();
	// TODO operations
}

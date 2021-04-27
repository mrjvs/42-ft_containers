//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"
#include <map>

int 	num3 = 0;
#define test(str) start_test(str, ++num3)

template <class Key, class T>
static void compareMap(ft::multimap<Key,T> list, const std::string &result) {
	std::stringstream ss;
	int i = 0;
	for (typename ft::multimap<Key,T>::iterator it = list.begin(); it != list.end(); ++it) {
		if (i != 0)
			ss << "-";
		ss << "(" << (*it).first << "," << (*it).second << ")";
		++i;
	}
	if (ss.str() != result)
		fail_test();
}

static void constructTests() {
	test("Basic constructor tests");
	{
		std::vector<ft::pair<int, int> > vect;
		vect.push_back(ft::pair<int,int>(5, 42));
		vect.push_back(ft::pair<int,int>(1, 69));

		ft::multimap<int,int> l1;
		ft::multimap<int,int> l2(vect.begin(), vect.end());
		ft::multimap<int,int> l3;
		l3 = l2;
		ft::multimap<int,int> l4(l2);
		l4.insert(ft::pair<int,int>(3, 3));
		compareMap<int,int>(l1, "");
		compareMap<int,int>(l2, "(1,69)-(5,42)");
		compareMap<int,int>(l3, "(1,69)-(5,42)");
		compareMap<int,int>(l4, "(1,69)-(3,3)-(5,42)");
	}
	end_test();
}

static void modifierTests() {
	test("insert iterator tests");
	{
		ft::multimap<int,int> l1;
		l1.insert(ft::pair<int,int>(3, 3));
		std::vector<ft::pair<int, int> > vect;
		vect.push_back(ft::pair<int,int>(5, 42));
		vect.push_back(ft::pair<int,int>(1, 69));

		l1.insert(vect.begin(), vect.end());
		compareMap<int,int>(l1, "(1,69)-(3,3)-(5,42)");
	}
	end_test();
	test("erase key tests");
	{
		ft::multimap<int,int> l1;
		l1.insert(l1.begin(), ft::pair<int,int>(3, 3));
		l1.insert(ft::pair<int,int>(5, 42));
		l1.insert(ft::pair<int,int>(5, 43));
		l1.insert(ft::pair<int,int>(9, 9));
		compareMap<int,int>(l1, "(3,3)-(5,43)-(5,42)-(9,9)");
		l1.erase(5);
		compareMap<int,int>(l1, "(3,3)-(9,9)");
		l1.erase(l1.begin());
		compareMap<int,int>(l1, "(9,9)");
		l1.erase(42);
		compareMap<int,int>(l1, "(9,9)");
		l1.insert(ft::pair<int,int>(5, 42));
		l1.erase(l1.begin(), l1.end());
		compareMap<int,int>(l1, "");
	}
	end_test();
}

static void operationTests() {
	test("find/count tests");
	{
		ft::multimap<int,int> l1;
		const ft::multimap<int,int> &l2 = l1;
		ft::multimap<int,int> l3;
		l1.insert(ft::pair<int,int>(3, 3));
		l1.insert(ft::pair<int,int>(5, 6));
		l1.insert(ft::pair<int,int>(5, 5));
		l1.insert(ft::pair<int,int>(9, 9));
		compareMap<int,int>(l1, "(3,3)-(5,5)-(5,6)-(9,9)");

		// find tests
		if (l1.find(9) != --(l1.end())) fail_test();
		if (l1.find(5) != ++(l1.begin())) fail_test();
		if (l2.find(9) != --(l2.end())) fail_test();
		if (l2.find(5) != ++(l2.begin())) fail_test();

		// empty/nonexistent find
		if (l3.find(5) != l3.end()) fail_test();
		if (l1.find(1) != l1.end()) fail_test();
		if (l1.find(1) != l1.end()) fail_test();

		// count tests
		if (l1.count(3) != 1) fail_test();
		if (l1.count(5) != 2) fail_test();
		if (l1.count(1) != 0) fail_test();
		if (l2.count(3) != 1) fail_test();
		if (l2.count(5) != 2) fail_test();
		if (l2.count(1) != 0) fail_test();
		if (l3.count(1) != 0) fail_test();
	}
	end_test();
	test("upper/lower/equal find tests");
	{
		ft::multimap<int,int> l1;
		const ft::multimap<int,int> &l2 = l1;
		l1.insert(ft::pair<int,int>(3, 3));
		l1.insert(ft::pair<int,int>(5, 5));
		l1.insert(ft::pair<int,int>(5, 6));
		l1.insert(ft::pair<int,int>(9, 9));

		// lower bound tests
		if (l1.lower_bound(9) != --(l1.end())) fail_test();
		if (l1.lower_bound(5) != ++(l1.begin())) fail_test();
		if (l1.lower_bound(1) != l1.end()) fail_test();
		if (l2.lower_bound(9) != --(l2.end())) fail_test();
		if (l2.lower_bound(5) != ++(l2.begin())) fail_test();
		if (l2.lower_bound(1) != l2.end()) fail_test();

		// upper bound tests
		if (l1.upper_bound(9) != l1.end()) fail_test();
		if (l1.upper_bound(5) != ++++++(l1.begin())) fail_test();
		if (l1.upper_bound(1) != l1.end()) fail_test();
		if (l2.upper_bound(9) != l2.end()) fail_test();
		if (l2.upper_bound(5) != ++++++(l2.begin())) fail_test();
		if (l2.upper_bound(1) != l2.end()) fail_test();


		// equal range
		if (l1.equal_range(9) != ft::pair<ft::multimap<int,int>::iterator,ft::multimap<int,int>::iterator>(--(l1.end()), l1.end())) fail_test();
		if (l1.equal_range(5) != ft::pair<ft::multimap<int,int>::iterator,ft::multimap<int,int>::iterator>(++(l1.begin()), --(l1.end()))) fail_test();
		if (l1.equal_range(1) != ft::pair<ft::multimap<int,int>::iterator,ft::multimap<int,int>::iterator>(l1.end(), l1.end())) fail_test();
		if (l2.equal_range(9) != ft::pair<ft::multimap<int,int>::const_iterator,ft::multimap<int,int>::const_iterator>(--(l2.end()), l2.end())) fail_test();
		if (l2.equal_range(5) != ft::pair<ft::multimap<int,int>::const_iterator,ft::multimap<int,int>::const_iterator>(++(l2.begin()), --(l2.end()))) fail_test();
		if (l2.equal_range(1) != ft::pair<ft::multimap<int,int>::const_iterator,ft::multimap<int,int>::const_iterator>(l2.end(), l2.end())) fail_test();
	}
	end_test();
}

// calling these functions will make the template functions run at least once, so they dont have runtime errors
static void executionNonUsedTests() {
	test("other tests");
	{
		ft::multimap<int,int> l1;
		const ft::multimap<int,int> &l2 = l1;
		ft::multimap<int,int> l3;
		// iterators
		(void)l1.begin();
		(void)l1.rbegin();
		(void)l1.end();
		(void)l1.rend();
		(void)l2.begin();
		(void)l2.rbegin();
		(void)l2.end();
		(void)l2.rend();

		// capacity
		(void)l1.empty();
		(void)l1.size();
		(void)l1.max_size();

		// modifiers
		l1.clear();
		l1.swap(l3);

		// observers
		(void)l1.key_comp();
		(void)l1.value_comp();
		(void)l1.get_allocator();
	}
	end_test();
}

// only test things that are different from orderedList
void multimap_test() {
	start_batch("multimap");
	constructTests();
	modifierTests();
	operationTests();
	executionNonUsedTests();
}

//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"

int 	num4 = 0;
#define test(str) start_test(str, ++num4)

template <class Key, class T>
static void compareMap(ft::map<Key,T> list, const std::string &result) {
	std::stringstream ss;
	int i = 0;
	for (typename ft::map<Key,T>::iterator it = list.begin(); it != list.end(); ++it) {
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
		std::vector<std::pair<int, int> > vect;
		vect.push_back(std::pair<int,int>(5, 42));
		vect.push_back(std::pair<int,int>(1, 69));

		ft::map<int,int> l1;
		ft::map<int,int> l2(vect.begin(), vect.end());
		ft::map<int,int> l3;
		l3 = l2;
		ft::map<int,int> l4(l2);
		l4.insert(std::pair<int,int>(3, 3));
		compareMap<int,int>(l1, "");
		compareMap<int,int>(l2, "(1,69)-(5,42)");
		compareMap<int,int>(l3, "(1,69)-(5,42)");
		compareMap<int,int>(l4, "(1,69)-(3,3)-(5,42)");
	}
	end_test();
}

static void modifierTests() {
	test("unique insert tests");
	{
		ft::map<int,int> l1;
		// insert single
		std::pair<ft::map<int,int>::iterator,bool> ret = l1.insert(std::pair<int,int>(3, 3));
		if (ret.first != l1.begin() || ret.second != true) fail_test();
		ret = l1.insert(std::pair<int,int>(3, 69));
		if (ret.first != l1.begin() || ret.second != false) fail_test();

		// insert with hint
		ft::map<int,int>::iterator it = l1.insert(l1.begin(), std::pair<int,int>(6, -42));
		if (it != ++(l1.begin())) fail_test();

		// insert with iterator range
		std::vector<std::pair<int, int> > vect;
		vect.push_back(std::pair<int,int>(5, 42));
		vect.push_back(std::pair<int,int>(1, 69));
		l1.insert(vect.begin(), vect.end());

		// compare end result
		compareMap<int,int>(l1, "(1,69)-(3,3)-(5,42)-(6,-42)");
	}
	end_test();
	test("operator access tests");
	{
		ft::map<int,int> l1;
		l1[5];
		compareMap<int,int>(l1, "(5,0)");
		l1[5] = 42;
		compareMap<int,int>(l1, "(5,42)");
		l1[1] = 1;
		compareMap<int,int>(l1, "(1,1)-(5,42)");
	}
	end_test();
}

// calling these functions will make the template functions run at least once, so they dont have runtime errors
// all of these are tested in multimap
static void executionNonUsedTests() {
	test("other tests");
	{
		ft::map<int,int> l1;
		const ft::map<int,int> &l2 = l1;
		ft::map<int,int> l3;
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
		l1[1] = 1;
		l1.erase(l1.begin());
		l1.erase(l1.begin(), l1.end());
		l1.erase(42);
		l1.clear();
		l1.swap(l3);

		// observers
		(void)l1.key_comp();
		(void)l1.value_comp();

		// operations
		(void)l1.find(42);
		(void)l2.find(42);
		(void)l1.count(42);
		(void)l1.lower_bound(42);
		(void)l2.lower_bound(42);
		(void)l1.upper_bound(42);
		(void)l2.upper_bound(42);
		(void)l1.equal_range(42);
		(void)l2.equal_range(42);
	}
	end_test();
}

// only test things that are different from orderedList
void map_test() {
	start_batch("map");
	constructTests();
	modifierTests();
	executionNonUsedTests();
}

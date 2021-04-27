//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"
#include <map>

template <class T, class PairCIt>
class multiset_tests {
private:
	int num;

	void compareSet(const T &list, const std::string &result) {
		std::stringstream ss;
		int i = 0;
		for (typename T::const_iterator it = list.begin(); it != list.end(); ++it) {
			if (i != 0)
				ss << "-";
			ss << "(" << *it << ")";
			++i;
		}
		if (ss.str() != result)
			fail_test();
	}

	void constructTests() {
		test("Basic constructor tests");
		{
			std::vector<int> vect;
			vect.push_back(5);
			vect.push_back(1);

			T l1;
			T l2(vect.begin(), vect.end());
			T l3;
			l3 = l2;
			T l4(l2);
			l4.insert(3);
			compareSet(l1, "");
			compareSet(l2, "(1)-(5)");
			compareSet(l3, "(1)-(5)");
			compareSet(l4, "(1)-(3)-(5)");
		}
		end_test();
	}

	void modifierTests() {
		test("insert iterator tests");
		{
			T l1;
			l1.insert(3);
			std::vector<int> vect;
			vect.push_back(5);
			vect.push_back(1);

			l1.insert(vect.begin(), vect.end());
			compareSet(l1, "(1)-(3)-(5)");
		}
		end_test();
		test("erase key tests");
		{
			T l1;
			l1.insert(l1.begin(), 3);
			l1.insert(5);
			l1.insert(5);
			l1.insert(9);
			compareSet(l1, "(3)-(5)-(5)-(9)");
			l1.erase(5);
			compareSet(l1, "(3)-(9)");
			l1.erase(l1.begin());
			compareSet(l1, "(9)");
			l1.erase(42);
			compareSet(l1, "(9)");
			l1.insert(5);
			l1.erase(l1.begin(), l1.end());
			compareSet(l1, "");
		}
		end_test();
	}

	void operationTests() {
		test("find/count tests");
		{
			T l1;
			const T &l2 = l1;
			T l3;
			const T &l4 = l3;
			l1.insert(3);
			l1.insert(5);
			l1.insert(5);
			l1.insert(9);
			compareSet(l1, "(3)-(5)-(5)-(9)");

			// find tests
			if (l2.find(9) != --(l2.end())) fail_test();
			if (l2.find(5) != ++(l2.begin())) fail_test();

			// empty/nonexistent find
			if (l3.find(5) != l4.end()) fail_test();
			if (l2.find(1) != l2.end()) fail_test();

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
			T l1;
			const T &l2 = l1;
			l1.insert(3);
			l1.insert(5);
			l1.insert(5);
			l1.insert(9);

			// lower bound tests
			if (l2.lower_bound(9) != --(l2.end())) fail_test();
			if (l2.lower_bound(5) != ++(l2.begin())) fail_test();
			if (l2.lower_bound(1) != l2.begin()) fail_test();

			// upper bound tests
			if (l2.upper_bound(9) != l2.end()) fail_test();
			if (l2.upper_bound(5) != ++ ++ ++(l2.begin())) fail_test();
			if (l2.upper_bound(1) != l2.begin()) fail_test();

			// equal range
			if (l2.equal_range(9) != PairCIt(--(l2.end()), l2.end()))
				fail_test();
			if (l2.equal_range(5) != PairCIt(++(l2.begin()), --(l2.end())))
				fail_test();
			if (l2.equal_range(1) != PairCIt(l2.begin(), l2.begin()))
				fail_test();
		}
		end_test();
	}

	// calling these functions will make the template functions run at least once, so they dont have runtime errors
	void executionNonUsedTests() {
		test("other tests");
		{
			T l1;
			const T &l2 = l1;
			T l3;
			// iterators
			(void) l1.begin();
			(void) l1.rbegin();
			(void) l1.end();
			(void) l1.rend();
			(void) l2.begin();
			(void) l2.rbegin();
			(void) l2.end();
			(void) l2.rend();

			// capacity
			(void) l1.empty();
			(void) l1.size();
			(void) l1.max_size();

			// modifiers
			l1.clear();
			l1.swap(l3);

			// observers
			(void) l1.key_comp();
			(void) l1.value_comp();
			(void) l1.get_allocator();
		}
		end_test();
	}

public:
	// only test things that are different from orderedList
	void run() {
		start_batch("multiset");
		constructTests();
		modifierTests();
		operationTests();
		executionNonUsedTests();
	}
};

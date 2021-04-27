//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"

template <class T, class PairType, class PairIt, class PairCIt>
class multimap_tests {
private:
	int num;

	void compareMap(T list, const std::string &result) {
		std::stringstream ss;
		int i = 0;
		for (typename T::iterator it = list.begin(); it != list.end(); ++it) {
			if (i != 0)
				ss << "-";
			ss << "(" << (*it).first << "," << (*it).second << ")";
			++i;
		}
		if (ss.str() != result)
			fail_test();
	}

	void constructTests() {
		test("Basic constructor tests");
		{
			std::vector<PairType > vect;
			vect.push_back(PairType(5, 42));
			vect.push_back(PairType(1, 69));

			T l1;
			T l2(vect.begin(), vect.end());
			T l3;
			l3 = l2;
			T l4(l2);
			l4.insert(PairType(3, 3));
			compareMap(l1, "");
			compareMap(l2, "(1,69)-(5,42)");
			compareMap(l3, "(1,69)-(5,42)");
			compareMap(l4, "(1,69)-(3,3)-(5,42)");
		}
		end_test();
	}

	void modifierTests() {
		test("insert iterator tests");
		{
			T l1;
			l1.insert(PairType(3, 3));
			std::vector<PairType > vect;
			vect.push_back(PairType(5, 42));
			vect.push_back(PairType(1, 69));

			l1.insert(vect.begin(), vect.end());
			compareMap(l1, "(1,69)-(3,3)-(5,42)");
		}
		end_test();
		test("erase key tests");
		{
			T l1;
			l1.insert(l1.begin(), PairType(3, 3));
			l1.insert(PairType(5, 42));
			l1.insert(PairType(5, 43));
			l1.insert(PairType(9, 9));
			compareMap(l1, "(3,3)-(5,42)-(5,43)-(9,9)");
			l1.erase(5);
			compareMap(l1, "(3,3)-(9,9)");
			l1.erase(l1.begin());
			compareMap(l1, "(9,9)");
			l1.erase(42);
			compareMap(l1, "(9,9)");
			l1.insert(PairType(5, 42));
			l1.erase(l1.begin(), l1.end());
			compareMap(l1, "");
		}
		end_test();
	}

	void operationTests() {
		test("find/count tests");
		{
			T l1;
			const T &l2 = l1;
			T l3;
			l1.insert(PairType(3, 3));
			l1.insert(PairType(5, 5));
			l1.insert(PairType(5, 6));
			l1.insert(PairType(9, 9));
			compareMap(l1, "(3,3)-(5,5)-(5,6)-(9,9)");

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
			T l1;
			const T &l2 = l1;
			l1.insert(PairType(3, 3));
			l1.insert(PairType(5, 5));
			l1.insert(PairType(5, 6));
			l1.insert(PairType(9, 9));

			// lower bound tests
			if (l1.lower_bound(9) != --(l1.end())) fail_test();
			if (l1.lower_bound(5) != ++(l1.begin())) fail_test();
			if (l1.lower_bound(1) != l1.end()) fail_test();
			if (l2.lower_bound(9) != --(l2.end())) fail_test();
			if (l2.lower_bound(5) != ++(l2.begin())) fail_test();
			if (l2.lower_bound(1) != l2.end()) fail_test();

			// upper bound tests
			if (l1.upper_bound(9) != l1.end()) fail_test();
			if (l1.upper_bound(5) != ++ ++ ++(l1.begin())) fail_test();
			if (l1.upper_bound(1) != l1.end()) fail_test();
			if (l2.upper_bound(9) != l2.end()) fail_test();
			if (l2.upper_bound(5) != ++ ++ ++(l2.begin())) fail_test();
			if (l2.upper_bound(1) != l2.end()) fail_test();


			// equal range
			if (l1.equal_range(9) !=PairIt(--(l1.end()), l1.end()))
				fail_test();
			if (l1.equal_range(5) != PairIt(++(l1.begin()), --(l1.end())))
				fail_test();
			if (l1.equal_range(1) != PairIt(l1.end(), l1.end()))
				fail_test();
			if (l2.equal_range(9) != PairCIt(--(l2.end()), l2.end()))
				fail_test();
			if (l2.equal_range(5) != PairCIt(++(l2.begin()), --(l2.end())))
				fail_test();
			if (l2.equal_range(1) != PairCIt(l2.end(), l2.end()))
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
		start_batch("multimap");
		constructTests();
		modifierTests();
		operationTests();
		executionNonUsedTests();
	}

};

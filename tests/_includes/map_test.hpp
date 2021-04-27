//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"

template <class T, class PairType, class PairBoolType>
class map_tests {
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
		test("unique insert tests");
		{
			T l1;
			// insert single
			PairBoolType ret = l1.insert(PairType(3, 3));
			if (ret.first != l1.begin() || ret.second != true) fail_test();
			ret = l1.insert(PairType(3, 69));
			if (ret.first != l1.begin() || ret.second != false) fail_test();

			// insert with hint
			typename T::iterator it = l1.insert(l1.begin(), PairType(6, -42));
			if (it != ++(l1.begin())) fail_test();

			// insert with iterator range
			std::vector<PairType > vect;
			vect.push_back(PairType(5, 42));
			vect.push_back(PairType(1, 69));
			l1.insert(vect.begin(), vect.end());

			// compare end result
			compareMap(l1, "(1,69)-(3,3)-(5,42)-(6,-42)");
		}
		end_test();
		test("operator access tests");
		{
			T l1;
			l1[5];
			compareMap(l1, "(5,0)");
			l1[5] = 42;
			compareMap(l1, "(5,42)");
			l1[1] = 1;
			compareMap(l1, "(1,1)-(5,42)");
		}
		end_test();
	}

	// calling these functions will make the template functions run at least once, so they dont have runtime errors
	// all of these are tested in multimap
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
			l1[1] = 1;
			l1.erase(l1.begin());
			l1.erase(l1.begin(), l1.end());
			l1.erase(42);
			l1.clear();
			l1.swap(l3);

			// observers
			(void) l1.key_comp();
			(void) l1.value_comp();
			(void) l1.get_allocator();

			// operations
			(void) l1.find(42);
			(void) l2.find(42);
			(void) l1.count(42);
			(void) l1.lower_bound(42);
			(void) l2.lower_bound(42);
			(void) l1.upper_bound(42);
			(void) l2.upper_bound(42);
			(void) l1.equal_range(42);
			(void) l2.equal_range(42);
		}
		end_test();
	}

public:
	// only test things that are different from orderedList
	void run() {
		start_batch("map");
		constructTests();
		modifierTests();
		executionNonUsedTests();
	}

};

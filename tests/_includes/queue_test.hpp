//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"

template <class T>
class queue_tests {
private:
	int num;

	void constructTests() {
		test("Basic constructor tests");
		{
			T l1;
			T l2(std::deque<int>(42, 5));
			if (!l1.empty()) fail_test();
			if (l2.size() != 42) fail_test();
		}
		end_test();
	}

	void accessTests() {
		test("empty/size tests");
		{
			T l1;
			if (!l1.empty()) fail_test();
			l1.push(1);
			if (l1.empty()) fail_test();
			l1.push(2);
			l1.push(3);
			if (l1.empty()) fail_test();
			if (l1.size() != 3) fail_test();
			l1.pop();
			l1.pop();
			l1.pop();
			if (l1.size() != 0) fail_test();
			if (!l1.empty()) fail_test();
		}
		end_test();
	}

	void modifierTests() {
		test("push/pop/front/back tests");
		{
			T l1;
			l1.push(1);
			l1.push(2);
			l1.push(3);
			if (l1.back() != 3 || l1.front() != 1) fail_test();
			l1.pop();
			if (l1.back() != 3 || l1.front() != 2) fail_test();
			l1.pop();
			l1.push(4);
			if (l1.back() != 4 || l1.front() != 3) fail_test();
			l1.pop();
			if (l1.back() != 4 || l1.front() != 4) fail_test();
			l1.pop();
		}
		end_test();
	}

	// calling these functions will make the template functions run at least once, so they dont have runtime errors
	// all of these are expected to work because of underlying containers
	void executionNonUsedTests() {
		test("other tests");
		{
			T l1;
			T l3;

			// comparisons
			(void) (l1 != l3);
			(void) (l1 == l3);
			(void) (l1 < l3);
			(void) (l1 <= l3);
			(void) (l1 > l3);
			(void) (l1 >= l3);
		}
		end_test();
	}

public:
	// only test things that are different from orderedList
	void run() {
		start_batch("queue");
		constructTests();
		modifierTests();
		accessTests();
		executionNonUsedTests();
	}

};

//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"

int 	num40 = 0;
#define test(str) start_test(str, ++num40)

static void constructTests() {
	test("Basic constructor tests");
	{
		ft::stack<int>	l1;
		ft::stack<int>	l2(std::deque<int>(42, 5));
		if (!l1.empty()) fail_test();
		if (l2.size() != 42) fail_test();
	}
	end_test();
}

static void accessTests() {
	test("empty/size tests");
	{
		ft::stack<int>	l1;
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

static void modifierTests() {
	test("push/pop tests");
	{
		ft::stack<int>	l1;
		l1.push(1);
		l1.push(2);
		l1.push(3);
		if (l1.top() != 3) fail_test();
		l1.pop();
		if (l1.top() != 2) fail_test();
		l1.pop();
		l1.push(4);
		if (l1.top() != 4) fail_test();
		l1.pop();
		if (l1.top() != 1) fail_test();
		l1.pop();
	}
	end_test();
}

// calling these functions will make the template functions run at least once, so they dont have runtime errors
// all of these are expected to work because of underlying containers
static void executionNonUsedTests() {
	test("other tests");
	{
		ft::stack<int> l1;
		ft::stack<int> l3;

		// comparisons
		(void)(l1!=l3);
		(void)(l1==l3);
		(void)(l1<l3);
		(void)(l1<=l3);
		(void)(l1>l3);
		(void)(l1>=l3);
	}
	end_test();
}

// only test things that are different from orderedList
void stack_test() {
	start_batch("stack");
	constructTests();
	modifierTests();
	accessTests();
	executionNonUsedTests();
}

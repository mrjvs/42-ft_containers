//
// Created by jelle on 4/23/2021.
//

#include "main.hpp"

int 	num = 0;
#define test(str) start_test(str, ++num)

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

template <class T>
static void compareList(const ft::list<T> &list, const std::string &result) {
	compareList<typename ft::list<T>::const_iterator>(list.begin(), list.end(), result);
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
		compareList(l1, "");
		compareList(l2, "1-2");
		compareList(l3, "42-42-42-42-42");
		compareList(l4, "1-2");
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

typedef struct {
	int data;
} s;

template<typename value_type>
struct testListNode {
	value_type					value;
	testListNode<value_type>	*next;
	testListNode<value_type>	*prev;
};

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
		s a = { .data = 1 };
		s b = { .data = 2 };
		s c = { .data = 3 };
		ft::list<int>	l1;
		l1.push_back(a.data);
		l1.push_back(b.data);
		l1.push_back(c.data);
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

		// value getters (* and ->)
		ft::list<s>	l3;
		l3.push_back(a);
		l3.push_back(b);
		l3.push_back(c);
		if (l3.begin()->data != 1) fail_test();
		if ((++(l3.begin()))->data != 2) fail_test();
		if ((*(l3.begin())).data != 1) fail_test();
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
		it = l1.end(); // set to end
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
		if (std::allocator<testListNode<int> >().max_size() != l1.max_size()) fail_test();
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

template<class T>
class isEven {
public:
	bool operator()(const T &a) {
		return a % 2 == 0;
	}
};

static void operationTests() {
	test("splice tests");
	{
		ft::list<int>	l1;
		ft::list<int>	l2;
		ft::list<int>	l3;
		l1.push_back(1);
		l1.push_back(3);
		l2.push_back(2);
		l2.push_back(4);
		l2.push_back(5);
		l2.push_back(6);
		l3.push_back(7);
		l3.push_back(8);
		l3.push_back(9);
		compareList<int>(l1, "1-3");
		compareList<int>(l2, "2-4-5-6");

		// splice single element
		l1.splice(++(l1.begin()), l2, l2.begin());
		compareList<int>(l1, "1-2-3");
		compareList<int>(l2, "4-5-6");

		// splice iterator range
		l1.splice(l1.end(), l2, l2.begin(), l2.end());
		compareList<int>(l1, "1-2-3-4-5-6");
		compareList<int>(l2, "");

		// splice entire list
		l1.splice(l1.end(), l3);
		compareList<int>(l1, "1-2-3-4-5-6-7-8-9");
		compareList<int>(l3, "");
	}
	end_test();
	test("remove/remove_if tests");
	{
		int tmplist[] = {1,2,3,4,5,6,7,8,9,10};
		ft::list<int>	l1(tmplist, tmplist+9);
		compareList<int>(l1, "1-2-3-4-5-6-7-8-9");

		// remove single element
		l1.remove(3);
		l1.remove(5);
		compareList<int>(l1, "1-2-4-6-7-8-9");

		// remove if
		l1.remove_if<isEven<int> >(isEven<int>());
		compareList<int>(l1, "1-7-9");
	}
	end_test();
	test("unique tests");
	{
		int tmplist[] = {1,2,3,3,4,5,5,1,6,7,8,9,10};
		ft::list<int>	l1(tmplist, tmplist+12);
		ft::list<int>	l2(l1);
		compareList<int>(l1, "1-2-3-3-4-5-5-1-6-7-8-9");
		compareList<int>(l2, "1-2-3-3-4-5-5-1-6-7-8-9");

		// make list unique
		l1.unique();
		compareList<int>(l1, "1-2-3-4-5-1-6-7-8-9");

		// make list unique with custom binary predicate
		l1.unique<ft::equal_to<int> >(ft::equal_to<int>());
		compareList<int>(l1, "1-2-3-4-5-1-6-7-8-9");
	}
	end_test();
	test("merge tests");
	{
		int tmplist[] = {1,2,6,7,9,10};
		int tmplist2[] = {-2,-1,3,4,5,10};
		int tmplist3[] = {8,10,11};
		ft::list<int>	l1(tmplist, tmplist+5);
		ft::list<int>	l2(tmplist2, tmplist2+5);
		ft::list<int>	l3(tmplist3, tmplist3+2);
		compareList<int>(l1, "1-2-6-7-9");
		compareList<int>(l2, "-2--1-3-4-5");
		compareList<int>(l3, "8-10");

		// merge a list
		l1.merge(l2);
		compareList<int>(l1, "-2--1-1-2-3-4-5-6-7-9");
		compareList<int>(l2, "");

		// merge a list with custom comparison object
		l1.merge<ft::less<int> >(l3, ft::less<int>());
		compareList<int>(l1, "-2--1-1-2-3-4-5-6-7-8-9-10");
		compareList<int>(l3, "");
	}
	end_test();
	test("sort tests");
	{
		int tmplist[] = {1,7,8,2,5,3,9,2,2,3,42,72,0};
		ft::list<int>	l1(tmplist, tmplist+12);
		ft::list<int>	l2(tmplist, tmplist+12);
		ft::list<int>	l3;
		l3.push_back(1);
		ft::list<int>	l4;
		compareList<int>(l1, "1-7-8-2-5-3-9-2-2-3-42-72");
		compareList<int>(l2, "1-7-8-2-5-3-9-2-2-3-42-72");

		// sort
		l1.sort();
		compareList<int>(l1, "1-2-2-2-3-3-5-7-8-9-42-72");
		l3.sort();
		compareList<int>(l3, "1");
		l4.sort();
		compareList<int>(l4, "");

		// sort with custom comparison object
		l2.sort<ft::less<int> >(ft::less<int>());
		compareList<int>(l2, "1-2-2-2-3-3-5-7-8-9-42-72");
	}
	end_test();
	test("reverse tests");
	{
		int tmplist[] = {1,7,8,2,5,3,9,2,2,3,42,72,0};
		ft::list<int>	l1(tmplist, tmplist+12);
		ft::list<int>	l2;
		ft::list<int>	l3;
		l2.push_back(1);
		compareList<int>(l1, "1-7-8-2-5-3-9-2-2-3-42-72");
		compareList<int>(l2, "1");
		compareList<int>(l3, "");

		// reverse even amount
		l1.reverse();
		compareList<int>(l1, "72-42-3-2-2-9-3-5-2-8-7-1");
		// reverse odd amount
		l1.pop_back();
		l1.reverse();
		compareList<int>(l1, "7-8-2-5-3-9-2-2-3-42-72");
		l2.reverse();
		compareList<int>(l2, "1");
		l3.reverse();
		compareList<int>(l3, "");
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

static void otherTests() {
	test("other tests");
	{
		ft::list<int>	l1;
		(void)l1.get_allocator();
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
	operationTests();
	nonMemberFunctions();
	otherTests();
}

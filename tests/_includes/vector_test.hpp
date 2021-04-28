//
// Created by jelle on 4/28/2021.
//

template <class T>
class vector_tests {
private:
	int 	num;

	template<class iterator>
	static void compareVector(iterator start, iterator last, const std::string &result) {
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

	static void compareVector(T &vec, const std::string &result) {
		compareVector<typename T::iterator>(vec.begin(), vec.end(), result);
	}

	void constructTests() {
		test("Basic constructor tests");
		{
			std::vector<int> vect;
			vect.push_back(1);
			vect.push_back(2);

			T l1;
			T l2(vect.begin(), vect.end());
			T l3((typename T::size_type)(5), 42);
			T l4(l2);
			compareVector(l1, "");
			compareVector(l2, "1-2");
			compareVector(l3, "42-42-42-42-42");
			compareVector(l4, "1-2");
		}
		end_test();
		test("Deep copy tests");
		{
			T l1;
			l1.push_back(1);
			l1.push_back(2);
			l1.push_back(3);
			T l2(l1);
			l1.push_back(4);
			l2.push_back(42);
			compareVector(l1, "1-2-3-4");
			compareVector(l2, "1-2-3-42");

			T l3;
			l3.push_back(420);
			compareVector(l3, "420");

			l3 = l1;
			l1.push_back(5);
			compareVector(l1, "1-2-3-4-5");
			compareVector(l3, "1-2-3-4");
		}
		end_test();
	}

	void iteratorTests() {
		test("iterator basic usage tests");
		{
			T l1;
			l1.push_back(1);
			l1.push_back(2);
			l1.push_back(3);
			const T &l2 = l1;

			compareVector<typename T::iterator>(l1.begin(), l1.end(), "1-2-3");
			compareVector<typename T::reverse_iterator>(l1.rbegin(), l1.rend(), "3-2-1");
			compareVector<typename T::const_iterator>(l2.begin(), l2.end(), "1-2-3");
			compareVector<typename T::const_reverse_iterator>(l2.rbegin(), l2.rend(), "3-2-1");
		}
		end_test();
		test("iterator increment/decrement");
		{
			int tmpList[] = {1,2,3,4,5,6,7,8,9,10};
			T l1(tmpList, tmpList+9);
			typename T::iterator it = l1.begin();

			// ++ and --
			if (*(it++) != 1) fail_test();
			if (*it != 2) fail_test();
			if (*(++it) != 3) fail_test();
			if (*(it--) != 3) fail_test();
			if (*(it) != 2) fail_test();
			if (*(--it) != 1) fail_test();

			// +=pos and +=neg
			it += 2;
			if (*it != 3) fail_test();
			it += -2;
			if (*it != 1) fail_test();
			if (*(it += 2) != 3) fail_test();

			// -=pos and -=neg
			it -= 2;
			if (*it != 1) fail_test();
			it -= -2;
			if (*it != 3) fail_test();
			if (*(it -= 2) != 1) fail_test();
			it += 2;
			if (*it != 3) fail_test();

			// it+n and it-n
			if (*(it + 2) != 5) fail_test();
			if (*(it + -2) != 1) fail_test();
			if (*(it - 2) != 1) fail_test();
			if (*(it - (-2)) != 5) fail_test();

			// it-it
			if ((it + 3) - (it) != 3) fail_test();
			if ((it) - (it+3) != -3) fail_test();

			// n+it
			if (*(3+it) != 6) fail_test();
			if (*(-1+it) != 2) fail_test();
		}
		end_test();
		test("iterator access tests");
		{
			int tmpList[] = {1,2,3,4,5,6,7,8,9,10};
			T l1(tmpList, tmpList+9);
			typename T::iterator it = l1.begin();
			it+=3;
			if (*it != 4) fail_test();
			if (it[0] != 4) fail_test();
			if (it[-1] != 3) fail_test();
			if (it[1] != 5) fail_test();
			if (it[-3] != 1) fail_test();
			if (it[3] != 7) fail_test();
		}
		end_test();
		test("iterator comparison tests");
		{
			int tmpList[] = {1,2,3,4,5,6,7,8,9,10};
			T l1(tmpList, tmpList+9);
			typename T::iterator start = l1.begin();
			typename T::iterator mid = l1.begin()+5;
			typename T::iterator mid2 = l1.begin()+5;
			typename T::iterator end = l1.begin()+7;

			// <
			if (!(start < mid)) fail_test();
			if (mid2 < mid) fail_test();
			if (end < mid) fail_test();

			// <=
			if (!(start <= mid)) fail_test();
			if (!(mid2 <= mid)) fail_test();
			if (end <= mid) fail_test();

			// >
			if (start > mid) fail_test();
			if (mid2 > mid) fail_test();
			if (!(end > mid)) fail_test();

			// >=
			if (start >= mid) fail_test();
			if (!(mid2 >= mid)) fail_test();
			if (!(end >= mid)) fail_test();

			// == and !=
			if (start == mid) fail_test();
			if (!(start != mid)) fail_test();
			if (!(mid2 == mid)) fail_test();
			if (mid2 != mid) fail_test();
		}
		end_test();
	}

	void modifierTests() {
		test("push/pop tests");
		{
			T l1;
			compareVector(l1, "");

			l1.push_back(1);
			l1.push_back(2);
			compareVector(l1, "1-2");

			l1.pop_back();
			compareVector(l1, "1");
			l1.push_back(4);
			compareVector(l1, "1-4");
			l1.pop_back();
			l1.pop_back();
			compareVector(l1, "");

			l1.push_back(1);
			l1.push_back(2);
			l1.push_back(3);
			l1.push_back(4);
			l1.push_back(5);
			compareVector(l1, "1-2-3-4-5");
		}
		end_test();
		test("swap/clear tests");
		{
			T l1;
			T l2;
			l1.push_back(1);
			l1.push_back(2);
			l1.push_back(3);

			l1.swap(l2);
			compareVector(l1, "");
			compareVector(l2, "1-2-3");

			l1.clear();
			l2.clear();
			compareVector(l1, "");
			compareVector(l2, "");
		}
		end_test();
		test("assign tests");
		{
			int tmpList[] = {1,2,3,4,5,6,7,8,9,10};
			T l1;
			T l2;
			l1.push_back(1);
			compareVector(l1, "1");
			compareVector(l2, "");

			l1.assign((typename T::size_type)5, 42);
			l2.assign((typename T::size_type)5, 42);
			compareVector(l1, "42-42-42-42-42");
			compareVector(l2, "42-42-42-42-42");

			l1.template assign<int*>(tmpList, tmpList+9);
			l2.template assign<int*>(tmpList, tmpList+9);
			compareVector(l1, "1-2-3-4-5-6-7-8-9");
			compareVector(l2, "1-2-3-4-5-6-7-8-9");
			l1.template assign<int*>(tmpList, tmpList);
			compareVector(l1, "");
		}
		end_test();
	}

	void capacitytests() {
		test("basic capacity tests");
		{
			T l1;
			if (!l1.empty()) fail_test();
			if (l1.size() != 0) fail_test();
			if (l1.capacity() != 0) fail_test();

			l1.push_back(1);
			l1.push_back(2);
			l1.push_back(3);
			if (l1.empty()) fail_test();
			if (l1.size() != 3) fail_test();
			if (l1.capacity() < 3) fail_test();
		}
		test("reserve tests");
		{
			T l1;
			l1.reserve(5);
			if (l1.capacity() < 5) fail_test();
			l1.reserve(3);
			if (l1.capacity() < 5) fail_test();
		}
		end_test();
		test("resize tests");
		{
			T l1((typename T::size_type)5, 42);
			compareVector(l1, "42-42-42-42-42");
			l1.resize(5, 5);
			compareVector(l1, "42-42-42-42-42");
			l1.resize(4, 5);
			compareVector(l1, "42-42-42-42");
			l1.resize(7, 5);
			compareVector(l1, "42-42-42-42-5-5-5");
			l1.resize(1, 5);
			compareVector(l1, "42");

			if (l1.capacity() < 7) fail_test();
		}
		end_test();
	}

	void accessTests() {
		test("basic access tests");
		{
			T l1;
			const T &l2 = l1;
			l1.push_back(1);
			l1.push_back(2);
			l1.push_back(3);

			if (l1[0] != 1 || l1[1] != 2 || l1[2] != 3) fail_test();
			if (l2[0] != 1 || l2[1] != 2 || l2[2] != 3) fail_test();
			if (l1.at(0) != 1 || l1.at(1) != 2 || l1.at(2) != 3) fail_test();
			if (l2.at(0) != 1 || l2.at(1) != 2 || l2.at(2) != 3) fail_test();

			if (l1.front() != 1 || l2.front() != 1) fail_test();
			if (l1.back() != 3 || l2.back() != 3) fail_test();
		}
		test("at() out_of_range tests");
		{
			T l1;
			const T &l2 = l1;
			l1.push_back(1);
			l1.push_back(2);
			l1.push_back(3);

			try {
				l1.at(4);
				fail_test();
			} catch (const std::out_of_range &e) {}
			try {
				l2.at(4);
				fail_test();
			} catch (const std::out_of_range &e) {}

			l1.clear();

			try {
				l1.at(0);
				fail_test();
			} catch (const std::out_of_range &e) {}
			try {
				l2.at(0);
				fail_test();
			} catch (const std::out_of_range &e) {}
		}
		end_test();
	}

	void nonUsedFunctions() {
		test("other tests");
		{
			T l1;

			(void)l1.get_allocator();
		}
		end_test();
	}

public:

	void run() {
		start_batch("vector");
		constructTests();
		modifierTests();
		capacitytests();
		accessTests();
		iteratorTests();
		nonUsedFunctions();
	}

};

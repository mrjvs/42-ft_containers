//
// Created by jelle on 4/28/2021.
//

template <class T>
class vector_tests {
private:
	int 	num;

	static void compareVector(T &vec, const std::string &result) {
		std::stringstream ss;
		int i = 0;
		for (typename T::iterator it = vec.begin(); it != vec.end(); ++it) {
			if (i != 0)
				ss << "-";
			ss << *it;
			++i;
		}
		if (ss.str() != result)
			fail_test();
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
		test("iterator usage tests");
		{
			// TODO iterator tests
			// TODO random access tests
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
		nonUsedFunctions();
	}

};
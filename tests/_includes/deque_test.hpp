//
// Created by jelle on 4/28/2021.
//

using namespace std;
using namespace ft;

template <class T>
class deque_tests {
private:
	int 	num;

	template<class iterator>
	static void compareDeque(iterator start, iterator last, const std::string &result) {
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

	static void compareDeque(T &vec, const std::string &result) {
		compareDeque<typename T::iterator>(vec.begin(), vec.end(), result);
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
			compareDeque(l1, "");
			compareDeque(l2, "1-2");
			compareDeque(l3, "42-42-42-42-42");
			compareDeque(l4, "1-2");
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
			compareDeque(l1, "1-2-3-4");
			compareDeque(l2, "1-2-3-42");

			T l3;
			l3.push_back(420);
			compareDeque(l3, "420");

			l3 = l1;
			l1.push_back(5);
			compareDeque(l1, "1-2-3-4-5");
			compareDeque(l3, "1-2-3-4");
		}
		end_test();
	}

	void modifierTests() {
		test("pushback/popback tests");
		{
			T l1;
			compareDeque(l1, "");

			l1.push_back(1);
			l1.push_back(2);
			compareDeque(l1, "1-2");

			l1.pop_back();
			compareDeque(l1, "1");
			l1.push_back(4);
			compareDeque(l1, "1-4");
			l1.pop_back();
			l1.pop_back();
			compareDeque(l1, "");

			l1.push_back(1);
			l1.push_back(2);
			l1.push_back(3);
			l1.push_back(4);
			l1.push_back(5);
			compareDeque(l1, "1-2-3-4-5");
		}
		end_test();
		test("pushfront/popfront tests");
		{
			T l1;
			compareDeque(l1, "");

			l1.push_front(1);
			l1.push_front(2);
			compareDeque(l1, "2-1");

			l1.pop_front();
			compareDeque(l1, "1");
			l1.push_front(4);
			compareDeque(l1, "4-1");
			l1.pop_front();
			l1.pop_front();
			compareDeque(l1, "");

			l1.push_front(1);
			l1.push_front(2);
			l1.push_front(3);
			l1.push_front(4);
			l1.push_front(5);
			compareDeque(l1, "5-4-3-2-1");
			l1.pop_front();
			compareDeque(l1, "4-3-2-1");
		}
		end_test();
	}

	void nonUsedFunctions() {
		test("other tests");
		{
			std::vector<int> ints;
			ints.push_back(1);
			ints.push_back(2);
			ints.push_back(3);
			T l1;
			const T &l2 = l1;
			T l3;

			// iterators
			(void)l1.begin();
			(void)l2.begin();
			(void)l1.rbegin();
			(void)l2.rbegin();
			(void)l1.end();
			(void)l2.end();
			(void)l1.rend();
			(void)l2.rend();

			// capacity
			(void)l1.size();
			(void)l1.max_size();
			(void)l1.empty();
			l1.resize(5, 42);

			// access
			(void)l1[1];
			(void)l2[1];
			(void)l1.at(0);
			(void)l2.at(0);
			(void)l1.front();
			(void)l2.front();
			(void)l1.back();
			(void)l2.back();

			// modifiers
			l1.assign((typename T::size_type)3, 3);
			l1.assign(ints.begin(), ints.end());
			(void)l1.insert(l1.begin(), 5);
			l1.insert(l1.begin(), (typename T::size_type)2, 42);
			l1.insert(l1.begin(), ints.begin(), ints.end());
			(void)l1.erase(l1.begin());
			(void)l1.erase(l1.begin(), l1.end());
			l1.swap(l3);
			l1.clear();

			// non member functions
			swap(l1, l3);

			// observers
			(void)l1.get_allocator();
		}
		end_test();
	}

public:

	void run() {
		start_batch("deque");
		constructTests();
		modifierTests();
		nonUsedFunctions();
	}

};

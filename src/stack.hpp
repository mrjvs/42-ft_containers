//
// Created by jelle on 4/26/2021.
//

#ifndef STACK_HPP
#define STACK_HPP

#include <deque> // for default container

namespace ft {

	template <class T, class Container = std::deque<T> > class stack {
	public:
		typedef T								value_type;
		typedef Container						container_type;
		typedef typename Container::size_type	size_type;

	private:
		container_type _data;

	public:
		explicit stack(const container_type& ctnr = container_type()): _data(ctnr) {}

		bool empty() const {
			return _data.empty();
		}
		size_type size() const {
			return _data.size();
		}

		// access
		value_type &top() {
			return _data.back();
		}
		const value_type &top() const {
			return _data.back();
		}

		// modifier
		void push(const value_type &val) {
			_data.push_back(val);
		}
		void pop() {
			_data.pop_back();
		}

		// friend operators (yes all of them)
		template <class A, class B> friend bool operator!=(const stack<A,B>& lhs, const stack<A,B>& rhs);
		template <class A, class B> friend bool operator==(const stack<A,B>& lhs, const stack<A,B>& rhs);
		template <class A, class B> friend bool operator<(const stack<A,B>& lhs, const stack<A,B>& rhs);
		template <class A, class B> friend bool operator<=(const stack<A,B>& lhs, const stack<A,B>& rhs);
		template <class A, class B> friend bool operator>(const stack<A,B>& lhs, const stack<A,B>& rhs);
		template <class A, class B> friend bool operator>=(const stack<A,B>& lhs, const stack<A,B>& rhs);
	};

	// comparison operators
	template <class T, class Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._data == rhs._data;
	}
	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._data != rhs._data;
	}
	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._data < rhs._data;
	}
	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._data <= rhs._data;
	}
	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._data > rhs._data;
	}
	template <class T, class Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs._data >= rhs._data;
	}

}

#endif //STACK_HPP

//
// Created by jelle on 4/26/2021.
//

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <deque> // for default container

namespace ft {

	template <class T, class Container = std::deque<T> > class queue {
	public:
		typedef T								value_type;
		typedef Container						container_type;
		typedef typename Container::size_type	size_type;

	private:
		container_type _data;

	public:
		explicit queue(const container_type& ctnr = container_type()): _data(ctnr) {}

		bool empty() const {
			return _data.empty();
		}
		size_type size() const {
			return _data.size();
		}

		// access
		value_type &front() {
			return _data.front();
		}
		const value_type &front() const {
			return _data.front();
		}
		value_type &back() {
			return _data.back();
		}
		const value_type &back() const {
			return _data.back();
		}

		// modifier
		void push(const value_type &val) {
			_data.push_back(val);
		}
		void pop() {
			_data.pop_front();
		}

		// friend operators (yes all of them)
		template <class A, class B> friend bool operator!=(const queue<A,B>& lhs, const queue<A,B>& rhs);
		template <class A, class B> friend bool operator==(const queue<A,B>& lhs, const queue<A,B>& rhs);
		template <class A, class B> friend bool operator<(const queue<A,B>& lhs, const queue<A,B>& rhs);
		template <class A, class B> friend bool operator<=(const queue<A,B>& lhs, const queue<A,B>& rhs);
		template <class A, class B> friend bool operator>(const queue<A,B>& lhs, const queue<A,B>& rhs);
		template <class A, class B> friend bool operator>=(const queue<A,B>& lhs, const queue<A,B>& rhs);
	};

	// comparison operators
	template <class T, class Container>
	bool operator==(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return lhs._data == rhs._data;
	}
	template <class T, class Container>
	bool operator!=(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return lhs._data != rhs._data;
	}
	template <class T, class Container>
	bool operator<(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return lhs._data < rhs._data;
	}
	template <class T, class Container>
	bool operator<=(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return lhs._data <= rhs._data;
	}
	template <class T, class Container>
	bool operator>(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return lhs._data > rhs._data;
	}
	template <class T, class Container>
	bool operator>=(const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return lhs._data >= rhs._data;
	}

}

#endif //QUEUE_HPP

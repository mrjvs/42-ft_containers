//
// Created by jelle on 4/28/2021.
//

#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "vector.hpp"

namespace ft {

	template <class T, class Alloc = std::allocator<T> >
	class deque {
	private:
		typedef typename ft::vector<T, Alloc>	list_type;
		list_type	_list;

	public:
		typedef typename list_type::value_type				value_type;
		typedef typename list_type::allocator_type			allocator_type;
		typedef typename list_type::reference				reference;
		typedef typename list_type::const_reference			const_reference;
		typedef typename list_type::pointer					pointer;
		typedef typename list_type::const_pointer			const_pointer;
		typedef typename list_type::difference_type			difference_type;
		typedef typename list_type::size_type				size_type;
		typedef typename list_type::iterator				iterator;
		typedef typename list_type::const_iterator			const_iterator;
		typedef typename list_type::reverse_iterator		reverse_iterator;
		typedef typename list_type::const_reverse_iterator	const_reverse_iterator;

		// constructors & destructor
		explicit deque(const allocator_type& alloc = allocator_type()): _list(alloc) {}
		explicit deque(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _list(n, val, alloc) {}
		template <class InputIterator>
		deque(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()): _list(first, last, alloc) {}
		deque(const deque& x): _list(x._list) {}
		~deque() {}

		// iterators
		iterator begin() { return  _list.begin(); }
		reverse_iterator rbegin() { return _list.rbegin(); }
		const_iterator begin() const { return _list.begin(); }
		const_reverse_iterator rbegin() const { return _list.rbegin(); }
		iterator end() { return _list.end(); }
		reverse_iterator rend() { return _list.rend(); }
		const_iterator end() const { return _list.end(); }
		const_reverse_iterator rend() const { return _list.rend(); }

		// capacity
		size_type size() const {
			return _list.size();
		}
		size_type max_size() const {
			return _list.max_size();
		}
		void resize(size_type n, value_type val = value_type()) {
			_list.resize(n, val);
		}
		bool empty() const {
			return _list.empty();
		}

		// access
		reference operator[](size_type n) {
			return _list[n];
		}
		const_reference operator[](size_type n) const {
			return _list[n];
		}
		reference at(size_type n) {
			return _list.at(n);
		}
		const_reference at(size_type n) const {
			return _list.at(n);
		}
		reference front() {
			return _list.front();
		}
		const_reference front() const {
			return _list.front();
		}
		reference back() {
			return _list.back();
		}
		const_reference back() const {
			return _list.back();
		}

		// modifiers
		void assign(size_type n, const value_type& val) {
			_list.assign(n, val);
		}
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last) {
			_list.assign(first, last);
		}
		void push_back(const value_type& val) {
			_list.push_back(val);
		}
		void pop_back() {
			_list.pop_back();
		}
		void push_front(const value_type& val) {
			insert(begin(), val);
		}
		void pop_front() {
			erase(begin());
		}
		iterator insert(iterator position, const value_type& val) {
			return _list.insert(position, val);
		}
		void insert(iterator position, size_type n, const value_type& val) {
			return _list.insert(position, n, val);
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last) {
			return _list.insert(position, first, last);
		}
		iterator erase(iterator position) {
			return _list.erase(position);
		}
		iterator erase(iterator first, iterator last) {
			return _list.erase(first, last);
		}
		void swap(deque& x) {
			_list.swap(x._list);
		}
		void clear() {
			_list.clear();
		}

		// observers
		allocator_type get_allocator() const {
			return _list.get_allocator();
		}
	};

	// non member functions
	template <class T, class Alloc>
	void swap(deque<T,Alloc>& x, deque<T,Alloc>& y) {
		x.swap(y);
	}

	// TODO comparisons
}

#endif //DEQUE_HPP

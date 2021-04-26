//
// Created by jelle on 4/25/2021.
//

#ifndef MULTISET_HPP
#define MULTISET_HPP

#include "orderedList.hpp"

namespace ft {

	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class multiset {
	public:
		typedef T														key_type;
		typedef T														value_type;
		typedef Compare													key_compare;
		typedef Compare													value_compare;
		typedef Alloc													allocator_type;

	private:
		typedef orderedList<value_type, value_compare, allocator_type>	list_type;
		list_type	_list;

	public:
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
		explicit multiset(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _list(comp, alloc) {}
		template <class InputIterator>
		multiset(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _list(comp, alloc) {
			insert(first, last);
		}
		multiset(const multiset& x): _list(x._list) {}
		~multiset() {}

		// operators
		multiset	&operator=(const multiset& x) {
			if (&x == this)
				return *this;
			_list = x._list;
			return *this;
		};

		// iterators
		iterator begin() { return _list.begin(); }
		reverse_iterator rbegin() { return _list.rbegin(); }
		const_iterator begin() const { return _list.begin(); }
		const_reverse_iterator rbegin() const { return _list.rbegin(); }
		iterator end() { return _list.end(); }
		reverse_iterator rend() { return _list.rend(); }
		const_iterator end() const { return _list.end(); }
		const_reverse_iterator rend() const { return _list.rend(); }

		// capacity
		bool empty() const {
			return _list.empty();
		}
		size_type size() const {
			return _list.size();
		}
		size_type max_size() const {
			return _list.max_size();
		}

		// modifiers
		iterator insert(const value_type& val) {
			return _list.insert(val);
		}

		iterator insert(iterator position, const value_type& val) {
			(void)position; // dont use binary search so this is useless
			return _list.insert(val);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			for (; first != last; ++first)
				_list.insert(*first);
		}

		void erase(iterator position) {
			_list.erase(position);
		}
		size_type erase(const value_type& val) {
			std::pair<iterator, iterator> its = _list.equal_range(val);
			iterator it = its.first;
			size_type i = 0;
			while (it != its.second) {
				it = _list.erase(it);
				i++;
			}
			return i;
		}
		void erase(iterator first, iterator last) {
			while (first != last)
				first = _list.erase(first);
		}
		void swap(multiset &x) {
			_list.swap(x._list);
		}
		void clear() {
			_list.clear();
		}

		// observers
		key_compare key_comp() const {
			return _list.value_comp();
		}
		value_compare value_comp() const {
			return _list.value_comp();
		}
		allocator_type get_allocator() const {
			return _list.get_allocator();
		}

		// operations
		const_iterator find(const value_type& val) const {
			return _list.get(val);
		}
		size_type count(const value_type& val) const {
			std::pair<const_iterator, const_iterator> its = _list.equal_range(val);
			size_type i = 0;
			for (const_iterator it = its.first; it != its.second; ++it)
				++i;
			return i;
		}
		const_iterator lower_bound(const value_type& val) const {
			return _list.lower_bound(val);
		}
		const_iterator upper_bound(const value_type& val) const {
			return _list.upper_bound(val);
		}
		std::pair<const_iterator,const_iterator> equal_range(const value_type& val) const {
			return _list.equal_range(val);
		}
	};

}

#endif //MULTISET_HPP

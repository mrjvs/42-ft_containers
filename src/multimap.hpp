//
// Created by jelle on 4/25/2021.
//

#ifndef MULTIMAP_HPP
#define MULTIMAP_HPP

#include "orderedList.hpp"

namespace ft {

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
	class multimap {

	private:
		template <class Type, class CompareObj>
		class value_compare_struct {
		private:
			CompareObj _compare;

		public:
			value_compare_struct(const CompareObj &comp = CompareObj()): _compare(comp) {}
			value_compare_struct(const value_compare_struct &x): _compare(x._compare) {}
			bool operator() (const Type& x, const Type& y) const {
				return _compare(x.first, y.first);
			}
		};

	public:
		typedef Key														key_type;
		typedef T														mapped_type;
		typedef typename std::pair<const key_type, mapped_type>			value_type;
		typedef Compare													key_compare;
		typedef value_compare_struct<value_type, key_compare>			value_compare;
		typedef Alloc													allocator_type;

	private:
		value_type	createKeySearch(const key_type &key) const {
			return value_type(key, mapped_type());
		}
		typedef orderedList<value_type, value_compare, allocator_type>	list_type;
		list_type	_list;
		key_compare _compare;
		allocator_type _alloc;
		value_compare _valueCompare;

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
		explicit multimap (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _list(), _compare(comp), _alloc(alloc), _valueCompare(_compare) {}
		template <class InputIterator>
		multimap (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _list(), _compare(comp), _alloc(alloc), _valueCompare(_compare) {
			insert(first, last);
		}
		multimap(const multimap& x): _list(x._list), _compare(x._compare), _alloc(x._alloc), _valueCompare(x._valueCompare) {}
		~multimap() {}

		// operators
		multimap	&operator=(const multimap& x) {
			if (&x == this)
				return *this;
			_compare = x._compare;
			_alloc = x._alloc;
			_valueCompare = x._valueCompare;
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
		size_type erase(const key_type& k) {
			std::pair<iterator, iterator> its = _list.equal_range(createKeySearch(k));
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
		void swap(multimap &x) {
			_list.swap(x._list);
		}
		void clear() {
			_list.clear();
		}

		// observers
		key_compare key_comp() const {
			return _compare;
		}
		value_compare value_comp() const {
			return _valueCompare;
		}

		// operations
		iterator find(const key_type& k) {
			return _list.get(createKeySearch(k));
		}
		const_iterator find(const key_type& k) const {
			return _list.get(createKeySearch(k));
		}
		size_type count(const key_type& k) const {
			std::pair<const_iterator, const_iterator> its = _list.equal_range(createKeySearch(k));
			size_type i = 0;
			for (const_iterator it = its.first; it != its.second; ++it)
				++i;
			return i;
		}
		iterator lower_bound(const key_type& k) {
			return _list.lower_bound(createKeySearch(k));
		}
		const_iterator lower_bound(const key_type& k) const {
			return _list.lower_bound(createKeySearch(k));
		}
		iterator upper_bound(const key_type& k) {
			return _list.upper_bound(createKeySearch(k));
		}
		const_iterator upper_bound(const key_type& k) const {
			return _list.upper_bound(createKeySearch(k));
		}
		std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
			return _list.equal_range(createKeySearch(k));
		}
		std::pair<iterator,iterator> equal_range(const key_type& k) {
			return _list.equal_range(createKeySearch(k));
		}
	};

}

#endif //MULTIMAP_HPP

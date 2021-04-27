//
// Created by jelle on 4/24/2021.
//

#ifndef ORDEREDLIST_HPP
#define ORDEREDLIST_HPP

#include "list.hpp"
#include "pair.hpp"

namespace ft {

	// class used as backend for any sorted data structures (like map & set)
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> > class orderedList {
	private:
		typedef typename ft::list<T, Alloc>					list_type;
		list_type	_list;

	public:
		typedef Compare										value_compare;
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

	private:
		value_compare _compare;

	public:
		// constructors & destructor
		explicit orderedList(const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type()): _list(alloc), _compare(comp) {}
		orderedList(const orderedList& x): _list(x._list), _compare(x._compare) {}
		~orderedList() {}

		// operators
		orderedList	&operator=(const orderedList& x) {
			if (&x == this)
				return *this;
			_compare = x._compare;
			_list = x._list;
			return *this;
		};

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
		bool empty() const {
			return _list.empty();
		}
		size_type size() const {
			return _list.size();
		}
		size_type max_size() const {
			return _list.max_size();
		}

		// access
		reference		front() {
			return _list.front();
		}
		const_reference	front() const {
			return _list.front();
		}
		reference		back() {
			return _list.back();
		}
		const_reference	back() const {
			return _list.back();
		}

		// access
		iterator upper_bound(const value_type& k) {
			for (iterator it = begin(); it != end(); ++it) {
				if (_compare(k, *it))
					return it;
			}
			return end();
		}
		const_iterator upper_bound(const value_type& k) const {
			for (const_iterator it = begin(); it != end(); ++it) {
				if (_compare(k, *it))
					return it;
			}
			return end();
		}
		iterator lower_bound(const value_type& k) {
			for (iterator it = begin(); it != end(); ++it) {
				if (!_compare(*it, k))
					return it;
			}
			return end();
		}
		const_iterator lower_bound(const value_type& k) const {
			for (const_iterator it = begin(); it != end(); ++it) {
				if (!_compare(*it, k))
					return it;
			}
			return end();
		}
		ft::pair<iterator,iterator>	equal_range(const value_type &key) {
			return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		}
		ft::pair<const_iterator,const_iterator>	equal_range(const value_type &key) const {
			return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
		}
		iterator get(const value_type &key) {
			iterator out = lower_bound(key);
			// if end or not equal
			if (out == end() || !(!_compare(*out, key) && !_compare(key, *out)))
				return end();
			return out;
		}
		const_iterator get(const value_type &key) const {
			const_iterator out = lower_bound(key);
			// if end or not equal
			if (out == end() || !(!_compare(*out, key) && !_compare(key, *out)))
				return end();
			return out;
		}
		bool has(const value_type &key) const {
			return get(key) != end();
		}

		// modifiers
		void	clear() {
			_list.clear();
		}
		iterator erase(iterator position) {
			return _list.erase(position);
		}
		iterator insert(const value_type &item) {
			return _list.insert(upper_bound(item), item);
		}
		void swap(orderedList &x) {
			_list.swap(x._list);
		}

		// observers
		value_compare value_comp() const {
			return _compare;
		}
		allocator_type get_allocator() const {
			return _list.get_allocator();
		}
	};

}

#endif //ORDEREDLIST_HPP

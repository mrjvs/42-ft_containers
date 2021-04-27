//
// Created by jelle on 4/25/2021.
//

#ifndef SET_HPP
#define SET_HPP

#include "multiset.hpp"

namespace ft {

	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set {
	private:
		typedef multiset<T, Compare, Alloc>	list_type;
		list_type	_set;

	public:
		typedef typename list_type::key_type										key_type;
		typedef typename list_type::value_type										value_type;
		typedef typename list_type::key_compare										key_compare;
		typedef typename list_type::value_compare									value_compare;
		typedef typename list_type::allocator_type									allocator_type;
		typedef typename list_type::reference										reference;
		typedef typename list_type::const_reference									const_reference;
		typedef typename list_type::pointer											pointer;
		typedef typename list_type::const_pointer									const_pointer;
		typedef typename list_type::difference_type									difference_type;
		typedef typename list_type::size_type										size_type;
		typedef typename list_type::iterator										iterator;
		typedef typename list_type::const_iterator									const_iterator;
		typedef typename list_type::reverse_iterator								reverse_iterator;
		typedef typename list_type::const_reverse_iterator							const_reverse_iterator;

	private:
		iterator _find(const value_type &val) {
			for (iterator it = begin(); it != end(); ++it) {
				if (!_set.value_comp()(val, *it) && !_set.value_comp()(*it, val))
					return it;
			}
			return end();
		}

	public:

		// constructors & destructor
		explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _set(comp, alloc) {}
		template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _set(comp, alloc) {
			insert(first, last);
		}
		set(const set& x): _set(x._set) {}
		~set() {}

		// operators
		set	&operator=(const set& x) {
			if (&x == this)
				return *this;
			_set = x._set;
			return *this;
		};

		// iterators
		iterator begin() { return _set.begin(); }
		reverse_iterator rbegin() { return _set.rbegin(); }
		const_iterator begin() const { return _set.begin(); }
		const_reverse_iterator rbegin() const { return _set.rbegin(); }
		iterator end() { return _set.end(); }
		reverse_iterator rend() { return _set.rend(); }
		const_iterator end() const { return _set.end(); }
		const_reverse_iterator rend() const { return _set.rend(); }

		// capacity
		bool empty() const {
			return _set.empty();
		}
		size_type size() const {
			return _set.size();
		}
		size_type max_size() const {
			return _set.max_size();
		}

		// modifiers
		ft::pair<iterator,bool>	insert(const value_type& val) {
			iterator it = _find(val);
			// return existing value
			if (it != end())
				return ft::pair<iterator,bool>(it,false);

			// insert new value
			return ft::pair<iterator,bool>(_set.insert(val),true);
		}
		iterator insert(iterator position, const value_type& val) {
			(void)position; // no binary search, so we ignore value
			return insert(val).first;
		}
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			for (; first != last; ++first)
				insert(*first);
		}
		void erase(iterator position) {
			_set.erase(position);
		}
		size_type erase(const value_type& val) {
			return _set.erase(val);
		}
		void erase(iterator first, iterator last) {
			_set.erase(first, last);
		}
		void swap(set &x) {
			_set.swap(x._set);
		}
		void clear() {
			_set.clear();
		}

		// observers
		key_compare key_comp() const {
			return _set.key_comp();
		}
		value_compare value_comp() const {
			return _set.value_comp();
		}
		allocator_type get_allocator() const {
			return _set.get_allocator();
		}

		// operations
		const_iterator find(const value_type& val) const {
			return _set.find(val);
		}
		size_type count(const value_type& val) const {
			return _set.count(val);
		}
		const_iterator lower_bound(const value_type& val) const {
			return _set.lower_bound(val);
		}
		const_iterator upper_bound(const value_type& val) const {
			return _set.upper_bound(val);
		}
		ft::pair<const_iterator,const_iterator> equal_range(const value_type& val) const {
			return _set.equal_range(val);
		}
	};

}

#endif //SET_HPP

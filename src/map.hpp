//
// Created by jelle on 4/25/2021.
//

#ifndef MAP_HPP
#define MAP_HPP

#include "multimap.hpp"

namespace ft {

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {
	private:
		typedef multimap<Key, T, Compare, Alloc>						list_type;
		list_type	_map;

	public:
		typedef typename list_type::key_type										key_type;
		typedef typename list_type::mapped_type										mapped_type;
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

	public:

		// constructors & destructor
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _map(comp, alloc) {}
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _map(comp, alloc) {
			insert(first, last);
		}
		map(const map& x): _map(x._map) {}
		~map() {}

		// operators
		map	&operator=(const map& x) {
			if (&x == this)
				return *this;
			_map = x._map;
			return *this;
		};

		// iterators
		iterator begin() { return _map.begin(); }
		reverse_iterator rbegin() { return _map.rbegin(); }
		const_iterator begin() const { return _map.begin(); }
		const_reverse_iterator rbegin() const { return _map.rbegin(); }
		iterator end() { return _map.end(); }
		reverse_iterator rend() { return _map.rend(); }
		const_iterator end() const { return _map.end(); }
		const_reverse_iterator rend() const { return _map.rend(); }

		// capacity
		bool empty() const {
			return _map.empty();
		}
		size_type size() const {
			return _map.size();
		}
		size_type max_size() const {
			return _map.max_size();
		}

		// access
		mapped_type& operator[](const key_type& k) {
			// call insert, get pair from iterator and return type
			return (*((insert(value_type(k, mapped_type()))).first)).second;
		}

		// modifiers
		ft::pair<iterator,bool>	insert(const value_type& val) {
			iterator it = _map.find(val.first);
			// return existing value
			if (it != end())
				return ft::pair<iterator,bool>(it,false);

			// insert new value
			return ft::pair<iterator,bool>(_map.insert(val),true);
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
			_map.erase(position);
		}
		size_type erase(const key_type& k) {
			return _map.erase(k);
		}
		void erase(iterator first, iterator last) {
			_map.erase(first, last);
		}
		void swap(map &x) {
			_map.swap(x._map);
		}
		void clear() {
			_map.clear();
		}

		// observers
		key_compare key_comp() const {
			return _map.key_comp();
		}
		value_compare value_comp() const {
			return _map.value_comp();
		}
		allocator_type get_allocator() const {
			return _map.get_allocator();
		}

		// operations
		iterator find(const key_type& k) {
			return _map.find(k);
		}
		const_iterator find(const key_type& k) const {
			return _map.find(k);
		}
		size_type count(const key_type& k) const {
			return _map.count(k);
		}
		iterator lower_bound(const key_type& k) {
			return _map.lower_bound(k);
		}
		const_iterator lower_bound(const key_type& k) const {
			return _map.lower_bound(k);
		}
		iterator upper_bound(const key_type& k) {
			return _map.upper_bound(k);
		}
		const_iterator upper_bound(const key_type& k) const {
			return _map.upper_bound(k);
		}
		ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
			return _map.equal_range(k);
		}
		ft::pair<iterator,iterator> equal_range(const key_type& k) {
			return _map.equal_range(k);
		}
	};

}

#endif //MAP_HPP

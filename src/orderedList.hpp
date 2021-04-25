//
// Created by jelle on 4/24/2021.
//

#ifndef ORDEREDLIST_HPP
#define ORDEREDLIST_HPP

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
		allocator_type _alloc;
		value_compare _compare;

	public:
		// constructors & destructor
		explicit orderedList(const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type()): _list(), _alloc(alloc), _compare(comp) {}
		orderedList(const orderedList& x): _list(x._list), _alloc(x._alloc), _compare(x._compare) {}
		~orderedList() {}

		// operators
		orderedList	&operator=(const orderedList& x) {
			if (&x == this)
				return *this;
			_alloc = x._alloc;
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
			bool foundEqual = false;
			for (iterator it = begin(); it != end(); ++it) {
				if (!foundEqual && !_compare(k, *it) && !_compare(*it, k))
					foundEqual = true;
				if (foundEqual && !(!_compare(k, *it) && !_compare(*it, k)))
					return it;
			}
			return end();
		}
		const_iterator upper_bound(const value_type& k) const {
			bool foundEqual = false;
			for (const_iterator it = begin(); it != end(); ++it) {
				if (!foundEqual && !_compare(k, *it) && !_compare(*it, k))
					foundEqual = true;
				if (foundEqual && !(!_compare(k, *it) && !_compare(*it, k)))
					return it;
			}
			return end();
		}
		iterator lower_bound(const value_type& k) {
			for (iterator it = begin(); it != end(); ++it) {
				if (!_compare(k, *it) && !_compare(*it, k))
					return it;
			}
			return end();
		}
		const_iterator lower_bound(const value_type& k) const {
			for (const_iterator it = begin(); it != end(); ++it) {
				if (!_compare(k, *it) && !_compare(*it, k))
					return it;
			}
			return end();
		}
		std::pair<iterator,iterator>	equal_range(const value_type &key) {
			return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		}
		std::pair<const_iterator,const_iterator>	equal_range(const value_type &key) const {
			return std::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
		}
		iterator get(const value_type &key) {
			return equal_range(key).first;
		}
		const_iterator get(const value_type &key) const {
			return equal_range(key).first;
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
			for (iterator it = begin(); it != end(); ++it) {
				if (!_compare(*it, item)) {
					// push front if beginning, otherwise insert at position
					if (it == begin()) {
						_list.push_front(item);
						return _list.begin();
					}
					return _list.insert(--it, item);
				}
			}
			// push back if end
			_list.push_back(item);
			return --(end());
		}
		void swap(orderedList &x) {
			_list.swap(x._list);
		}
	};

}

#endif //ORDEREDLIST_HPP

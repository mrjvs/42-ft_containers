//
// Created by jelle on 4/23/2021.
//

#ifndef LIST_HPP
#define LIST_HPP

#include <memory> // allocator
#include <iterator> // iterator category
#include <limits> // max size

namespace ft {

	// properties: sequence, double linked list, allocator
	template <class T, class Alloc = std::allocator<T> > class list {
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

	private:
		template<typename value_type>
		class listNode {
		public:
			value_type				value;
			listNode<value_type>	*next;
			listNode<value_type>	*prev;

			explicit listNode(value_type val = value_type(), listNode<value_type> *n = NULL, listNode<value_type> *p = NULL): value(val), next(n), prev(p) {}
		};

		// standard iterator
		template<typename value_typeT, typename difference_typeT, typename referenceT, typename pointerT>
		class listIterator {
		public:
			friend class list;

			typedef difference_typeT				difference_type;
			typedef value_typeT						value_type;
			typedef referenceT						reference;
			typedef pointerT						pointer;
			typedef std::bidirectional_iterator_tag	iterator_category;

		private:
			listNode<value_type>	*_node;

		public:
			listIterator(): _node(NULL) {}
			listIterator(listNode<value_type> *node): _node(node) {}
			listIterator(const listIterator &it): _node(it._node) {}
			~listIterator() {}

			listIterator	&operator=(const listIterator &it) {
				if (&it == this)
					return *this;
				_node = it._node;
				return *this;
			}
			bool			operator==(const listIterator &it) const {
				return 	it._node == _node;
			}
			bool			operator!=(const listIterator &it) const {
				return 	it._node != _node;
			}
			listIterator	&operator++() {
				if (_node->next == NULL)
					throw std::exception(); // TODO exception
				_node = _node->next;
				return *this;
			}
			listIterator	operator++(int) {
				iterator copy(*this);
				++(*this);
				return copy;
			}
			listIterator	&operator--() {
				if (_node->prev == NULL)
					throw std::exception(); // TODO exception
				_node = _node->prev;
				return *this;
			}
			listIterator	operator--(int) {
				iterator copy(*this);
				--(*this);
				return copy;
			}

			reference operator*() const {
				return _node->value;
			}
			pointer operator->() const {
				return &(**this);
			}
		};

	public:
		typedef listIterator<value_type, difference_type, reference, pointer>				iterator;
		typedef listIterator<value_type, difference_type, const_reference, const_pointer>	const_iterator;
		typedef std::reverse_iterator<iterator>												reverse_iterator; // TODO remove reverse_iterator dependency
		typedef std::reverse_iterator<const_iterator>										const_reverse_iterator;

	private:
		typedef typename allocator_type::template rebind<listNode<value_type> >::other	node_allocator;
		allocator_type			_allocator;
		node_allocator			_nodeAllocator;
		listNode<value_type>	*_endNode;
		listNode<value_type>	*_front;
		listNode<value_type>	*_back;

	public:
		// constructors & destructor
		explicit list(const allocator_type& alloc = allocator_type()): _allocator(alloc), _nodeAllocator(_allocator), _endNode(new listNode<value_type>()), _front(_endNode), _back(_endNode) {}
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _allocator(alloc), _nodeAllocator(_allocator), _endNode(new listNode<value_type>()), _front(_endNode), _back(_endNode) {
			assign(n, val);
		}
		template <class InputIterator>
		list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()): _allocator(alloc), _nodeAllocator(_allocator), _endNode(new listNode<value_type>()), _front(_endNode), _back(_endNode) {
			assign<InputIterator>(first, last);
		}
		list(const list& x): _allocator(), _nodeAllocator(), _endNode(new listNode<value_type>()), _front(_endNode), _back(_endNode) {
			operator=(x);
		}
		~list() {
			clear();
		}

		// operators
		list	&operator=(const list& x) {
			if (&x == this)
				return *this;
			_allocator = x._allocator;
			_nodeAllocator = x._nodeAllocator;
			clear();
			assign(x.begin(), x.end());
			return *this;
		};

		// iterators
		iterator begin() { return iterator(_front); }
		reverse_iterator rbegin() { return reverse_iterator(_back); }
		const_iterator begin() const { return const_iterator(_front); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_back); }
		iterator end() { return iterator(_back); }
		reverse_iterator rend() { return reverse_iterator(_front); }
		const_iterator end() const { return const_iterator(_back); }
		const_reverse_iterator rend() const { return const_reverse_iterator(_front); }

		// capacity
		bool empty() const {
			return _front == _back;
		}
		size_type size() const {
			size_type	out = 0;
			for (const_iterator it = begin(); it != end(); ++it)
				out++;
			return out;
		}
		size_type max_size() const {
			return std::numeric_limits<size_type>::max(); // TODO remove numeric_limits?
		}

		// access
		reference		front() {
			return *begin();
		}
		const_reference	front() const {
			return *begin();
		}
		reference		back() {
			return *(--end());
		}
		const_reference	back() const {
			return *(--end());
		}

		// modifiers
		void	clear() {
			erase(begin(), end());
		}
		void	push_front(const value_type& val) {
			listNode<value_type> *newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode, listNode<value_type>(val, _front));
			_front->prev = newNode;
			_front = newNode;
		}
		void	pop_front() {
			listNode<value_type> *detachedNode = _front;
			_front = _front->next;
			_front->prev = NULL;
			_nodeAllocator.destroy(detachedNode);
			_nodeAllocator.deallocate(detachedNode, 1);
		}
		void	push_back(const value_type& val) {
			listNode<value_type> *newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode, listNode<value_type>(val, _back));
			if (_back->prev != NULL) {
				_back->prev->next = newNode;
				newNode->prev = _back->prev;
				newNode->next = _back;
			}
			_back->prev = newNode;
			if (_front == _back) {
				_front = newNode;
			}
		}
		void	pop_back() {
			listNode<value_type> *detachedNode = _back->prev;
			_back->prev = detachedNode->prev;
			if (_back->prev != NULL)
				_back->prev->next = _back;
			if (_front == detachedNode)
				_front = detachedNode->next;
			_nodeAllocator.destroy(detachedNode);
			_nodeAllocator.deallocate(detachedNode, 1);
		}
		void	assign(size_type n, const value_type& val) {
			clear();
			for (size_type i = 0; i < n; ++i)
				push_back(val);
		}
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last) {
			clear();
			for (InputIterator it = first; it != last; ++it)
				push_back(*it);
		}
		iterator erase(iterator position) {
			listNode<value_type> *detachedNode = position._node;
			++position;
			detachedNode->next->prev = detachedNode->prev;
			if (detachedNode->prev != NULL)
				detachedNode->prev->next = detachedNode->next;
			if (_back->prev != NULL)
				_back->prev->next = _back;
			if (_front == detachedNode)
				_front = detachedNode->next;
			_nodeAllocator.destroy(detachedNode);
			_nodeAllocator.deallocate(detachedNode, 1);
			return position;
		}
		iterator erase(iterator first, iterator last) {
			while (first != last)
				first = erase(first);
			return last;
		}
		void swap(list& x) {
			std::swap(x._endNode, _endNode); // TODO dont use std::swap
			std::swap(x._back, _back);
			std::swap(x._front, _front);
		}
		void resize(size_type n, value_type val = value_type()) {
			size_type s = size();
			if (n > s) {
				for (size_type toAdd = n - s; toAdd > 0; --toAdd)
					push_back(val);
			}
			else if (s > n) {
				iterator toDelete = begin();
				std::advance(toDelete, n); // TODO dont use std::advance
				erase(toDelete, end());
			}
		}
		iterator insert(iterator position, const value_type& val) {
			listNode<value_type> *newNode = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(newNode, listNode<value_type>(val, position._node->next, position._node));
			position._node->next->prev = newNode;
			position._node->next = newNode;
			return ++position;
		}
		void insert(iterator position, size_type n, const value_type& val) {
			size_type i = 0;
			iterator begin = position;
			try {
				for (; i < n; ++i)
					position = insert(position, val);
			} catch (const std::exception &e) {
				// undo changes if failed to allocate
				if (i > 0)
					erase(++begin, ++position);
				throw;
			}
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last) {
			size_type i = 0;
			iterator begin = position;
			try {
				for (; first != last; ++first) {
					position = insert(position, *first);
					++i;
				}
			} catch (const std::exception &e) {
				// undo changes if failed to allocate
				if (i > 0)
					erase(++begin, ++position);
				throw;
			}
		}

		// operations
		void splice(iterator position, list &x) {
			splice(position, x, x.begin(), x.end());
		}
		void splice(iterator position, list &x, iterator i) {
			if (&x == this) return;
			listNode<value_type> *node = i._node;
			// detach from previous list
			if (node->prev != NULL)
				node->prev->next = node->next;
			node->next->prev = node->prev;

			// attach to new list
			node->next = position._node;
			node->prev = position._node->prev;
			if (position._node->prev)
				position._node->prev->next = node;
			position._node->prev = node;
		}
		void splice(iterator position, list &x, iterator first, iterator last) {
			if (&x == this) return;
			for (; first != last; ++first)
				splice(position, x, first);
		}
		void remove(const value_type& val) {
			for (iterator it = begin(); it != end();) {
				if (*it == val)
					it = erase(it);
				else
					++it;
			}
		}
		template <class Predicate>
		void remove_if(Predicate pred) {
			for (iterator it = begin(); it != end();) {
				if (pred(*it))
					it = erase(it);
				else
					++it;
			}
		}
		void unique() {
			iterator it = begin();
			iterator it2 = begin();
			if (it == end() || ++it2 == end()) return;
			while (it2 != end()) {
				if (*it == *it2)
					it2 = erase(it2);
				else {
					++it;
					++it2;
				}
			}
		}
		template <class BinaryPredicate>
		void unique(BinaryPredicate binary_pred) {
			iterator it = begin();
			iterator it2 = begin();
			if (it == end() || ++it2 == end()) return;
			while (it2 != end()) {
				if (binary_pred(*it,*it2))
					it2 = erase(it2);
				else {
					++it;
					++it2;
				}
			}
		}
		void merge(list& x) {
			if (&x == this) return;
			iterator x_it = x.begin();
			iterator this_it = begin();
			if (x_it == x.end()) return;
			while (this_it != end()) {
				if (!(*x_it < *this_it)) {
					splice(this_it, x, x_it);
					x_it = x.begin();
					if (x_it == x.end()) return;
				}
				else
					++this_it;
			}
			// move the remainder
			splice(end(), x);
		}
		template <class Compare>
		void merge(list& x, Compare comp) {
			if (&x == this) return;
			iterator x_it = x.begin();
			iterator this_it = begin();
			if (x_it == x.end()) return;
			while (this_it != end()) {
				if (!comp(*x_it, *this_it)) {
					splice(this_it, x, x_it);
					x_it = x.begin();
					if (x_it == x.end()) return;
				}
				else
					++this_it;
			}
			// move the remainder
			splice(end(), x);
		}
		void sort() {
			// TODO sort logic
		}
		template <class Compare>
		void sort(Compare comp) {
			// TODO sort logic
		}
		void reverse() {
			// TODO reverse logic
		}

		// observers
		allocator_type	get_allocator() const {
			return _allocator;
		}
	};

	// non member functions
	template <class T, class Alloc>
	void swap(list<T,Alloc>& x, list<T,Alloc>& y) {
		x.swap(y);
	}

	// operators
	template <class T, class Alloc>
	bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		typename list<T,Alloc>::const_iterator	lhs_it = lhs.begin();
		typename list<T,Alloc>::const_iterator	rhs_it = rhs.begin();
		while (lhs_it != lhs.end() && rhs_it != rhs.end()) {
			if (*lhs_it != *rhs_it)
				return false; // not equal, return false
			++lhs_it;
			++rhs_it;
		}
		return true;
	}

	template <class T, class Alloc>
	bool operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return !(lhs==rhs);
	}

	template <class T, class Alloc>
	bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		typename list<T,Alloc>::const_iterator	lhs_it = lhs.begin();
		typename list<T,Alloc>::const_iterator	rhs_it = rhs.begin();
		while (lhs_it != lhs.end() && rhs_it != rhs.end()) {
			if (*lhs_it != *rhs_it) {
				return *lhs_it < *rhs_it; // number not equal, return comparison
			}
			++lhs_it;
			++rhs_it;
		}
		if (lhs_it == lhs.end() && rhs_it == rhs.end())
			return false; // equal
		if (lhs_it == lhs.end())
			return true; // left is smaller in size
		return false; // right is smaller in size
	}

	template <class T, class Alloc>
	bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return !(rhs<lhs);
	}

	template <class T, class Alloc>
	bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return rhs<lhs;
	}

	template <class T, class Alloc>
	bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return !(lhs<rhs);
	}
}

#endif //LIST_HPP

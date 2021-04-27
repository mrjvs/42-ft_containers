//
// Created by jelle on 4/23/2021.
//

#ifndef LIST_HPP
#define LIST_HPP

#include <memory> // allocator and std::bad_alloc exception
#include <exception> // custom exception class
#include <iterator> // iterator category
#include "utils.hpp" // ft::less and ft::swap

namespace ft {

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
			class _outOfBoundsException: public std::exception {
				const char * what() const throw() {
					return "Iterator: out of bounds";
				}
			};
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
					throw _outOfBoundsException();
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
					throw _outOfBoundsException();
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
		listNode<value_type>	_endNodeStack;
		listNode<value_type>	*_endNode;
		listNode<value_type>	*_front;
		listNode<value_type>	*_back;

	public:
		// constructors & destructor
		explicit list(const allocator_type& alloc = allocator_type()): _allocator(alloc), _nodeAllocator(_allocator), _endNodeStack(), _endNode(&_endNodeStack), _front(_endNode), _back(_endNode) {}
		explicit list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _allocator(alloc), _nodeAllocator(_allocator), _endNodeStack(), _endNode(&_endNodeStack), _front(_endNode), _back(_endNode) {
			assign(n, val);
		}
		template <class InputIterator>
		list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()): _allocator(alloc), _nodeAllocator(_allocator), _endNodeStack(), _endNode(&_endNodeStack), _front(_endNode), _back(_endNode) {
			assign<InputIterator>(first, last);
		}
		list(const list& x): _allocator(), _nodeAllocator(), _endNodeStack(), _endNode(&_endNodeStack), _front(_endNode), _back(_endNode) {
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
			return _nodeAllocator.max_size();
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
			ft::swap(_endNode, x._endNode);
			ft::swap(_back, x._back);
			ft::swap(_front, x._front);
		}
		void resize(size_type n, value_type val = value_type()) {
			size_type s = size();
			if (n > s) {
				for (size_type toAdd = n - s; toAdd > 0; --toAdd)
					push_back(val);
			}
			else if (s > n) {
				iterator toDelete = begin();
				for (;n > 0;--n) ++toDelete;
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
			} catch (const std::bad_alloc &e) {
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
			} catch (const std::bad_alloc &e) {
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
			if (x._front == node)
				x._front = node->next;

			// attach to new list
			node->next = position._node;
			node->prev = position._node->prev;
			if (position._node->prev)
				position._node->prev->next = node;
			position._node->prev = node;
			if (_front == position._node)
				_front = node;
		}
		void splice(iterator position, list &x, iterator first, iterator last) {
			if (&x == this) return;
			while (first != last) {
				iterator tmp = first;
				++first;
				splice(position, x, tmp);
			}
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
			unique(ft::equal_to<value_type>());
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
			merge(x, ft::less<value_type>());
		}
		template <class Compare>
		void merge(list& x, Compare comp) {
			if (&x == this) return;
			iterator x_it = x.begin();
			iterator this_it = begin();
			if (x_it == x.end()) return;
			while (this_it != end()) {
				if (comp(*x_it, *this_it)) {
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
	private:
		iterator swap_items(iterator first, iterator second) {
			if (first == second)
				return first;
			if (first == end() || second == end())
				return first;

			// front protection
			if (first._node == _front)
				_front = second._node;
			else if (second._node == _front)
				_front = first._node;

			listNode<value_type>	*tmp;
			// swap prev pointers
			tmp = first._node->prev;
			first._node->prev = second._node->prev;
			second._node->prev =  tmp;

			// swap next pointers
			tmp = first._node->next;
			first._node->next = second._node->next;
			second._node->next = tmp;

			// fix pointers, (if X points to X, then change it to Y)
			if (second._node->next == second._node) second._node->next = first._node;
			if (second._node->prev == second._node) second._node->prev = first._node;
			if (first._node->next == first._node) first._node->next = second._node;
			if (first._node->prev == first._node) first._node->prev = second._node;

			// fix prev and next of the bunch
			if (second._node->prev != NULL) second._node->prev->next = second._node;
			if (first._node->prev != NULL) first._node->prev->next = first._node;
			second._node->next->prev = second._node;
			first._node->next->prev = first._node;
			return second;
		}

	public:
		void sort() {
			sort(ft::less<value_type>());
		}
		template <class Compare>
		void sort(Compare comp) {
			size_type loops = size();
			size_type advance = 0;
			if (loops < 2) return;
			// only do sort iteration if more than 1 item left
			while (loops > 1) {
				iterator a = begin();
				iterator b = a;
				size_type i = 0;
				++b; // a = i, b = i+1;
				while (i < loops-1) {
					if (comp(*b, *a)) // if b is smaller than a, swap
						a = swap_items(a,b);
					a++;
					b = a; // needed because b gets invalidated by swap_items
					++b; // a = i, b = i+1
					i++;
				}
				loops--; // count down loops
			}
		}
		void reverse() {
			iterator a = begin();
			iterator b = end();
			if (a == b) return; // no items
			if (a == b--) return; // only one item

			// reverse
			while (a != b) {
				a = swap_items(a, b++); // swap a and b
				----b; // move b to original pos - 1
				if (a == b) break; // prevent it from passing each other
				a++; // increase a
			}
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

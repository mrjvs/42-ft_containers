//
// Created by jelle on 4/28/2021.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> // allocator
#include <iterator> // iterator tag
#include <exception> // out of range exception
#include "utils.hpp" // ft::swap

namespace ft {

	template <class T, class Alloc>
	class vector;

	// random access iterator
	template<class T, class Alloc, class containerT, typename containerReferenceT, typename containerPointerT, typename value_typeT, typename difference_typeT, typename referenceT, typename pointerT>
	class vectorIterator {
	public:
		friend class vector<T, Alloc>;

		typedef difference_typeT				difference_type;
		typedef value_typeT						value_type;
		typedef referenceT						reference;
		typedef pointerT						pointer;
		typedef std::random_access_iterator_tag	iterator_category;

	private:
		typedef containerT						container;
		typedef containerReferenceT				container_reference;
		typedef containerPointerT				container_pointer;
		typedef typename containerT::size_type	size_type;

		container_pointer _cont;
		size_type _index;

	public:
		vectorIterator() : _cont(0), _index(0) {}
		vectorIterator(containerReferenceT ref, size_type index = 0) : _cont(&ref), _index(index) {}
		vectorIterator(const vectorIterator &it) : _cont(it._cont), _index(it._index) {}
		~vectorIterator() {}

		vectorIterator &operator=(const vectorIterator &it) {
			if (&it == this)
				return *this;
			_cont = it._cont;
			_index = it._index;
			return *this;
		}

		bool operator==(const vectorIterator &it) const {
			return it._cont == _cont && it._index == _index;
		}

		bool operator!=(const vectorIterator &it) const {
			return !operator==(it);
		}

		vectorIterator &operator++() {
			if (_index >= _cont->size())
				throw std::out_of_range("iterator::out_of_range");
			_index++;
			return *this;
		}

		vectorIterator operator++(int) {
			vectorIterator copy(*this);
			++(*this);
			return copy;
		}

		vectorIterator &operator--() {
			if (_index == 0)
				throw std::out_of_range("iterator::out_of_range");
			_index--;
			return *this;
		}

		vectorIterator operator--(int) {
			vectorIterator copy(*this);
			--(*this);
			return copy;
		}

		vectorIterator &operator+=(difference_type rhs) {
			if (rhs < 0)
				return operator-=(rhs*-1);
			for (difference_type i = 0; i < rhs; ++i)
				operator++();
			return *this;
		}
		vectorIterator &operator-=(difference_type rhs) {
			if (rhs < 0)
				return operator+=(rhs*-1);
			for (difference_type i = 0; i < rhs; ++i)
				operator--();
			return *this;
		}
		vectorIterator operator+(const difference_type &rhs) const {
			vectorIterator lhs = *this;
			lhs+=rhs;
			return lhs;
		}
		vectorIterator operator-(const difference_type &rhs) const {
			vectorIterator lhs = *this;
			lhs-=rhs;
			return lhs;
		}
		difference_type operator-(const vectorIterator &rhs) const {
			return ((difference_type)_index) - rhs._index;
		}

		bool operator<(const vectorIterator &rhs) const {
			return operator-(rhs) < 0;
		}
		bool operator<=(const vectorIterator &rhs) const {
			return operator-(rhs) <= 0;
		}
		bool operator>(const vectorIterator &rhs) const {
			return operator-(rhs) > 0;
		}
		bool operator>=(const vectorIterator &rhs) const {
			return operator-(rhs) >= 0;
		}

		reference operator*() const {
			return (*_cont)[_index];
		}

		reference operator[](difference_type rhs) const {
			vectorIterator it = *this;
			it+=rhs;
			return *it;
		}

		pointer operator->() const {
			return &(**this);
		}
	};

	template<class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef vectorIterator<T, Alloc, vector<value_type>, vector<value_type> &, vector<value_type> *, value_type, difference_type, reference, pointer>							iterator;
		typedef vectorIterator<T, Alloc, vector<value_type>, const vector<value_type> &, const vector<value_type> *, value_type, difference_type, const_reference, const_pointer>	const_iterator;
		typedef std::reverse_iterator<iterator>																																		reverse_iterator; // TODO remove reverse_iterator dependency
		typedef std::reverse_iterator<const_iterator>																																const_reverse_iterator;

	private:
		allocator_type	_alloc;
		value_type		*_data;
		size_type		_capacity;
		size_type		_size;

	public:
		explicit vector(const allocator_type& alloc = allocator_type()): _alloc(alloc), _data(0), _capacity(0), _size(0) {}
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _data(0), _capacity(0), _size(0) {
			assign(n, val);
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()): _alloc(alloc), _data(0), _capacity(0), _size(0) {
			assign<InputIterator>(first, last);
		}
		vector(const vector& x): _alloc(), _data(0), _capacity(0), _size(0) {
			operator=(x);
		}
		~vector() {
			resize(0);
			_alloc.deallocate(_data, _capacity);
		}
		vector& operator=(const vector& x) {
			if (&x == this)
				return *this;
			// clear old data completely
			resize(0);
			_alloc.deallocate(_data, _capacity);
			_data = 0;
			_capacity = 0;

			// add new data
			_alloc = x._alloc;
			assign<const_iterator>(x.begin(), x.end());
			return *this;
		}

		// iterators
		iterator begin() { return iterator(*this, 0); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_iterator begin() const { return const_iterator(*this, 0); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		iterator end() { return iterator(*this, _size); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_iterator end() const { return const_iterator(*this, _size); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		// capacity
		size_type size() const {
			return _size;
		}
		size_type max_size() const {
			return _alloc.max_size();
		}
		void resize(size_type n, value_type val = value_type()) {
			if (n > _size) {
				reserve(n);
				for (size_type i = size(); i < n; ++i)
					push_back(val);
				return;
			}
			while (_size > n)
				pop_back();
		}
		size_type capacity() const {
			return _capacity;
		}
		bool empty() const {
			return _size == 0;
		}
		void reserve(size_type n) {
			if (n <= _capacity) return;
			size_type oldCapacity = _capacity;
			if (_capacity == 0) _capacity = 1;
			for (;_capacity < n; _capacity *= 2);
			value_type *ptr = _alloc.allocate(_capacity);
			for (iterator it = begin(); it != end(); ++it) {
				_alloc.construct(ptr+it._index, *it);
				_alloc.destroy(_data+it._index);
			}
			if (_data != 0)
				_alloc.deallocate(_data, oldCapacity);
			_data = ptr;
		}

		// access
		reference operator[](size_type n) {
			return _data[n];
		}
		const_reference operator[](size_type n) const {
			return _data[n];
		}
		reference at(size_type n) {
			if (n < 0 || n >= _size)
				throw std::out_of_range("vector::out_of_range");
			return operator[](n);
		}
		const_reference at(size_type n) const {
			if (n < 0 || n >= _size)
				throw std::out_of_range("vector::out_of_range");
			return operator[](n);
		}
		reference front() {
			return operator[](0);
		}
		const_reference front() const {
			return operator[](0);
		}
		reference back() {
			return operator[](_size-1);
		}
		const_reference back() const {
			return operator[](_size-1);
		}

		// modifiers
		void assign(size_type n, const value_type &val) {
			clear();
			resize(n, val);
		}
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last) {
			size_type s = 0;
			for (InputIterator it = first; it != last; ++it)
				s++;
			clear();
			reserve(s);
			for (; first != last; ++first)
				push_back(*first);
		}
		void push_back(const value_type& val) {
			reserve(_size+1);
			_alloc.construct(_data+_size, val);
			++_size;
		}
		void pop_back() {
			if (empty()) return;
			--_size;
			_alloc.destroy(_data+_size);
		}

	private:
		void	moveData(iterator position, size_type n) {
			size_type endIndex = _size;
			size_type startIndex = position._index;
			resize(_size+n);

			// move all items from position to end N places up in reverse order
			for (; endIndex > startIndex; --endIndex)
				operator[](endIndex-1+n) = operator[](endIndex-1);
		}
		void	removeData(iterator position, size_type n) {
			size_type endIndex = _size;
			size_type startIndex = position._index;
			resize(_size+n);

			// move all items from position to end N places up in reverse order
			for (; endIndex > startIndex; --endIndex)
				operator[](endIndex-1+n) = operator[](endIndex-1);
		}

	public:
		iterator insert(iterator position, const value_type& val) {
			size_type index = position._index;
			insert(position, (size_type)1, val);
			return begin()+index;
		}
		void insert(iterator position, size_type n, const value_type& val) {
			size_type index = position._index;
			moveData(position, n);
			for (size_type i = 0; i < n; ++i)
				operator[](index+i) = val;
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last) {
			size_type n = 0;
			size_type index = position._index;
			for (InputIterator it = first; it != last; ++it)
				n++;
			moveData(position, n);
			for (size_type i = 0; i < n;) {
				operator[](index+i) = *first;
				++first;
				++i;
			}
		}
		iterator erase(iterator position) {
			return erase(position, position+1);
		}
		iterator erase(iterator first, iterator last) {
			size_type lastIndex = first._index;
			difference_type removedAmount = last - first;
			while (last != end()) {
				*first = *last;
				++first;
				++last;
			}
			for (size_type i = 0; i < removedAmount; ++i)
				pop_back();
			return begin()+lastIndex;
		}
		void swap(vector& x) {
			ft::swap(x._data, _data);
			ft::swap(x._capacity, _capacity);
			ft::swap(x._size, _size);
			ft::swap(x._alloc, _alloc);
		}
		void clear() {
			resize(0);
		}

		// observers
		allocator_type get_allocator() const {
			return _alloc;
		}
	};

	template<class T, class Alloc, typename A, typename B, typename C, typename D, typename E, typename F, typename G>
	vectorIterator<T, Alloc, A, B, C, D, E, F, G>	operator+(typename vectorIterator<T, Alloc, A, B, C, D, E, F, G>::difference_type lhs, const vectorIterator<T, Alloc, A, B, C, D, E, F, G> &rhs) {
		return rhs+lhs;
	}

	// non member overloads
	template <class T, class Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}

	// TODO comparison
}

#endif //VECTOR_HPP

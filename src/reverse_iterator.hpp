//
// Created by jelle on 4/29/2021.
//

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

namespace ft {

	template <class Iter>
	class reverse_iterator {
	public:

		typedef Iter								iterator_type;
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;

	protected:
		iterator_type	_current;

	public:
		// constructors
		reverse_iterator(): _current() {}
		explicit reverse_iterator(iterator_type x): _current(x) {}
		reverse_iterator(const reverse_iterator &other): _current(other._current) {}
		reverse_iterator &operator=(const reverse_iterator &other) {
			_current = other._current;
		}

		// member functions
		iterator_type base() const {
			return _current;
		}

		// access
		reference operator*() const {
			Iter tmp = _current;
			return *--tmp;
		}
		pointer operator->() const {
			return &(operator*());
		}
		reference operator[](difference_type n) const {
			return base()[-n-1];
		}

		// increment/decrement
		reverse_iterator &operator++() {
			_current--;
			return *this;
		}
		reverse_iterator &operator--() {
			_current++;
			return *this;
		}
		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			_current--;
			return tmp;
		}
		reverse_iterator operator--(int) {
			reverse_iterator tmp = *this;
			_current++;
			return tmp;
		}
		reverse_iterator &operator+=(difference_type n) {
			_current += -n;
		}
		reverse_iterator &operator-=(difference_type n) {
			_current -= -n;
		}
		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(base()-n);
		}
		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(base()+n);
		}

		// comparison
		bool operator==(const reverse_iterator &rhs) {
			return base() == rhs.base();
		}
		bool operator!=(const reverse_iterator &rhs) {
			return base() != rhs.base();
		}
		bool operator<(const reverse_iterator &rhs) {
			return base() < rhs.base();
		}
		bool operator<=(const reverse_iterator &rhs) {
			return base() <= rhs.base();
		}
		bool operator>(const reverse_iterator &rhs) {
			return base() > rhs.base();
		}
		bool operator>=(const reverse_iterator &rhs) {
			return base() >= rhs.base();
		}
	};

	// non member functions
	template<class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it) {
		return reverse_iterator<Iter>(it.base() - n);
	}
	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
		return rhs.base() - lhs.base();
	}
}

#endif //REVERSE_ITERATOR_HPP

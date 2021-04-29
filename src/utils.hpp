//
// Created by jelle on 4/27/2021.
//

#ifndef _UTILS_HPP
#define _UTILS_HPP

namespace ft {

	template<class T> struct less {
		bool operator()(const T &lhs, const T &rhs ) const {
			return lhs < rhs;
		}
	};

	template<class T>
	void swap(T &a, T &b) {
		T tmp = a;
		a = b;
		b = tmp;
	}

	template<class T> struct equal_to {
		bool operator()(const T &lhs, const T &rhs ) const {
			return lhs == rhs;
		}
	};

}

#endif //_UTILS_HPP

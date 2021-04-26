//
// Created by jelle on 4/23/2021.
//

#ifndef MAIN_HPP
#define MAIN_HPP

#include "list.hpp"
#include "orderedList.hpp"
#include "multimap.hpp"
#include "map.hpp"
#include "multiset.hpp"
#include "set.hpp"
#include "stack.hpp"
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sstream>

// printing
void	start_test(const std::string &title, int num);
void	start_batch(const std::string &prefix);
void	fail_test();
void	end_test();

// tests
void list_tests();
void ordered_list_tests();
void multimap_test();
void map_test();
void set_test();
void multiset_test();
void stack_test();

#endif //MAIN_HPP

//
// Created by jelle on 4/23/2021.
//

#ifndef MAIN_HPP
#define MAIN_HPP

#include "list.hpp"
#include "orderedList.hpp"
#include "multimap.hpp"
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

#endif //MAIN_HPP

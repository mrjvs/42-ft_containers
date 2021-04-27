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
#include "queue.hpp"
#include <vector>
#include <unistd.h>
#include <iostream>
#include <sstream>

// printing
void	start_test(const std::string &title, int num);
void	start_batch(const std::string &prefix);
void	fail_test();
void	end_test();
void	end_of_tests();

#define test(str) start_test(str, ++num)

// tests
#include "list_test.hpp"
#include "ordered_list_test.hpp"
#include "multimap_test.hpp"
#include "map_test.hpp"
#include "multiset_test.hpp"
#include "set_test.hpp"
#include "queue_test.hpp"
#include "stack_test.hpp"

#endif //MAIN_HPP

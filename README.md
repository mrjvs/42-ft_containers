# 42-ft_containers
remaking some c++ containers from scratch (poorly)

## usage
1. add /src as include folder
2. include any file/container you need

## unit tests
All containers added MUST have full test coverage. you can run the tests by running make/cmake.
```SH
./build/ft_container_tests FT # run all tests on ft namespace
./build/ft_container_tests STD # run all tests on std namespace
./build/ft_container_tests help # show usage

# specify tests to run after the namespace specifier
./build/ft_container_tests FT list ordered_list stack
```

## todos
 - [ ] make custom reverse iterators
 - [ ] make normal makefile
 - [X] make tests for stdlib versions (for comparing)
 - [X] no leaks
 - [X] make and use `ft::pair` instead of `std::pair`
 - [X] full test coverage for `ft::orderedList`
 - [X] remove all uses of `std::`
 - [X] use allocator for allocation (`allocator::rebind<Node<T>>::other(allocatorInstance)`)
 - [X] full test coverage for `ft::list`

## containers todo
 - [ ] `ft::vector`
 - [ ] `ft::deque`
 - [X] `ft::list`
 - [X] `ft::map`
 - [X] `ft::stack`
 - [X] `ft::queue`
 - [X] `ft::multimap`
 - [X] `ft::set`
 - [X] `ft::multiset`

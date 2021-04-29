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

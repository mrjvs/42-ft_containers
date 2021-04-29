# Constants
NAME			= ft_containers_tests

# Compiler
CXX				= clang++

CXX_FLAGS		= -Wall -Werror -Wextra -std=c++98 -pedantic-errors

# Files
SRC_DIR		            	= tests
BUILD_DIR	            	= build
OUT_DIR		            	= build/out
INC_DIR		            	= tests/_includes
CONTAINER_INC_DIR			= src
NAME		               	:= $(addprefix ./$(BUILD_DIR)/,$(NAME))

SRC	=\
	main.cpp\
	printing.cpp\

HEADERS	=\
	main.hpp\
	deque_test.hpp\
	list_test.hpp\
	map_test.hpp\
	multimap_test.hpp\
	set_test.hpp\
	multiset_test.hpp\
	ordered_list_test.hpp\
	queue_test.hpp\
	stack_test.hpp\
	vector_test.hpp

CONTAINER_HEADERS	=\
	utils.hpp\
	reverse_iterator.hpp\
	pair.hpp\
	deque.hpp\
	list.hpp\
	map.hpp\
	multimap.hpp\
	set.hpp\
	multiset.hpp\
	orderedList.hpp\
	queue.hpp\
	stack.hpp\
	vector.hpp

# Fix sources and headers
OBJ				    = $(patsubst %,%.o,$(SRC))
HEADERS			    := $(addprefix $(INC_DIR)/,$(HEADERS))
CONTAINER_HEADERS	:= $(addprefix $(CONTAINER_INC_DIR)/,$(CONTAINER_HEADERS))

# Colours
DARK_GREEN		= \033[0;32m
GREEN			= \033[0;92m
END				= \033[0;0m

PREFIX			= $(DARK_GREEN)$(notdir $(NAME)) $(END)>>

# Rules
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(addprefix $(OUT_DIR)/,$(OBJ))
	@echo "$(PREFIX)$(GREEN) Bundling objects...$(END)"
	@echo "BUILD $(NAME) $(CXX_FLAGS) $(DEBUG_FLAGS) $(BUILD_FLAGS)"
	@$(CXX) $(CXX_FLAGS) $(DEBUG_FLAGS) $(BUILD_FLAGS) -I$(INC_DIR) -I$(CONTAINER_INC_DIR) -o $@ $(addprefix $(OUT_DIR)/,$(OBJ))

$(OUT_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp $(HEADERS) $(CONTAINER_HEADERS)
	@echo "$(PREFIX)$(GREEN) Compiling file $(END)$(notdir $<) $(GREEN)to $(END)$(notdir $@)"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXX_FLAGS) $(DEBUG_FLAGS) -I$(SRC_DIR) -I$(INC_DIR) -I$(CONTAINER_INC_DIR) -o $@ -c $<

clean:
	@echo "$(PREFIX)$(GREEN) Removing directory $(END)$(OUT_DIR)"
	@rm -rf $(OUT_DIR)

fclean: clean
	@echo "$(PREFIX)$(GREEN) Removing file $(END)$(NAME)"
	@rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

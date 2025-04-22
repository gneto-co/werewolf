NAME = werewolf
CC = c++
CXXFLAGS = -Wall -Wextra -Werror

SRC_DIR = sources
OBJ_DIR = objects

SRC = $(shell find $(SRC_DIR) -type f -name "*.cpp" | sed 's|sources/||')
	
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

TOTAL := $(words $(SRC))

NC = \033[0m
RED = \033[31m
ORANGE = \033[33m
GREEN = \033[92m
BLUE = \033[34m

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $(CXXFLAGS) -o $@ $<
	@COMPILED=$$(find $(OBJ_DIR) -type f -name "*.o"  | wc -l); \
	PERCENT=$$(echo "scale=2; $$COMPILED / $(TOTAL) * 100" | bc); \
	printf "\r$(BLUE)Compiling... %d%%$(NC)" $$(printf "%.0f" $$PERCENT)
	#@echo "$(GREEN)[OK]$(NC)\t"$@

$(NAME): $(OBJ)
	@$(CC) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "\n------------------------------"
	@echo "$(ORANGE)$(NAME)$(NC) ready to use\n"

all: $(NAME)

# generate dependency files
# CXXFLAGS += -MMD

# leacks
# CXXFLAGS += -fsanitize=address

# for MacOs: cpp08
#	@$(CC) $(CXXFLAGS) $(OBJ) -o $(NAME) -lc++

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./whatever
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)[OK]\t$(RED)temporary object files deleted$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)[OK]$(NC)\t$(NAME) $(RED)deleted$(NC)"

newLine:
	@echo ""

re: fclean newLine all

.SILENT: $(OBJ)

.PHONY: all re clean fclean newLine

# ============== CUSTOM TEXT =================
BOLD=\033[1m
RESET=\033[0m
LIGHT_RED=\033[91m
LIGHT_GREEN=\033[92m
LIGHT_CYAN=\033[96m

# ============== MAIN INFO =================
NAME = minishell

# ============== LIBFT COMMANDS =================
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INCLUDES = -I $(LIBFT_DIR)/includes -I $(LIBFT_DIR)/dependency_includes

# ============== COMPILATION COMMANDS =================
INCLUDES = -I includes $(LIBFT_INCLUDES)
CC = cc
# CFLAGS = -Wall -Werror -Wextra -g3 -Ofast -march=native -flto -funroll-loops $(INCLUDES)
CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDES)

# ============== SRC FILES =================

TOKEN_DIR = src/lexer/tokenizer
TOKEN_FILES = $(TOKEN_DIR)/splitter/raw_splitter.c $(TOKEN_DIR)/splitter/raw_splitter_utils.c \
$(TOKEN_DIR)/splitter/granular_splitter.c $(TOKEN_DIR)/splitter/splitter_utils.c

STRUCTURES = src/linkedlist/linkedlist_node.c src/linkedlist/linkedlist.c

SRC_FILES = $(STRUCTURES) src/signals.c $(TOKEN_FILES)


# ============== PROGRAM FILES =================
MAIN_PROGRAM=src/main.c
TEST_PROGRAM=src/hashtable/hashtable.c

# ============== PROGRAM DEPENDENCIES =================

DEPENDENCIES = -lreadline -pie

# ============== CUSOM SLEEP =================
SLEEP = 0.07

# ============== COMPILATION =================
OBJS = $(SRC_FILES:%.c=%.o)
OBJ_MAIN_PROGRAM = $(MAIN_PROGRAM:%.c=%.o)
COMPILATION_DEPENDENCIES = $(OBJS) $(LIBFT)

OBJ_TEST_PROGRAM = $(TEST_PROGRAM:%.c=%.o)
COMPILATION_DEPENDENCIES_TEST = $(OBJ_TEST_PROGRAM) $(LIBFT)

TEST_PROGRAMS = split test linkedkist


# ***************************************************************************************************
# ********************************************           ********************************************
# ********************************************  TARGETS  ********************************************
# ********************************************           ********************************************
# ***************************************************************************************************

all: $(NAME)

$(NAME): $(OBJ_MAIN_PROGRAM) $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@echo "$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)"
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

$(LIBFT):
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(LIBFT_DIR) SLEEP="$(SLEEP)"

test: $(COMPILATION_DEPENDENCIES_TEST)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

split: tests/split.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

linkedkist: tests/linkedkist.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

%.o: %.c
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$<$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(MLX_DIR) SLEEP="$(SLEEP)"

minilibx:
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(MLX_DIR) SLEEP="$(SLEEP)"


clean:
	@echo "$(LIGHT_RED)>> $(BOLD)cleanning$(RESET) $(LIGHT_CYAN)./src$(RESET)..." && sleep $(SLEEP)
	@rm -rf $(COMPILATION_DEPENDENCIES)

fclean: clean
	@echo "$(LIGHT_RED)>> $(BOLD)deletting$(RESET) $(LIGHT_CYAN)./$(NAME)$(RESET)..." && sleep $(SLEEP)
	@rm -rf $(NAME)
	@echo "$(LIGHT_RED)>> $(BOLD)deletting$(RESET) $(LIGHT_CYAN)./$(BONUS)$(RESET)..." && sleep $(SLEEP)
	@rm -rf $(BONUS)
	@echo "$(LIGHT_RED)>> $(BOLD)deletting$(RESET) $(LIGHT_CYAN)$(TEST_PROGRAMS)$(RESET)..." && sleep $(SLEEP)
	@rm -rf $(TEST_PROGRAMS)

re: fclean all

.PHONY: all clean fclean re minilibx

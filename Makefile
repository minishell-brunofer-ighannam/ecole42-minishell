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
CFLAGS = -Wall -Werror -Wextra -g3 -fPIE $(INCLUDES)

# ============== SRC FILES =================

TOKEN_DIR = src/lexer/tokenizer
TOKEN_FILES = $(TOKEN_DIR)/splitter/raw_splitter.c $(TOKEN_DIR)/splitter/raw_splitter_utils.c $(TOKEN_DIR)/splitter/splitter_utils.c \
$(TOKEN_DIR)/splitter/refined_splitter.c $(TOKEN_DIR)/splitter/refine_raw_token.c

STRUCTURES = src/linkedlist/linkedlist_node.c src/linkedlist/linkedlist.c src/linkedlist_array/linkedlist_array.c src/hashtable/hashtable.c

BUILTINS = src/builtins/ft_env.c src/builtins/ft_export.c

PROCESS = src/process/child_process.c

READER = src/reader/reader.c

HASHTABLE = src/hashtable/hashtable.c src/hashtable/new_hashtable.c

ENV = src/env/env.c

SRC_FILES = $(STRUCTURES) $(TOKEN_FILES) $(BUILTINS) $(PROCESS) $(HASHTABLE) $(ENV) src/signals.c src/globals.c



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

TEST_PROGRAMS = linkedlist linkedlist_array raw_splitter refined_splitter env_ht_op child_process


# ***************************************************************************************************
# ********************************************           ********************************************
# ********************************************  TARGETS  ********************************************
# ********************************************           ********************************************
# ***************************************************************************************************

all: $(NAME)

$(NAME): $(OBJ_MAIN_PROGRAM) $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

$(LIBFT):
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(LIBFT_DIR) SLEEP="$(SLEEP)"


tests: fclean child_process linkedlist linkedlist_array raw_splitter refined_splitter
	@clear && echo "code% make tests"
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)child_process$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./child_process
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)linkedlist$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./linkedlist
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)linkedlist_array$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./linkedlist_array
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)raw_splitter$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./raw_splitter
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)refined_splitter$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./refined_splitter


linkedlist: tests/linkedlist.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

linkedlist_array: tests/linkedlist_array.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

raw_splitter: tests/raw_splitter.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

refined_splitter: tests/refined_splitter.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

env_ht_op: tests/env_ht_op.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) -no-pie -o $@ $^ $(DEPENDENCIES)

child_process: tests/child_process.c tests/tests.c $(COMPILATION_DEPENDENCIES)
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
	@echo "$(LIGHT_RED)>> $(BOLD)deletting$(RESET) $(LIGHT_CYAN)$(OBJ_MAIN_PROGRAM)$(RESET)..." && sleep $(SLEEP)
	@rm -rf $(OBJ_MAIN_PROGRAM)


re: fclean all

.PHONY: all clean fclean re minilibx

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


# ------------ LEXER FILES -----------------
SPLITTER_DIR = src/lexer/tokenizer/splitter
SPLITTER_FILES = $(SPLITTER_DIR)/raw_splitter.c $(SPLITTER_DIR)/raw_splitter_utils.c $(SPLITTER_DIR)/splitter_utils.c \
$(SPLITTER_DIR)/refined_splitter.c $(SPLITTER_DIR)/refine_raw_token.c

PROMPT_VAL_DIR = src/lexer/tokenizer/prompt_validator
PROMPT_VAL_FILES = $(PROMPT_VAL_DIR)/prompt_validator.c $(PROMPT_VAL_DIR)/validate_backquotes.c \
$(PROMPT_VAL_DIR)/validate_dollar_parens.c $(PROMPT_VAL_DIR)/validate_doublequotes.c \
$(PROMPT_VAL_DIR)/validate_parens.c $(PROMPT_VAL_DIR)/validate_utils.c $(PROMPT_VAL_DIR)/structure_jump.c \
$(PROMPT_VAL_DIR)/validate_singlequotes.c

LEXER_U_DIR = src/lexer/lexer_utils
LEXER_U_FILES = $(LEXER_U_DIR)/reserved_structures.c $(LEXER_U_DIR)/error_printer.c

LEXER_FILES = $(SPLITTER_FILES) $(PROMPT_VAL_FILES) $(LEXER_U_FILES)


# ------------ STRUCTURE FILES -----------------
STRUCTURES = src/linkedlist/iteration.c src/linkedlist/linkedlist_node.c src/linkedlist/linkedlist.c \
src/linkedlist_array/linkedlist_array.c src/hashtable/hashtable.c



# ------------ BUILTINS FILES -----------------
BUILTINS = src/builtins/ft_env.c src/builtins/ft_export.c src/builtins/ft_set.c src/builtins/ft_unset.c



# ------------ PROCESS FILES -----------------
PROCESS = src/process/child_process.c


ENV = src/env/env.c


EXECUTER = src/executer/find_path.c


SRC_FILES = $(STRUCTURES) $(LEXER_FILES) $(BUILTINS) $(PROCESS) $(ENV) $(EXECUTER) src/signals.c src/globals.c




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
COMPILATION_DEPENDENCIES = $(LIBFT) $(OBJS) 
 
TEST_PROGRAMS = linkedlist linkedlist_array raw_splitter refined_splitter env_ht_op child_process prompt_validator env_ht_op find_path



# ***************************************************************************************************
# ********************************************           ********************************************
# ********************************************  TARGETS  ********************************************
# ********************************************           ********************************************
# ***************************************************************************************************

all: $(NAME)

$(NAME): $(COMPILATION_DEPENDENCIES) $(OBJ_MAIN_PROGRAM) 
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJ_MAIN_PROGRAM) $(LIBFT)  -o $@ $(DEPENDENCIES)

$(LIBFT):
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(LIBFT_DIR) SLEEP="$(SLEEP)"


tests: fclean child_process linkedlist linkedlist_array raw_splitter refined_splitter prompt_validator env_ht_op find_path
	@clear && echo "code% make tests"
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)child_process$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes ./child_process
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)prompt_validator$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./prompt_validator
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)linkedlist$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./linkedlist
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)linkedlist_array$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./linkedlist_array
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)raw_splitter$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./raw_splitter
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)refined_splitter$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./refined_splitter
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)env_ht_op$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./env_ht_op
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)find_path$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./find_path

linkedlist: tests/linkedlist.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/linkedlist.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

linkedlist_array: tests/linkedlist_array.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/linkedlist_array.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

prompt_validator: tests/lexer/prompt_validator.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/lexer/prompt_validator.c  tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

raw_splitter: tests/lexer/raw_splitter.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/lexer/raw_splitter.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

refined_splitter: tests/lexer/refined_splitter.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/lexer/refined_splitter.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

env_ht_op: tests/env_ht_op.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) -no-pie -o $@ tests/env_ht_op.c $(OBJS) $(LIBFT) $(DEPENDENCIES)

child_process: tests/child_process.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/child_process.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

find_path: tests/find_path.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/find_path.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)


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
	@echo "$(LIGHT_RED)>> $(BOLD)cleanning$(RESET) $(LIGHT_CYAN)./$(LIBFT_DIR)$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(LIGHT_RED)>> $(BOLD)deletting$(RESET) $(LIGHT_CYAN)$(LIBFT_DIR)$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(LIBFT_DIR) fclean
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

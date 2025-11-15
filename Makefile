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

TOKENIZE_DIR = src/lexer/tokenizer/tokenize
EXP_OBJECT_DIR = $(TOKENIZE_DIR)/expandable_object
EXP_OBJECT_FILES = $(EXP_OBJECT_DIR)/find_expandable.c $(EXP_OBJECT_DIR)/expansion_utils.c \
$(EXP_OBJECT_DIR)/expansion_object_utils.c $(EXP_OBJECT_DIR)/find_keys_to_expand.c \
$(EXP_OBJECT_DIR)/expandable_object.c

TOKENIZE_FILES = $(EXP_OBJECT_FILES) $(TOKENIZE_DIR)/build_expansion.c $(TOKENIZE_DIR)/token.c

LEXER_U_DIR = src/lexer/lexer_utils
LEXER_U_FILES = $(LEXER_U_DIR)/reserved_structures.c $(LEXER_U_DIR)/error_printer.c

LEXER_FILES = $(SPLITTER_FILES) $(PROMPT_VAL_FILES) $(TOKENIZE_FILES) $(LEXER_U_FILES)


# ------------ STRUCTURE FILES -----------------
STRUCTURES = src/linkedlist/iteration.c src/linkedlist/linkedlist_node.c src/linkedlist/linkedlist.c \
src/linkedlist_array/linkedlist_array.c src/hashtable/hashtable.c


# ------------ BUILTINS FILES -----------------
BUILTINS = src/builtins/ft_env.c src/builtins/ft_export.c src/builtins/ft_unset.c


# ------------ PROCESS FILES -----------------
PROCESS = src/process/child_process.c


SRC_FILES = $(STRUCTURES) $(LEXER_FILES) $(BUILTINS) $(PROCESS) src/signals.c src/globals.c



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

TEST_PROGRAMS = linkedlist linkedlist_array raw_splitter refined_splitter \
env_ht_op child_process prompt_validator find_expandable find_keys_to_expand \
create_expandable_object build_expansion



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


tests: fclean child_process find_expandable find_keys_to_expand create_expandable_object \
linkedlist linkedlist_array raw_splitter refined_splitter prompt_validator

	@clear && echo "code% make tests"
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)child_process$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full --track-fds=yes ./child_process

#	=================== EXPANSION TESTS =====================
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)find_expandable$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./find_expandable

	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)find_keys_to_expand$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./find_keys_to_expand

	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)create_expandable_object$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./create_expandable_object

#	=================== PROMPT & SPLITTING TESTS =====================
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)prompt_validator$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./prompt_validator

	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)raw_splitter$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./raw_splitter
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)refined_splitter$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./refined_splitter

#	=================== DATA STRUCTURES TESTS =====================
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)linkedlist$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./linkedlist
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)linkedlist_array$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./linkedlist_array


linkedlist: tests/linkedlist.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

linkedlist_array: tests/linkedlist_array.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

prompt_validator: tests/lexer/prompt_validator.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

raw_splitter: tests/lexer/raw_splitter.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

refined_splitter: tests/lexer/refined_splitter.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

find_expandable: tests/lexer/tokenize/find_expandable.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

find_keys_to_expand: tests/lexer/tokenize/find_keys_to_expand.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

create_expandable_object: tests/lexer/tokenize/create_expandable_object.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $^ -o $@ $(DEPENDENCIES)

build_expansion: tests/lexer/tokenize/build_expansion.c tests/tests.c $(COMPILATION_DEPENDENCIES)
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

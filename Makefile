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
CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDES)
DESTDIR= $(HOME)/bin
INSTALL_PATH= $(DESTDIR)/$(NAME)

# ============== SRC FILES =================

# ------------ LEXER FILES -----------------
SPLITTER_DIR = src/core/lexer/splitter
SPLITTER_FILES = $(SPLITTER_DIR)/raw_splitter/raw_splitter.c $(SPLITTER_DIR)/raw_splitter/raw_splitter_utils.c $(SPLITTER_DIR)/raw_splitter/raw_splitter_quote_states.c \
$(SPLITTER_DIR)/refined_splitter/refined_splitter.c $(SPLITTER_DIR)/refined_splitter/refine_raw_token.c $(SPLITTER_DIR)/refined_splitter/refine_raw_token_push.c \
$(SPLITTER_DIR)/refined_splitter/refine_raw_manage_grouped_and_ungrouped.c \
$(SPLITTER_DIR)/splitter_utils.c $(SPLITTER_DIR)/splitter.c

PROMPT_VAL_DIR = src/core/lexer/prompt_validator
PROMPT_VAL_FILES = $(PROMPT_VAL_DIR)/prompt_validator.c $(PROMPT_VAL_DIR)/validate_backquotes.c \
$(PROMPT_VAL_DIR)/validate_dollar_parens.c $(PROMPT_VAL_DIR)/validate_doublequotes.c \
$(PROMPT_VAL_DIR)/validate_parens.c $(PROMPT_VAL_DIR)/validate_utils.c $(PROMPT_VAL_DIR)/structure_jump.c \
$(PROMPT_VAL_DIR)/validate_singlequotes.c $(PROMPT_VAL_DIR)/validate_utils_get_end.c $(PROMPT_VAL_DIR)/validate_utils_identify_structures.c \
$(PROMPT_VAL_DIR)/validate_utils_get_end_skip_inner.c

TOKENIZE_DIR = src/core/lexer/tokenize
EXP_OBJECT_DIR = $(TOKENIZE_DIR)/expandable_object
EXP_OBJECT_FILES = $(EXP_OBJECT_DIR)/expandable_object.c $(EXP_OBJECT_DIR)/expansion_object_utils.c \
$(EXP_OBJECT_DIR)/find_expandable.c $(EXP_OBJECT_DIR)/find_keys_to_expand.c $(EXP_OBJECT_DIR)/find_keys_to_expand_utils.c

SEP_QUOTES_DIR = $(TOKENIZE_DIR)/separate_quote_chuncks
SEP_QUOTES_FILES = $(SEP_QUOTES_DIR)/separate_quote_chuncks.c $(SEP_QUOTES_DIR)/separate_quote_chuncks_utils.c \
$(SEP_QUOTES_DIR)/separate_quote_chunck_session.c

TOKENIZE_FILES = $(EXP_OBJECT_FILES) $(SEP_QUOTES_FILES) $(TOKENIZE_DIR)/build_expansion.c $(TOKENIZE_DIR)/build_expansion_utils.c \
$(TOKENIZE_DIR)/build_expansion_result.c $(TOKENIZE_DIR)/token.c $(TOKENIZE_DIR)/tokenize.c

LEXER_FILES = $(SPLITTER_FILES) $(PROMPT_VAL_FILES) $(TOKENIZE_FILES) \
src/core/lexer/lexer.c src/core/lexer/lexer_utils.c src/core/lexer/properties.c

# ------------ PARSER FILES -----------------
PARSER_DIR = src/core/parser
AST_DIR = $(PARSER_DIR)/ast

AST_BUILD_DIR = $(PARSER_DIR)/ast_build
AST_BUILD_FILES = $(AST_BUILD_DIR)/ast_build_cmd.c $(AST_BUILD_DIR)/ast_build_composition.c $(AST_BUILD_DIR)/ast_build_redirects.c \
$(AST_BUILD_DIR)/ast_build_utils.c $(AST_BUILD_DIR)/ast_build.c $(AST_BUILD_DIR)/lexer_manipulation.c

SYNTAX_DIR = $(PARSER_DIR)/syntactic_analysis
SYNTAX_FILES = $(SYNTAX_DIR)/analyse_logic_node.c $(SYNTAX_DIR)/analyse_pipe_node.c \
$(SYNTAX_DIR)/analyse_redirect_node.c $(SYNTAX_DIR)/syntactic_analysis.c $(SYNTAX_DIR)/analyse_subshell_node.c \
$(SYNTAX_DIR)/analyse_cmd_node.c

PARSER_FILES = $(AST_BUILD_FILES) $(SYNTAX_FILES) $(AST_DIR)/ast.c $(AST_DIR)/print_ast.c $(AST_DIR)/properties.c \
$(PARSER_DIR)/parser.c


# ------------ STRUCTURE FILES -----------------
STRUCTURES = src/data_structures/linkedlist/iteration.c src/data_structures/linkedlist/linkedlist_node.c src/data_structures/linkedlist/linkedlist.c \
src/data_structures/linkedlist_array/linkedlist_array.c src/data_structures/hashtable/hashtable.c \
src/data_structures/binary_tree/binary_tree_node.c src/data_structures/binary_tree/binary_tree.c

# ----------------- EXECUTER FILES -----------------
EXEC_DIR = src/core/executer

# ..... BUILTINS FILES .....
BUILTINS = $(EXEC_DIR)/builtins/ft_env.c $(EXEC_DIR)/builtins/ft_export.c $(EXEC_DIR)/builtins/ft_export_ii.c \
$(EXEC_DIR)/builtins/ft_set.c $(EXEC_DIR)/builtins/ft_unset.c $(EXEC_DIR)/builtins/builtins.c \
$(EXEC_DIR)/builtins/ft_cd.c $(EXEC_DIR)/builtins/ft_pwd.c $(EXEC_DIR)/builtins/ft_echo.c \
$(EXEC_DIR)/builtins/ft_exit.c

# ..... PROCESS FILES .....
PROCESS = $(EXEC_DIR)/process/child_process.c

# ..... ENV FILES .....
ENV = $(EXEC_DIR)/env/env.c $(EXEC_DIR)/env/expand_var.c $(EXEC_DIR)/env/expand_glob_i.c $(EXEC_DIR)/env/expand_glob_ii.c $(EXEC_DIR)/env/expand_glob_iii.c

EXECUTER = $(EXEC_DIR)/find_path.c $(EXEC_DIR)/cmd_i.c $(EXEC_DIR)/cmd_ii.c $(EXEC_DIR)/cmd_iii.c $(EXEC_DIR)/cmd_ii_build_args.c $(EXEC_DIR)/cmd_ii_get_args.c \
	$(EXEC_DIR)/redirect.c $(EXEC_DIR)/redirect_execute.c $(EXEC_DIR)/pipe.c $(EXEC_DIR)/here_doc_i.c \
	$(EXEC_DIR)/here_doc_ii.c $(EXEC_DIR)/cmd_builtin.c $(EXEC_DIR)/tree.c $(EXEC_DIR)/and.c $(EXEC_DIR)/or.c $(EXEC_DIR)/subshell.c \
	$(EXEC_DIR)/executer.c  \
	$(EXEC_DIR)/mapper/ast_node_props.c $(EXEC_DIR)/mapper/exec.c $(EXEC_DIR)/mapper/argv.c $(EXEC_DIR)/mapper/env.c \
	$(EXEC_DIR)/mapper/fds.c $(EXEC_DIR)/mapper/heredoc.c $(EXEC_DIR)/mapper/redirects.c $(EXEC_DIR)/mapper/mapper_signals.c

# ----------------- SIGNAL FILES -----------------
SIGNAL = src/core/signals/signals_i.c src/core/signals/signals_ii.c

# ----------------- READER FILES -----------------
READER_DIR = src/core/reader
READER = $(READER_DIR)/get_prompt.c $(READER_DIR)/reader.c

UTILS = src/utils/array_str.c src/utils/commands.c src/utils/print.c


SRC_FILES = $(STRUCTURES) $(LEXER_FILES) $(PARSER_FILES) $(BUILTINS) $(READER) $(PROCESS) $(ENV) $(EXECUTER) $(UTILS) $(SIGNAL)




# ============== PROGRAM FILES =================
MAIN_PROGRAM=src/main.c

# ============== PROGRAM DEPENDENCIES =================

# DEPENDENCIES = -lreadline -pie
DEPENDENCIES = -lreadline

# ============== CUSOM SLEEP =================
SLEEP = 0.07

# ============== COMPILATION =================
OBJS = $(SRC_FILES:%.c=%.o)
OBJ_MAIN_PROGRAM = $(MAIN_PROGRAM:%.c=%.o)

COMPILATION_DEPENDENCIES = $(LIBFT) $(OBJS)

TEST_PROGRAMS = linkedlist linkedlist_array binary_tree raw_splitter refined_splitter \
env_ht_op child_process prompt_validator find_expandable find_keys_to_expand \
create_expandable_object build_expansion  find_path expand_var_test expand_glob_test \
lexer ast_build parser




# ***************************************************************************************************
# ********************************************           ********************************************
# ********************************************  TARGETS  ********************************************
# ********************************************           ********************************************
# ***************************************************************************************************

all: $(INSTALL_PATH) stats


$(INSTALL_PATH): $(NAME)
	@mkdir -p $(DESTDIR)
	@install -m 755 $(NAME) $(DESTDIR)/

stats:
	@printf "$(BOLD)$(LIGHT_CYAN)src stats:$(RESET)\n"
#	=================== FILES AMOUNT INFO =====================
	@printf " - Total Files:$(BOLD) "
	@printf "%s\n$(RESET)" $(shell find src -type f ! -name '*.o' | wc -l)

	@printf "    * Total Images:$(BOLD) "
	@printf "%8s\n$(RESET)" $(shell find src \( -name "*.png" -o -name "*.jpg -o -name "*.jpeg -o -name "*.webp""" \) | wc -l) | tr ' ' '.'

	@printf "    * Total READMEs:$(BOLD) "
	@printf "%7s\n$(RESET)" $(shell find src -name "README.md" | wc -l) | tr ' ' '.'

	@printf "    * Total .h Files:$(BOLD) "
	@printf "%6s\n$(RESET)" $(shell find src -name "*.h" | wc -l) | tr ' ' '.'

	@printf "    * Total .c Files:$(BOLD) "
	@printf "%6s\n$(RESET)" $(shell find src -name "*.c" | wc -l) | tr ' ' '.'
#	=================== LINES WRITTEN INFO =====================
	@printf "\n - Lines Written *.{c,h}:$(BOLD) "
	@printf "%s\n$(RESET)" $(shell cat $(shell find src \( -name "*.c" -o -name "*.h" \)) | wc -l)

	@printf "    * Lines Written *.c:$(BOLD) "
	@printf "%8s\n$(RESET)" $(shell cat $(shell find src -name "*.c") | wc -l) | tr ' ' '.'

	@printf "    * Lines Written *.h:$(BOLD) "
	@printf "%8s\n$(RESET)" $(shell cat $(shell find src -name "*.h") | wc -l) | tr ' ' '.'
#	=================== CONCLUSION =====================
	@printf "\n - Conclusion:$(BOLD) "
	@printf "%s\n$(RESET)" "Best Minishell Ever"

$(NAME): $(COMPILATION_DEPENDENCIES) $(OBJ_MAIN_PROGRAM)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) $(OBJS) $(OBJ_MAIN_PROGRAM) $(LIBFT)  -o $@ $(DEPENDENCIES)

$(LIBFT):
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(LIBFT_DIR) SLEEP="$(SLEEP)"



tests: fclean find_expandable find_keys_to_expand create_expandable_object \
linkedlist linkedlist_array binary_tree raw_splitter refined_splitter prompt_validator build_expansion \
find_path expand_var_test expand_glob_test env_ht_op lexer

	@clear && echo "code% make tests"

#	=================== LEXER TESTS =====================
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)lexer$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./lexer

#	=================== EXPANSION TESTS =====================
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)find_expandable$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./find_expandable

	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)find_keys_to_expand$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./find_keys_to_expand

	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)create_expandable_object$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./create_expandable_object

	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)build_expansion$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./build_expansion

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
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)binary_tree$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./binary_tree

#	=================== ENV & EXPORT TESTS =====================
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)env_ht_op$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./env_ht_op
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)find_path$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./find_path
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)expand_var_test$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --leak-check=full ./expand_var_test
	@echo "$(LIGHT_GREEN)$(BOLD)testting$(RESET) $(LIGHT_CYAN)expand_glob_test$(RESET)..." && sleep $(SLEEP)
	@valgrind -q --track-origins=yes --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp --leak-check=full ./expand_glob_test


linkedlist: tests/data_structures/linkedlist.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/data_structures/linkedlist.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

linkedlist_array: tests/data_structures/linkedlist_array.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/data_structures/linkedlist_array.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

binary_tree: tests/data_structures/binary_tree.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/data_structures/binary_tree.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

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

find_path: tests/find_path.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/find_path.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

expand_var_test: tests/expand_var_test.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/expand_var_test.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

expand_glob_test: tests/expand_glob_test.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/expand_glob_test.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

find_expandable: tests/lexer/tokenize/find_expandable.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/lexer/tokenize/find_expandable.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

find_keys_to_expand: tests/lexer/tokenize/find_keys_to_expand.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/lexer/tokenize/find_keys_to_expand.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

create_expandable_object: tests/lexer/tokenize/create_expandable_object.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/lexer/tokenize/create_expandable_object.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

build_expansion: tests/lexer/tokenize/build_expansion.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/lexer/tokenize/build_expansion.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

lexer: tests/lexer/lexer.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/lexer/lexer.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

ast_build: tests/parser/ast_build.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/parser/ast_build.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

parser: tests/parser/parser.c tests/tests.c $(COMPILATION_DEPENDENCIES)
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$@$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) tests/parser/parser.c tests/tests.c $(OBJS) $(LIBFT) -o $@ $(DEPENDENCIES)

run_valgrind:
	@valgrind -q --track-origins=yes --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp --leak-check=full ./minishell

%.o: %.c
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./$<$(RESET)..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) -c $< -o $@


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

.PHONY: all clean fclean re

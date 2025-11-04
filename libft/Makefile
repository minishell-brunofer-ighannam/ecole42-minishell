BOLD=\033[1m
RESET=\033[0m
LIGHT_RED=\033[91m
LIGHT_GREEN=\033[92m
LIGHT_CYAN=\033[96m

NAME = libft.a
# ------------------------ Dependencies -------------------------------
STACK_PATH = src/lists/stack
STACK = $(STACK_PATH)/libstack.a
# ----------
LIBSTR_PATH = src/libstr
LIBSTR = $(LIBSTR_PATH)/libstr.a
# ----------
LIBGNL_PATH = src/libgnl
LIBGNL = $(LIBGNL_PATH)/libgnl.a
# ------------------------ Commands -------------------------------
INCLUDES = -I ./includes -I $(STACK_PATH)/includes -I $(LIBSTR_PATH)/includes -I $(LIBGNL_PATH)/includes
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDES)
SLEEP = 0.07
# ------------------------ Paths / files -------------------------------
SRC_FILES = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c \
			ft_memcmp.c ft_calloc.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c \
			ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c \
			ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJ = obj
OBJ_FILES := $(SRC_FILES:%.c=$(OBJ)/%.o)
DEPENDENCY_OBJS = dependency_objs
DEPENDENCY_LIBS = $(STACK) $(LIBSTR) $(LIBGNL)
DEPENDENCY_INCLUDES = dependency_includes

# ******************* Main targets *******************
all: $(DEPENDENCY_LIBS) $(OBJ) $(DEPENDENCY_OBJS) $(NAME)

$(NAME): $(DEPENDENCY_INCLUDES) $(OBJ_FILES)
# -------------- copying includes -----------------------------------------
	@echo ">> $(BOLD)copying inludes$(RESET) from '$(LIGHT_CYAN)./libft/$(STACK_PATH)$(RESET)' to '$(LIGHT_CYAN)$(DEPENDENCY_INCLUDES)$(RESET)'..." && sleep $(SLEEP)
	@cp -rf $(STACK_PATH)/includes/* $(DEPENDENCY_INCLUDES)
	@echo ">> $(BOLD)copying inludes$(RESET) from '$(LIGHT_CYAN)./libft/$(LIBSTR_PATH)$(RESET)' to '$(LIGHT_CYAN)$(DEPENDENCY_INCLUDES)$(RESET)'..." && sleep $(SLEEP)
	@cp -rf $(LIBSTR_PATH)/includes/* $(DEPENDENCY_INCLUDES)
	@echo ">> $(BOLD)copying inludes$(RESET) from '$(LIGHT_CYAN)./libft/$(LIBGNL_PATH)$(RESET)' to '$(LIGHT_CYAN)$(DEPENDENCY_INCLUDES)$(RESET)'..." && sleep $(SLEEP)
	@cp -rf $(LIBGNL_PATH)/includes/* $(DEPENDENCY_INCLUDES)
# -------------- extracting 'files.o' -----------------------------------------
	@echo ">> $(BOLD)extracting 'files.o'$(RESET) from '$(LIGHT_CYAN)./libft/$(STACK)$(RESET)' to '$(LIGHT_CYAN)$(DEPENDENCY_OBJS)$(RESET)'..." && sleep $(SLEEP)
	@ar x $(STACK) --output $(DEPENDENCY_OBJS)
	@echo ">> $(BOLD)extracting 'files.o'$(RESET) from '$(LIGHT_CYAN)./libft/$(LIBSTR)$(RESET)' to '$(LIGHT_CYAN)$(DEPENDENCY_OBJS)$(RESET)'..." && sleep $(SLEEP)
	@ar x $(LIBSTR) --output $(DEPENDENCY_OBJS)
	@echo ">> $(BOLD)extracting 'files.o'$(RESET) from '$(LIGHT_CYAN)./libft/$(LIBGNL)$(RESET)' to '$(LIGHT_CYAN)$(DEPENDENCY_OBJS)$(RESET)'..." && sleep $(SLEEP)
	@ar x $(LIBGNL) --output $(DEPENDENCY_OBJS)
# -------------- compiling 'libft.a' -----------------------------------------
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./libft/$@$(RESET)..." && sleep $(SLEEP)
	@ar rcs $@ $(OBJ_FILES) $(DEPENDENCY_OBJS)/*.o
# ****************************************************

# ------------- Dependency libs -------------
$(STACK):
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./libft/$@$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(STACK_PATH)

$(LIBSTR):
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./libft/$@$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(LIBSTR_PATH)

$(LIBGNL):
	@echo "$(LIGHT_GREEN)>> $(BOLD)compiling$(RESET) $(LIGHT_CYAN)./libft/$@$(RESET)..." && sleep $(SLEEP)
	@make -s -C $(LIBGNL_PATH)
# --------------------------------------------

# ------------- Obrigatory files on root -------------
$(OBJ):
	@echo ">> $(BOLD)creatting $(LIGHT_CYAN)./libft/$@$(RESET) folder..." && sleep $(SLEEP)
	@mkdir $(OBJ)

$(DEPENDENCY_OBJS):
	@echo ">> $(BOLD)creatting $(LIGHT_CYAN)./libft/$@$(RESET) folder..." && sleep $(SLEEP)
	@mkdir $(DEPENDENCY_OBJS)

$(DEPENDENCY_INCLUDES):
	@echo ">> $(BOLD)creatting $(LIGHT_CYAN)./libft/$@$(RESET) folder..." && sleep $(SLEEP)
	@mkdir $(DEPENDENCY_INCLUDES)
# -----------------------------------------------------

$(OBJ)/%.o: %.c
# @echo ">> compiling $< file..." && sleep $(SLEEP)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(LIGHT_RED)>> $(BOLD)cleanning$(RESET) '$(LIGHT_CYAN)./libft/$(STACK_PATH)$(RESET)'..." && sleep $(SLEEP)
	@make -s -C $(STACK_PATH) clean
	@echo "$(LIGHT_RED)>> $(BOLD)cleanning$(RESET) '$(LIGHT_CYAN)./libft/$(LIBSTR_PATH)$(RESET)'..." && sleep $(SLEEP)
	@make -s -C $(LIBSTR_PATH) clean
	@echo "$(LIGHT_RED)>> $(BOLD)cleanning$(RESET) '$(LIGHT_CYAN)./libft/$(LIBGNL_PATH)$(RESET)'..." && sleep $(SLEEP)
	@make -s -C $(LIBGNL_PATH) clean
	@echo "$(LIGHT_RED)>> $(BOLD)cleanning$(RESET) '$(LIGHT_CYAN)./libft/$(RESET)'..." && sleep $(SLEEP)
	@rm -rf $(OBJ) $(DEPENDENCY_OBJS) $(DEPENDENCY_INCLUDES)

fclean: clean
	@echo "$(LIGHT_RED)>> $(BOLD)deletting$(RESET) '$(LIGHT_CYAN)./libft/$(STACK)$(RESET)'..." && sleep $(SLEEP)
	@make -s -C $(STACK_PATH) fclean
	@echo "$(LIGHT_RED)>> $(BOLD)deletting$(RESET) '$(LIGHT_CYAN)./libft/$(LIBSTR)$(RESET)'..." && sleep $(SLEEP)
	@make -s -C $(LIBSTR_PATH) fclean
	@echo "$(LIGHT_RED)>> $(BOLD)deletting$(RESET) '$(LIGHT_CYAN)./libft/$(NAME)$(RESET)'..." && sleep $(SLEEP)
	@make -s -C $(LIBGNL_PATH) fclean
	@echo "$(LIGHT_RED)>> $(BOLD)deletting$(RESET) '$(LIGHT_CYAN)./libft/$(NAME)$(RESET)'..." && sleep $(SLEEP)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

NAME = libgnl.a
INCLUDES = -I includes
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDES)

SRC = src
SRC_FILES = get_next_line_utils.c get_next_line.c

OBJ = obj
OBJ_FILES := $(SRC_FILES:%.c=$(OBJ)/%.o)

all: $(NAME)

test: $(NAME)
	@$(CC) $(CFLAGS) test/main.c $(NAME) -o a.out

$(NAME): $(OBJ) $(OBJ_FILES)
	@ar rcs $(NAME) $(OBJ_FILES)

$(OBJ):
	@mkdir $(OBJ)

$(OBJ)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ) a.out

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re so

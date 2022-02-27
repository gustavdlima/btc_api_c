NAME	= cli

CC = gcc
CFLAGS =

INCLUDE = -I ./include

SRC_DIR = ./src
GNL_FOLDER = ./gnl
UTILS_FOLDER = ./utils

SRC = cli.c $(GNL_FOLDER)/get_next_line.c $(UTILS_FOLDER)/utils.c
SRC := $(addprefix $(SRC_DIR)/,$(SRC))

OBJ = $(SRC:%.c=%.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

install: $(NAME)
	cp $(NAME) /usr/local/bin

re: fclean all

run: re
	./$(NAME)

.PHONY: all clean fclean re

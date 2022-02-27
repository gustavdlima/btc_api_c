NAME	= server

CC		=	gcc
CFLAGS	=	-g -Wall -Wextra
LIBS	= -lcurl -DMG_ENABLE_OPENSSL=1 -lssl -lcrypto
INCLUDE =	-I ./include

BTC_DATA = ./btc_data.txt

S_FOLDER = ./src/
L_FOLDER = ./libs
GNL_FOLDER = ./gnl
UTILS_FOLDER = ./utils
ROUTE_FOLDER = ./route
M_FOLDER = ./libs/mongoose
LOG_FOLDER = ./log_src
API_REQUESTER_FOLDER = ./external_api_requester

HEADER	= ./include/server.h

SRC =			$(addprefix $(S_FOLDER), \
		 server.c \
		 $(M_FOLDER)/mongoose.c \
		 $(ROUTE_FOLDER)/route.c \
		 $(UTILS_FOLDER)/utils.c \
		 $(API_REQUESTER_FOLDER)/api_requester.c \
		 $(LOG_FOLDER)/log.c \
		 $(LOG_FOLDER)/log_utils.c \
		 $(GNL_FOLDER)/get_next_line.c \
)

OBJ = $(SRC:%.c=%.o)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c $< -o $(<:%.c=%.o)


all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	rm -rf $(NAME)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) $(BTC_DATA)

re: fclean all

run: re
	./$(NAME)

tls:
	make MBEDTLS_DIR=/path/to/your/mbedtls/installation

.PHONY: all clean fclean re push run tls

SERVER_NAME = server

CLIENT_NAME = client

SERVER_SRCS	= server.c server_utils.c

CLIENT_SRCS	= client.c client_utils.c

CC = clang

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SERVER_OBJS = $(SERVER_SRCS:.c=.o)

CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) -o $(SERVER_NAME) $(SERVER_OBJS)

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJS)

clean:
	$(RM) $(SERVER_OBJS)
	$(RM) $(CLIENT_OBJS)

fclean:	clean
	$(RM) $(SERVER_NAME)
	$(RM) $(CLIENT_NAME)

re:	fclean all

.PHONY: .c.o all clean fclean re

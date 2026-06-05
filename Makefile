NAME = Retro-MFA
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SOURCES = main.c
OBJECTS = $(SOURCES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -lX11 -lasound -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(NAME) MFA/white1.mfa

runval: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) MFA/white1.mfa

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

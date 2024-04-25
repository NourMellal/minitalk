SRC = client.c server.c error_handler.c

LIBFTDIR = ./ft_libft
LIBFT = $(LIBFTDIR)/libft.a

PRINTFDIR = ./ft_printf
PRINTF = $(PRINTFDIR)/libftprintf.a

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
CC = cc
LDFLAGS = -L$(LIBFTDIR) -lft -L$(PRINTFDIR) -lftprintf

NAME1 = server
NAME2 = client

OBJ = $(SRC:.c=.o)

all: $(NAME1) $(NAME2) $(LIBFT) $(PRINTF)

$(LIBFT):
	make -C $(LIBFTDIR)

$(PRINTF):
	make -C $(PRINTFDIR)

$(NAME1): server.o error_handler.o $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(NAME1) server.o error_handler.o $(LDFLAGS)

$(NAME2): client.o error_handler.o $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(NAME2) client.o error_handler.o $(LDFLAGS)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFTDIR)
	make clean -C $(PRINTFDIR)

fclean: clean
	rm -f $(NAME1) $(NAME2)
	make fclean -C $(LIBFTDIR)
	make fclean -C $(PRINTFDIR)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
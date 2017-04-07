NAME	= get_next

CC		= gcc

LIBFT	= libft/

FLAG	= -Wall -Wextra -Werror -o

SRCS	= $(LIBFT)libft.a \
	   			main.c \
	   			get_next_line.c \
	   			
all:	$(NAME)

$(NAME):
		@$(CC) $(FLAG) $(NAME) $(SRCS) -g

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re

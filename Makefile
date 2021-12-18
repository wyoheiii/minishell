NAME = minishell_command
SRCS = main.c command_main.c my_echo.c my_pwd.c my_exit.c
SRCSD = ./srcs/
ADDSRCS = $(addprefix $(SRCSD),$(SRCS))
OBJS = $(ADDSRCS:.c=.o)
CC	 = gcc
RM	 = rm -f
CFLAGS	= -Wall -Wextra -Werror
LIBFTD = ./libft
LIBFT  = $(LIBFTD)/libft.a
INC	= -I./inc
all:	 $(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):	$(LIBFTD)/*.c
			$(MAKE) -C $(LIBFTD) bonus

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFTD) clean

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(LIBFT)

re:			fclean $(NAME)

.PHONY:		all clean fclean r
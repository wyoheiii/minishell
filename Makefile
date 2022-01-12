NAME = minishell
SRCS = main.c command_main.c my_echo.c my_pwd.c my_exit.c my_cd.c my_env.c \
		env_init.c env_util.c env_util2.c my_export.c my_unset.c \
		god_malloc.c delimiter.c flag.c lexer.c parser.c utils.c token.c sig.c
SRCSD = ./srcs/
ADDSRCS = $(addprefix $(SRCSD),$(SRCS))
OBJS = $(ADDSRCS:.c=.o)
CC	 = gcc
RM	 = rm -f
CFLAGS	= -Wall -Wextra -Werror
LIBFTD = ./libft
LIBFT  = $(LIBFTD)/libft.a
INC	= ./includes
LIBINC = ./libft
all:	 $(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -I$(INC) -I$(LIBINC) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):	$(LIBFTD)/*.c
			$(MAKE) -C $(LIBFTD) bonus

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFTD) clean

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(LIBFT)

re:			fclean $(NAME)

.c.o :
			$(CC) $(CFLAGS) -c -o $@ $< -I$(INC) -I$(LIBINC)

.PHONY:		all clean fclean r
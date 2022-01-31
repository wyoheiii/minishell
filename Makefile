NAME = minishell
SRCS = main.c command_main.c my_echo.c my_pwd.c my_exit.c my_cd.c my_env.c \
		env_init.c env_util.c env_util2.c my_export.c my_unset.c \
		delimiter.c flag.c lexer.c parser.c utils.c token.c sig.c command_util.c \
		multi_command.c error_function.c error_function2.c my_redirect.c
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
RL1 =
RL2 =
RL_ELSE =
#ifeq	($(shell uname), Darwin)
#	RL1 =  -I/usr/local/opt/readline/include
#	RL2=    -L/usr/local/opt/readline/lib -lreadline
#else
#	RL_ELSE = -lreadline
#endif
ifeq	($(shell uname), Darwin)
	RL1 =  -I$(shell brew --prefix readline)/include
	RL2=   -L$(shell brew --prefix readline)/lib -lreadline
else
	RL_ELSE = -lreadline
endif
all:	 $(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS)  -I$(INC) -I$(LIBINC) $(OBJS) $(LIBFT) -o $(NAME) $(RL1) $(RL2) $(RL_ELSE)
#-fsanitize=address
$(LIBFT):	$(LIBFTD)
			$(MAKE) -C $(LIBFTD)

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFTD) clean

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(LIBFT)

re:			fclean $(NAME)

.c.o :
			$(CC) $(CFLAGS)  -c -o $@ $< -I$(INC) -I$(LIBINC) $(RL1)

.PHONY:		all clean fclean r
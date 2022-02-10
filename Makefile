NAME := minishell
SRCS := main.c command_main.c my_echo.c my_pwd.c my_exit.c my_cd.c my_env.c \
		env_init.c env_util.c env_util2.c my_export.c my_unset.c \
		delimiter.c flag.c lexer.c parser.c utils.c token.c sig.c command_util.c \
		multi_command.c error_function.c error_function2.c my_redirect.c \
		list_utils.c libft_utils.c expansion.c expand_struct.c not_param_str.c\
		param.c redirect_list.c my_heredoc.c

SRCSD := ./srcs/

ADDSRCS := $(addprefix $(SRCSD),$(SRCS))

OBJDIR = ./obj
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(ADDSRCS:%.c=%.o)))
#OBJS := $(ADDSRCS:.c=.o)

CC	 := gcc
RM	 := rm -f
CFLAGS	:= -Wall -Wextra -Werror  #-g -fsanitize=address
LIBFTD := ./libft
LIBFT  := $(LIBFTD)/libft.a
INC	:= ./includes
LIBINC := ./libft
#CFLAGS += -Idebug ./debug/debug.c
RL1 :=
RL2 :=
RL_ELSE :=
#ifeq	($(shell uname), Darwin)
#	RL1 =  -I/usr/local/opt/readline/include
#	RL2=    -L/usr/local/opt/readline/lib -lreadline
#else
#	RL_ELSE = -lreadline
#endif
ifeq	($(shell uname), Darwin)
	RL1 :=  -I$(shell brew --prefix readline)/include
	RL2 :=   -L$(shell brew --prefix readline)/lib -lreadline
else
	RL_ELSE := -lreadline
endif


MINISHL_LEAKS	:= minishell_leaks
SRCS_LEAKS	:= ./test/help/leaks.c
INCLUDE_LEAKS := -I./test/help

ifdef LEAKS
NAME := $(MINISHL_LEAKS)
endif



all:	 $(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -I$(INC) -I$(LIBINC) $(OBJS)  $(LIBFT) -o $(NAME) $(RL1) $(RL2) $(RL_ELSE)
#-fsanitize=address
$(LIBFT):	$(LIBFTD)
			$(MAKE) -C $(LIBFTD)

clean:
			$(RM) -r $(OBJDIR)
#			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFTD) clean

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(LIBFT)

re:			fclean $(NAME)

$(OBJDIR)/%.o : $(SRCSD)%.c
	@if [ ! -d $(OBJDIR) ]; then echo "mkdir -p $(OBJDIR)" && mkdir -p $(OBJDIR); fi    
	$(CC) $(CFLAGS)  -c -o $@ $< -I$(INC) -I$(LIBINC) $(RL1)

#.c.o :
#			$(CC) $(CFLAGS)  -c -o $@ $< -I$(INC) -I$(LIBINC) $(RL1)

leaks: $(LIBFT)
	$(MAKE) CFLAGS="$(CFLAGS) -D LEAKS=1" INC="$(INC) $(INCLUDE_LEAKS)" ADDSRCS="$(ADDSRCS) $(SRCS_LEAKS)" LEAKS=TRUE

cleanleaks: clean
	$(RM) ./test/help/leaks.o ./test/help/leaks.d

fcleanleaks: cleanleaks
	$(RM) $(MINISHL_LEAKS)

.PHONY:		all clean fclean r
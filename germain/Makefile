#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 10:59:36 by gtoubol           #+#    #+#              #
#    Updated: 2022/06/20 15:50:25 by gtoubol          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# List of all the sources (.c)
# -------------------------------------------------------------------------

SRCS =		$(addprefix environment/,	environment_copy.c	\
										environment_add.c	\
										environment_remove.c\
										environment_set.c	\
										environment_get.c	\
										environment_format.c\
										environment_var_compare.c \
										ft_newdico.c		\
										ft_freedico.c)		 \
			$(addprefix builtins/,		builtin_echo.c 		\
										builtin_cd.c 		\
										builtin_pwd.c		\
										builtin_export.c	\
										builtin_unset.c		\
										builtin_env.c		\
										builtin_exit.c)		\
			$(addprefix parser/, 		parser.c 			\
										path.c 				\
										split_cmd.c 		\
										split_redirect.c)	\
			$(addprefix lexer/, 		is_prio.c 			\
										is_redirect.c 		\
										is_separator.c		\
										is_word.c			\
										lexer.c				\
										tokens_alloc.c)		\
			$(addprefix utils/, 		display_msg.c 		\
										free.c				\
										ft_atoll.c			\
										ft_join3.c			\
										ft_strndup.c		\
										print2.c			\
										print.c)			\
			$(addprefix execution/,		main.c				\
										interactive_session.c\
										interactive_signals.c\
										run_line.c			\
										run_pipe_series.c	\
										do_redirect.c)

TMP =		$(addprefix tmp/,			ft_lstsort.c)

# List of the related directories
# -------------------------------------------------------------------------
SRCS_DIR =	srcs
HEAD_DIR =	includes libft/includes

# List of all compilation options
# -------------------------------------------------------------------------
CC = 		cc
CFLAGS =	-Wall -Wextra
CDEBUG =	-g3
CRELEASE =	-Werror
CPROFILE =	-pg

# Description of the final target
# -------------------------------------------------------------------------
NAME =		g_minishell

# Libraries
# -------------------------------------------------------------------------
LIBFT_DIR = libft
LIBFT =		libft/libft.a
LIB =		-Llibft -lft -lreadline

# General rules on makefile
# -------------------------------------------------------------------------
OBJS = 		$(addprefix $(SRCS_DIR)/,$(SRCS:.c=.o) $(TMP:.c=.o))
DEPS =		$(OBJS:.o=.d)

INCLUDES =	$(addprefix -I,$(HEAD_DIR))

ifeq (debug, $(filter debug,$(MAKECMDGOALS)))
	CFLAGS += $(CDEBUG)
else ifeq (profile, $(filter profile,$(MAKECMDGOALS)))
	CFLAGS += $(CPROFILE) $(CRELEASE)
else
	CFLAGS += $(CRELEASE)
endif
RM =		rm -f

vpath %.c $(SRCS_DIR):$(TEST_DIR)
vpath %.h $(HEAD_DIR)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIB)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

all:		$(NAME)

clean:		dclean
			$(RM) $(OBJS)

fclean:		clean libfclean tclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus

# Library rules
# -----------------------------------------------------------------------
$(LIBFT):	libft.h
			$(MAKE) -C $(LIBFT_DIR)

libclean:
			$(MAKE) -C $(LIBFT_DIR) clean

libfclean:
			$(MAKE) -C $(LIBFT_DIR) fclean

.PHONY:		libclean libfclean

# Custom rules
# ------------------------------------------------------------------------
TEST_N =	test_malloc

debug:		all
profile:	all
			@echo "\e[36mTo use profiler:"
			@echo "    1. Run your app"
			@echo "    2. grof \e[3m<your-app>\e[0;36m gmon.out > \e[3m<analysis-file>\e[0;36m"
			@echo "    3. cat \e[3m<analysis-file>\e[0m"

test:		$(TEST_N)

$(TEST_N):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIB)

malloc_test:$(OBJS) $(TEST_O) $(LIBFT)
			$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ $(OBJS) $(TEST_O) $(LIB) -L. -lmallocator

t_clean:
			$(RM) $(TEST_N)

.PHONY:		debug profile test tclean

# General dependences management
# ------------------------------------------------------------------------
%.d:		%.c
			$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $(INCLUDES) $< > $@

dclean:
			$(RM) $(DEPS)

.PHONY:		dclean
.SILENT:    $(DEPS) dclean

-include	$(DEPS)

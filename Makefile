# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 10:59:36 by gtoubol           #+#    #+#              #
#    Updated: 2022/07/06 16:59:02 by gtoubol          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# List of all the sources (.c)
# -------------------------------------------------------------------------

SRCS =		$(addprefix environment/,	environment_copy.c	\
										environment_add.c	\
										environment_remove.c\
										environment_set.c	\
										environment_get.c	\
										environment_format.c\
										environment_var_compare.c\
										environment_update.c\
										ft_newdico.c		\
										ft_freedico.c)		\
			$(addprefix signals/,		manage_pid.c		\
										pid_utils.c			\
										interupted.c		\
										last_pid.c			\
										is_father.c)		\
			$(addprefix builtins/,		builtin_echo.c 		\
										builtin_cd.c 		\
										builtin_pwd.c		\
										builtin_export.c	\
										builtin_unset.c		\
										builtin_env.c		\
										builtin_exit.c		\
										is_builtin.c)		\
			$(addprefix parser/, 		parser.c 			\
										parser2.c			\
										path.c 				\
										split_cmd.c 		\
										split_redirect.c)	\
			$(addprefix lexer/, 		is_prio.c 			\
										is_redirect.c 		\
										is_separator.c		\
										is_word.c			\
										is_word2.c			\
										lexer.c				\
										tokens_alloc.c)		\
			$(addprefix utils/, 		display_msg.c 		\
										free.c				\
										ft_atoll.c			\
										ft_join3.c			\
										ft_strndup.c		\
										print2.c			\
										print.c				\
										ft_lst_remove_if.c	\
										str_utils.c			\
										quicksort.c			\
										lst_to_tab.c		\
										split_in_lst.c		\
										lst_str_utils.c		\
										ft_list_at.c		\
										ft_lst_remove_at.c	\
										strjoin_custom.c	\
										trim_c.c			\
										debug_gnl.c			\
										ft_join_tab.c		\
										ft_strnjoin.c		\
										clean_hdoc.c)		\
			$(addprefix parser/astree/,	astree.c			\
										astree_utils.c		\
										fill_astree.c\
										display_tree.c\
										rec_astree.c)		\
			$(addprefix execution/,		main.c				\
										interactive_session.c\
										interactive_signals.c\
										run_line.c			\
										do_redirect.c		\
										do_redirect_hdoc.c	\
										redirect_name.c		\
										do_bind_pipe.c		\
										run_child.c			\
										run_parent.c		\
										exec_process.c		\
										get_exec_path.c		\
										wait_all.c			\
										run_builtin.c		\
										run_tree_exec.c		\
										cmd_status.c)		\
			$(addprefix tree_execution/,count_wait_tree.c	\
										exec_tree_and.c		\
										exec_tree.c			\
										exec_tree_cmd.c		\
										exec_tree_or.c		\
										exec_tree_pipe.c	\
										exec_tree_add_level.c)\
			$(addprefix cleanable/,		cleanable_add_pipe.c\
										cleanable_pop_pipe.c\
										clear_cleanable.c	\
										cleanable_close_pipes.c)\
			$(addprefix expand/,							\
			$(addprefix wildcard/,		wildcard.c			\
										update_wc.c			\
										prefix_suffix.c		\
										new_wc.c			\
										rec_wc.c			\
										lst_utils.c			\
										dir_utils.c			\
										wc_utils.c			\
										sort_lst.c			\
										expand_wc.c)		\
			$(addprefix	variable/,		var_expand.c		\
										split_var.c			\
										var_expand_wc.c		\
										get_var.c)			\
			$(addprefix quotes/,		expand_quotes.c)	\
			$(addprefix hdoc/,			get_hdoc.c			\
										set_hdoc.c			\
										read_hdoc.c			\
										quotes_hdoc.c		\
										tmp_filename.c)		\
										expand.c			\
										expand_loop.c		\
										expand_utils.c)

TMP =		$(addprefix tmp/,			ft_lstsort.c		\
										astree_apply_infix.c\
										ft_atoll_protected.c)

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
NAME =		minishell

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
	CFLAGS += $(CRELEASE) -g
endif
RM =		rm -f

vpath %.c $(SRCS_DIR)
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
debug:		all
profile:	all
			@echo "\e[36mTo use profiler:"
			@echo "    1. Run your app"
			@echo "    2. grof \e[3m<your-app>\e[0;36m gmon.out > \e[3m<analysis-file>\e[0;36m"
			@echo "    3. cat \e[3m<analysis-file>\e[0m"

malloc_test:$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) -fsanitize=undefined -rdynamic -o $@ $(OBJS) $(LIB) -L. -lmallocator

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

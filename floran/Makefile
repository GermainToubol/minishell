# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/03 14:23:03 by fmauguin          #+#    #+#              #
#    Updated: 2022/06/21 18:59:17 by fmauguin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL				=	/bin/sh

PROGNAME			:=	minishell

LIBFT				:=	../commun/libft/libft.a
LIBFTDIR			:=	../commun/libft/includes

INCLUDEDIR			:=	../commun/includes
SRCDIR				:=	../commun/srcs

OBJDIR				:=	./obj
DEBUGDIR			:=	./debugobj

LEXERSRC			:=	lexer/lexer.c					\
						lexer/is_separator.c			\
						lexer/is_redirect.c				\
						lexer/is_word.c					\
						lexer/is_word2.c				\
						lexer/is_prio.c					\
						lexer/tokens_alloc.c			\

PARSERSRC			:=	parser/main.c					\
						parser/parser.c					\
						parser/parser2.c				\
						parser/path.c					\
						parser/split_redirect.c			\
						parser/split_cmd.c				\

UTILSSRC			:=	utils/ft_atoll.c				\
						utils/ft_strndup.c				\
						utils/print.c					\
						utils/print2.c					\
						utils/display_msg.c				\
						utils/ft_join3.c				\
						utils/ft_strcmp.c				\
						utils/ft_lst_remove_if.c		\
						utils/free.c					\

TREESRC				:=	astree/astree.c					\
						astree/astree_utils.c			\
						astree/fill_astree.c			\
						astree/display_tree.c			\

EXPANDSRC			:=	expand/wildcard.c				\
						expand/lst_utils.c				\
						expand/ft_lst_sort_custom.c		\
						expand/wc_utils.c				\
						expand/prefix_suffix.c			\
						expand/update_wc.c				\
						expand/rec_wc.c					\
						expand/main.c					\
						expand/expand.c					\
						expand/lst_to_tab.c				\

CC					:=	cc
RM					:=	rm

CCFLAGS				:=	-Wall -Wextra -Werror
LIBFLAGS			:=	-lreadline
OPTFLAG				:=	-g

NAME				:=	$(PROGNAME)
WILDCARD			:=	wildcard

OUTDIR				:=	$(OBJDIR)

DEBUGNAME			:= $(addsuffix .debug,$(PROGNAME))

ifdef DEBUG
	OPTFLAG 		:=	-g
	LIBFT			:=	$(addsuffix .debug,$(LIBFT))
	NAME			:=	$(DEBUGNAME)
	BONUSNAME		:=	$(BONUSDEBUGNAME)
	OUTDIR			:=	$(DEBUGDIR)
endif

$(OUTDIR)/%.o		:	$(SRCDIR)/%.c | $(OUTDIR)
	@mkdir -p $(dir $@)
	$(CC) -c -MMD -MP $(CCFLAGS) $(OPTFLAG) $(addprefix -I ,$(INCLUDEDIR)) $(addprefix -I ,$(LIBFTDIR)) $< -o $@

$(NAME)				:	$(addprefix $(OUTDIR)/,$(LEXERSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(PARSERSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(TREESRC:.c=.o)) $(LIBFT)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(NAME) $(addprefix $(OUTDIR)/,$(LEXERSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(PARSERSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(TREESRC:.c=.o)) $(LIBFT) $(LIBFLAGS)

$(WILDCARD)			:	$(addprefix $(OUTDIR)/,$(EXPANDSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(WILDCARD) $(addprefix $(OUTDIR)/,$(EXPANDSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(LIBFLAGS)

all					:	$(NAME)

malloc_test			:	$(addprefix $(OUTDIR)/,$(EXPANDSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT)
	$(CC) $(CFLAGS) $(OPTFLAG) -fsanitize=undefined -rdynamic -o $@ $(addprefix $(OUTDIR)/,$(EXPANDSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(LIBFLAGS) -L. -lmallocator

$(DEBUGNAME)		:
ifndef DEBUG
	$(MAKE) $(DEBUGNAME) DEBUG=1
endif


ifdef DEBUG
$(PROGNAME)			:	$(NAME)
endif

debug				:
ifndef DEBUG
	$(MAKE) DEBUG=1
endif

ifdef LIBFT
$(LIBFT)			:
	$(MAKE) -j -C $(dir $(LIBFT)) $(notdir $(LIBFT))
endif

$(OUTDIR)			:
	mkdir $(OUTDIR)

clean				:
ifdef LIBFT
	$(MAKE) -j -C $(dir $(LIBFT)) fclean
endif
	$(RM) -rf $(OBJDIR) $(DEBUGDIR)

fclean				:	clean
	$(RM) -f $(PROGNAME) $(DEBUGNAME)

re					:	fclean
	$(MAKE) $(NAME)

.PHONY				:	all bonus clean fclean re

-include	$(addprefix $(OUTDIR)/,$(LEXERSRC:.c=.d))
-include	$(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.d))
-include	$(addprefix $(OUTDIR)/,$(PARSERSRC:.c=.d))
-include	$(addprefix $(OUTDIR)/,$(TREESRC:.c=.d))
-include	$(addprefix $(OUTDIR)/,$(EXPANDSRC:.c=.d))
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/03 14:23:03 by fmauguin          #+#    #+#              #
#    Updated: 2022/06/15 15:41:12 by fmauguin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL				=	/bin/sh

PROGNAME			:=	minishell

LIBFT				:=	../commun/libft/libft.a
LIBFTDIR			:=	../commun/libft/includes

INCLUDEDIR			:=	./includes
SRCDIR				:=	.

OBJDIR				:=	./obj
DEBUGDIR			:=	./debugobj

LEXERSRC			:=	lexer/lexer.c				\
						lexer/utils.c				\
						lexer/is_separator.c		\
						lexer/is_redirect.c			\
						lexer/is_word.c				\
						lexer/is_prio.c				\
						lexer/tokens_alloc.c		\
						lexer/free.c				\

PARSERSRC			:=	parser/main.c				\
						parser/parser.c				\

CC					:=	cc
RM					:=	rm

CCFLAGS				:=	-Wall -Wextra -Werror
LIBFLAGS			:=	-lreadline
OPTFLAG				:=

NAME				:=	$(PROGNAME)

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

$(NAME)				:	$(addprefix $(OUTDIR)/,$(LEXERSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(PARSERSRC:.c=.o)) $(LIBFT)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(NAME) $(addprefix $(OUTDIR)/,$(LEXERSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(PARSERSRC:.c=.o)) $(LIBFT) $(LIBFLAGS)

all					:	$(NAME)

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
	$(MAKE) -C $(dir $(LIBFT)) $(notdir $(LIBFT))
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
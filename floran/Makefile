# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/03 14:23:03 by fmauguin          #+#    #+#              #
#    Updated: 2022/06/16 01:45:06 by fmauguin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL				=	/bin/sh

PROGNAME			:=	minishell

LIBFT				:=	../commun/libft/libft.a
LIBFTDIR			:=	../commun/libft/includes

INCLUDEDIR			:=	./includes ../commun/
SRCDIR				:=	.

OBJDIR				:=	./obj
DEBUGDIR			:=	./debugobj

LEXERSRC			:=	lexer/lexer.c				\
						lexer/is_separator.c		\
						lexer/is_redirect.c			\
						lexer/is_word.c				\
						lexer/is_prio.c				\
						lexer/tokens_alloc.c		\

PARSERSRC			:=	parser/main.c				\
						parser/parser.c				\
						parser/path.c				\
						parser/split_redirect.c		\
						parser/split_cmd.c			\

UTILSSRC			:=	utils/ft_atoll.c			\
						utils/ft_strndup.c			\
						utils/print.c				\
						utils/display_msg.c			\
						utils/ft_join3.c			\
						utils/free.c				\

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

$(NAME)				:	$(addprefix $(OUTDIR)/,$(LEXERSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(PARSERSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT)
	$(CC) $(CCFLAGS) $(OPTFLAG) -o $(NAME) $(addprefix $(OUTDIR)/,$(LEXERSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(PARSERSRC:.c=.o)) $(addprefix $(OUTDIR)/,$(UTILSSRC:.c=.o)) $(LIBFT) $(LIBFLAGS)

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
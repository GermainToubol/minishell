#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 10:59:36 by gtoubol           #+#    #+#              #
#    Updated: 2022/06/13 15:45:37 by gtoubol          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# List of all the sources (.c)
# -------------------------------------------------------------------------
SRCS =		g_main.c interactive_session.c non_interactive_session.c

# List of the related directories
# -------------------------------------------------------------------------
SRCS_DIR =	srcs
HEAD_DIR =	includes libft/includes

# List of all compilation options
# -------------------------------------------------------------------------
CC = 		gcc
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
OBJS = 		$(addprefix $(SRCS_DIR)/,$(SRCS:.c=.o))
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

vpath %.c $(SRCS_DIR)
vpath %.h $(HEAD_DIR)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIB)


$(NAME_B):	$(OBJS_B) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS_B) $(LIB)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $< $(LIB)

all:		$(NAME)

clean:		dclean
			$(RM) $(OBJS)

fclean:		clean libfclean
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

.PHONY:		debug profile

# General dependences management
# ------------------------------------------------------------------------
%.d:		%.c
			$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $(INCLUDES) $< $(LIB) > $@

dclean:
			$(RM) $(DEPS)

.PHONY:		dclean
.SILENT:    $(DEPS) dclean

-include	$(DEPS)

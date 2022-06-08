#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/16 16:41:38 by gtoubol           #+#    #+#              #
#    Updated: 2022/06/06 10:28:58 by gtoubol          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# List of all the sources (.c)
# -------------------------------------------------------------------------
SRCS =		ft_atoi.c ft_bzero.c ft_calloc.c ft_fprintf.c ft_free_split.c	\
			ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c				\
			ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c		\
			ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c			\
			ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memchr.c ft_memcmp.c	\
			ft_memcpy.c ft_memmove.c ft_memset.c ft_printf.c				\
			ft_printf_char.c ft_printf_formatify.c ft_printf_hex.c			\
			ft_printf_hex_base.c ft_printf_hex_caps.c ft_printf_int.c		\
			ft_printf_long_hex.c ft_printf_padding.c ft_printf_percent.c	\
			ft_printf_precision.c ft_printf_ptr.c ft_printf_str.c			\
			ft_printf_unsigned.c ft_putchar_fd.c ft_putendl_fd.c			\
			ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c			\
			ft_strcmp.c ft_strdup.c ft_striteri.c ft_strjoin.c				\
			ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c				\
			ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c				\
			ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c			\
			get_next_line_fds.c get_next_line_utils_fds.c

# List of the related directories
# -------------------------------------------------------------------------
SRCS_DIR =	srcs
HEAD_DIR =	includes

# List of all compilation options
# -------------------------------------------------------------------------
CC = 		gcc
CFLAGS =	-Wall -Wextra
CDEBUG =	-g3
CRELEASE =	-Werror
CPROFILE =	-pg

# Description of the final target
# -------------------------------------------------------------------------
NAME =		libft.a

# General rules on makefile
# -------------------------------------------------------------------------
OBJS =		$(addprefix $(SRCS_DIR)/,$(SRCS:.c=.o))
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

$(NAME):	$(OBJS)
			ar rcs $@ $?

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

all:		$(NAME)

clean:		dclean
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

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
			$(CC) -MM -MT $(@:.d=.o) $(CFLAGS) $(INCLUDES) $< > $@

dclean:
			$(RM) $(DEPS)

.PHONY:		dclean
.SILENT:    $(DEPS) dclean

-include	$(DEPS)

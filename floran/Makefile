# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/03 14:23:03 by fmauguin          #+#    #+#              #
#    Updated: 2022/06/09 13:50:36 by fmauguin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	parse

CC			=	cc
CFLAGS	=	-Wall -Wextra -Werror -g3 -I./ -I$(INCLUDE) -I$(LIBFT_DIR)/includes

RM			=	rm -rf

INCLUDE		=	../commun
SRC_DIR		=	srcs/
OBJ_DIR		=	obj/
SRC_FILES	=	main
SRC			=	$(addsuffix .c, $(addprefix $(SRC_DIR), $(SRC_FILES)))
OBJ			=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

LIBFT_DIR	=	../commun/libft/

RED = \033[0;31m
GREEN = \033[0;32m
NONE = \033[0m


$(NAME):	$(OBJ)
			@make -C $(LIBFT_DIR)
			@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $@
			@printf "\t[ $(GREEN)✔$(NONE) ] "$@" done\n\n"
			@printf "$(GREEN)Compiled "$@" successfully!\n $(NONE)\n"

$(OBJ):		$(OBJ_DIR)%.o : $(SRC_DIR)%.c
			@mkdir -p ${OBJ_DIR}
			@$(CC) $(CFLAGS) -c $< -o $@
			@printf "\t[ $(GREEN)✔$(NONE) ] "$@" done\n"

all:		$(NAME)

bonus:		$(BONUS_NAME)

clean:
			@if \
			test -d "./$(OBJ_DIR)"; \
			then \
			${RM} $(OBJ_DIR); \
			printf "\t[ $(RED)✗$(NONE) ] ./$(OBJ_DIR) deleted\n"; \
			fi

fclean:		clean
			@if \
			test -f "./$(NAME)"; \
			then \
			${RM} $(NAME); \
			printf "\t[ $(RED)✗$(NONE) ] ./$(NAME) deleted\n\n"; \
			fi
			@printf "$(RED)"$@" successful!\n $(NONE)\n"

libft_clean:
			make clean -C $(LIBFT_DIR)

libft_fclean:	libft_clean
			make fclean -C $(LIBFT_DIR)

re: 		fclean all

.PHONY: 	clean fclean all re NAME

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: squiquem <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/23 19:01:27 by squiquem          #+#    #+#              #
#    Updated: 2019/03/04 22:17:08 by squiquem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY			:	all clean fclean re opti

NAME			=	rtv1

SRC_DIR			=	./sources/

OBJ_DIR			=	./objects/

CPPFLAGS 		=	-I includes/

SRC_FILES		=	draw.c \
					main.c \
					vec.c \
					vec2.c \
					hit_items.c \
					hit_func.c \
					ray.c \
					find_closest.c \
					find_normal.c \
					light.c \
					parsing.c \
					parsing2.c \
					parsing_items.c \
					rotate.c \
					new.c

OBJ_FILES		=	$(SRC_FILES:.c=.o)

OBJ_D_FILES		=	$(SRC_FILES:.c=.d)

SRC				=	$(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJ				=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

OBJ_D			=	$(addprefix $(OBJ_DIR), $(OBJ_D_FILES))

LFT				=	-L libft/ -lft

MLX				=	-L minilibx/ -lmlx -framework OpenGL -framework AppKit

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -MMD -O3

opti			:
	@make -j8 all

all				:
	@make all -C libft/
	@make all -C minilibx/
	@make $(NAME)

$(NAME)			:	$(OBJ)
	@$(CC) $(CFLAGS) $(LFT) $(MLX) $(OBJ) -o $@ 
	@printf '\033[4m'
	@printf "\033[32m[ ✔ ] $(NAME)\n\033[0m"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
	@mkdir $(OBJ_DIR) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@printf '\033[0m[ ✔ ] %s\n\033[0m' "$<"

clean			:
	@make fclean -C libft/
	@make clean -C minilibx/
	@rm -f $(OBJ)
	@rm -f $(OBJ_D)
	@rm -rf $(OBJ_DIR) 2> /dev/null || true
	@printf '\033[4m'
	@echo "\033[31mRTV1:\033[0m"
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Object Files"

fclean			:	clean
	@rm -f $(NAME)
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "Clean Binary File"

re				:
	@make fclean
	@make opti

-include $(OBJ_D)

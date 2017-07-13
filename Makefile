# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-meur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/14 15:29:40 by tle-meur          #+#    #+#              #
#    Updated: 2016/01/26 11:51:36 by tle-meur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fdf

FLAGS	=	-Wall -Wextra -Werror

SRCS	=	main.c utilities.c parse.c functions.c image.c

OBJS	=	$(SRCS:.c=.o)

all		:	$(NAME)

$(NAME)	:
			@make -C libft/
			@echo "libft.a created"
			@gcc $(FLAGS) -c $(SRCS)
			@gcc $(FLAGS) -o $(NAME) $(OBJS) -lm -lmlx -L libft/ -lft
			@echo "fdf created"
clean	:
			@rm -f $(OBJS)
			@echo "objects deleted"

fclean	:	clean
			@rm -f $(NAME) libft/libft.a minilibx_macos/libmlx.a
			@echo "fdf libft.a and liblmlx.a deleted"

re		:	fclean $(NAME)

simple	:	re
			@rm -f $(OBJS)
			@echo "objects deleted"

.PHONY	:	all clean fclean re simple

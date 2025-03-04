# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 00:49:01 by igvisera          #+#    #+#              #
#    Updated: 2025/03/04 18:25:51 by igvisera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= 	philo

CC 				= 	gcc
CFLAGS 			= 	-g3 -Wall -Wextra -Werror -fsanitize=thread -O3 -lpthread
# CFLAGS 			= 	-g3 -Wall -Wextra -Werror -fsanitize=address -O3 -lpthread -fsanitize=thread
INCLUDES		= 	-I ./philo.h

PATH_BASE 		=	./src/
BASE	   		=	$(addprefix $(PATH_BASE), $(BASE_SRC))

BASE_SRC		=	main.c \
					time_utils.c \
					philo_utils.c \
					simulation.c \
					init_params.c \
					actions.c \
					checkers.c \
					getter_setter.c \
					handle_actions.c \

OBJS			=	${BASE:.c=.o} \

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES)

clean:
	@rm -rf $(OBJS)
	
fclean: clean	
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

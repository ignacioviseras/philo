# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igvisera <igvisera@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 00:49:01 by drestrep          #+#    #+#              #
#    Updated: 2024/12/12 15:58:52 by igvisera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= 	philo

CC 				= 	gcc
# CFLAGS 			= 	-g3 -Wall -Wextra -Werror -O3 -lpthread
CFLAGS 			= 	-g3 -Wall -Wextra -Werror -fsanitize=address -O3 -lpthread
INCLUDES		= 	-I ./philo.h

PATH_BASE 		=	./src/
PATH_UTILS 		=	./src/utils/
BASE	   		=	$(addprefix $(PATH_BASE), $(BASE_SRC))
UTILS	   		=	$(addprefix $(PATH_UTILS), $(UTILS_SRC))
# PATH_PARSING	=	./src/parsing/
# PARSING			=	$(addprefix $(PATH_PARSING), $(PARSING_SRC))

BASE_SRC		=	main.c

# PARSING_SRC		=	xxxxxxxxxxxxx.c \

# UTILS_SRC		=	utils01.c \
					# utils02.c \

OBJS			=	${BASE:.c=.o} \
					# ${UTILS:.c=.o} \

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES)

exe: all
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

clean:
	@rm -rf $(OBJS)
	
fclean: clean	
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

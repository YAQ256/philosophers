# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyacoub- <cyacoub-@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/21 06:22:51 by cyacoub-          #+#    #+#              #
#    Updated: 2023/06/01 14:54:54 by cyacoub-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## EXECUTABLE ##
NAME = philo
## COMPILATION ##
CC = gcc
CFLAGS = -Wall -Werror  -Wextra #-g3 -fsanitize=thread
#DEBUG = -g3 -fsanitize=address
## INCLUDE ##
#SRC_PATH = ./src/
#SRC_PATH_BONUS = ./bonus/
## VARIABLES ##
AR = @ar rcs
RM = @rm -f
LINK = -L $(LIBS_PATH)
## SOURCE FILE ##
SRCS =	philo.c utils.c init.c parser.c routine.c

SRC_BONUS =	
#SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = ${SRCS:.c=.o}

SRCS_BONUS = $(addprefix $(SRC_PATH_BONUS), $(SRC_BONUS))
OBJS_BONUS = ${SRCS_BONUS:.c=.o}
## COLORS ##
END     = \033[0m
RED     = \033[1;31m
GREEN   = \033[1;32m
YELLOW  = \033[1;33m
BLUE    = \033[1;34m
WHITE   = \033[1;37m
## RULES ##
all: $(NAME)

%.o :%.c 
	@echo "${BLUE} ◎ $(YELLOW)Compiling   ${RED}→   $(WHITE)$< $(END)" 
	@$(CC) $(CFLAGS) -c -o $@ $< 

$(NAME) : $(OBJS)
	clear
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)You Created $(NAME)$(END)"

#$(NAME2) : $(OBJS_BONUS)
#	clear
#	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o checker
#	@echo "$(GREEN)You Created Checker$(END)"

## CLEANNING ##

clean:
	@$(RM) $(OBJS)
	@echo "$(GREEN)$(NAME): $(RED)→ $(BLUE) Cleaning... $(END)"
	@echo "$(GREEN)$(NAME): $(RED)→ $(YELLOW) the files(*.o) were deleted $(END)"

## REMOVING .O FILES AND .A FILES ##

fclean: clean
	$(RM) $(NAME) $(OBJS) $(OBJS_BONUS)
	clear
	@echo "$(GREEN)$(NAME): $(RED) → $(BLUE)was deleted$(END)"

## REMOVING AND RUNNING ##

re: fclean all

.PHONY: all re clean fclean 
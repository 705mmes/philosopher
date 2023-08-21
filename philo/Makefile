# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sammeuss <sammeuss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/27 10:56:40 by sammeuss          #+#    #+#              #
#    Updated: 2023/08/21 14:13:26 by sammeuss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#     ███▄ ▄███▓ ▄▄▄       ██ ▄█▀▓█████   █████▒██▓ ██▓    ▓█████ 
#    ▓██▒▀█▀ ██▒▒████▄     ██▄█▒ ▓█   ▀ ▓██   ▒▓██▒▓██▒    ▓█   ▀ 
#    ▓██    ▓██░▒██  ▀█▄  ▓███▄░ ▒███   ▒████ ░▒██▒▒██░    ▒███   
#    ▒██    ▒██ ░██▄▄▄▄██ ▓██ █▄ ▒▓█  ▄ ░▓█▒  ░░██░▒██░    ▒▓█  ▄ 
#    ▒██▒   ░██▒ ▓█   ▓██▒▒██▒ █▄░▒████▒░▒█░   ░██░░██████▒░▒████▒
#    ░ ▒░   ░  ░ ▒▒   ▓▒█░▒ ▒▒ ▓▒░░ ▒░ ░ ▒ ░   ░▓  ░ ▒░▓  ░░░ ▒░ ░
#    ░  ░      ░  ▒   ▒▒ ░░ ░▒ ▒░ ░ ░  ░ ░      ▒ ░░ ░ ▒  ░ ░ ░  ░
#    ░      ░     ░   ▒   ░ ░░ ░    ░    ░ ░    ▒ ░  ░ ░      ░   
#           ░         ░  ░░  ░      ░  ░        ░      ░  ░   ░  ░
                                                            
NAME 			= philo
PRINT_NAME		= philo
PRINT_PREFIX	= \033[1m\033[38;5;240m[\033[0m\033[38;5;250m$(PRINT_NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m

SRC = 	main \
		utils_0 \
		utils_1	\
		data_init \
		parsing \
		runnin \
		whatdoido \
		
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread -g3

DIR_SRCS    = src/
DIR_OBJS    = objs/

SRCS        = $(addprefix $(DIR_SRCS), $(addsuffix .c, $(SRC)))
OBJS        = $(addprefix $(DIR_OBJS), $(addsuffix .o, $(SRC)))

all: $(NAME)

$(NAME): $(OBJS)
		@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling \033[0m\n"
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
		@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

$(DIR_OBJS)%.o :	$(DIR_SRCS)%.c $(OBJF)
				@mkdir -p $(DIR_OBJS)
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
		@echo "$(PRINT_PREFIX)\033[0;38;5;226m Cleaning \033[0m\n"
		@rm -f $(OBJS)
		@rm -r $(DIR_OBJS)
		@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
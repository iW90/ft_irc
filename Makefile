# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 19:37:25 by maalexan          #+#    #+#              #
#    Updated: 2025/01/11 10:47:38 by maalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		:=	ircserv

# Directories for source, object and libraries
SRC_DIR		:=	./src
OBJ_DIR		:=	./obj
HDR_DIR		:=	./inc

# Compilation flags
CC					:=	c++
CFLAGS			:=	-Wall -Wextra -Werror -std=c++98 -I $(HDR_DIR)
DEBUG_FLAGS := -DDEBUG=1

# Source files
SRC			:=	main.cpp

# Object files
OBJ			:=	$(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRC)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(if $(DEBUG), $(DEBUG_FLAGS)) -c $< -o $@

debug: DEBUG = 1
debug: all

val: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME}  || echo ""

clean:
	@[ -d ./obj ] && rm -rf ./obj || echo Object directory doesn\'t exist

fclean: clean
	@[ -f ./$(NAME) ] && rm $(NAME) || echo Program $(NAME) isn\'t compiled

re: fclean all

.PHONY: all clean fclean re val

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stopp <stopp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 16:09:25 by stopp             #+#    #+#              #
#    Updated: 2024/08/28 16:09:34 by stopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME := cub3d

# Define ANSI color codes
GREEN := \033[0;32m
RED := \033[0;31m
BLUE := \033[0;34m
NC := \033[0m

# Flags
CFLAGS  := -Wall -Werror -Wextra -I.

# Directories
SRC_DIR := src
OBJ_DIR := obj
# Source files
SRCS    := src/main.c
# Object files
OBJS    := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Header file
HEADER  := cub3d.h

MESSAGE := "\n$(GREEN)$(NAME) built successfully!$(NC)\n"

# Project build rule
all: $(OBJ_DIR) $(NAME) $(HEADER)
	@echo $(MESSAGE)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

# Rule to compile source files into object files in a separate obj folder
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(HEADER)
	@mkdir -p $(dir $@)
	@echo Compiling:  $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Create the objects directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule to clean object files
clean:
	@rm -rf $(OBJ_DIR)

# Rule to clean project and object files
fclean: clean
	@rm -rf $(NAME)

# Rule to clean and rebuild the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re Makefile

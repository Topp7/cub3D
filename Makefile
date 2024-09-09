# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stopp <stopp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 16:09:25 by stopp             #+#    #+#              #
#    Updated: 2024/09/09 16:36:17 by stopp            ###   ########.fr        #
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

LIBS := ./MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

# Directories
LIBFT := lib/libft
SRC_DIR := src
OBJ_DIR := obj
# Source files
SRCS    :=	gnl/get_next_line.c \
			gnl/get_next_line_utils.c \
			src/error_handler/check_directions.c \
			src/error_handler/check_nonsense.c \
			src/error_handler/check_order.c \
			src/error_handler/check_rgb.c \
			src/error_handler/error_checks.c \
			src/main.c \
			src/helper/helper1.c \
			src/helper/helper2.c \
			src/initialization/init_data.c \
			src/parser/parse_cub_content.c \
			src/parser/parse_cub_file.c \
			src/raycasting/raycasting.c \
			src/raycasting/test_functions.c \
			src/raycasting/ray_calcs.c \

# Object files
OBJS    := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Header file
HEADER  := include/cub3d.h lib/libft/libft.h

MESSAGE := "\n$(GREEN)$(NAME) built successfully!$(NC)\n"

# Project build rule
all: libmlx $(OBJ_DIR) $(NAME) $(HEADER)
	@echo $(MESSAGE)

# Build the MLX42 library (if needed)
libmlx:
	@if [ ! -d "MLX42" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git MLX42; \
	else \
		echo "Directory MLX42 already exists."; \
	fi
		@cd MLX42 && cmake -B build && cmake --build build -j4 \

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@echo "$(BLUE)libft built successfully!$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFT)/libft.a -o $@

# Rule to compile source files into object files in a separate obj folder
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(HEADER)
	@mkdir -p $(dir $@)
	@echo Compiling: $<
	@$(CC) $(CFLAGS) -c $< -o $@

# Create the objects directory
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Rule to clean object files
clean:
	@rm -rf $(OBJ_DIR)
	make -C $(LIBFT) clean

# Rule to clean project and object files
fclean:
	@rm -rf MLX42
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	make -C $(LIBFT) fclean

# Rule to clean and rebuild the project
re: fclean all

# Phony targets
.PHONY: all clean fclean re Makefile

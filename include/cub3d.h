/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:10:05 by stopp             #+#    #+#             */
/*   Updated: 2024/08/30 15:34:44 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// header file
#ifndef CUB3D_H
# define CUB3D_H

/* ------------------------------- DEFINITIONS ------------------------------ */

# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define RED "\033[0;31m"

/* -------------------------------- LIBRARIES ------------------------------- */

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <math.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

/* ------------------------------ WINDOW SIZE ------------------------------- */

# define WIDTH 256
# define HEIGHT 256

/* -------------------------------- STRUCTS --------------------------------- */

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_data
{
	char	*temp;
	char	*file;
	char	**cub_cont;
	char	**map;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*ceiling;
	char	*floor;
	char	player_direction;
	t_pos	player_pos;
	mlx_t	*mlx_ptr;
}	t_data;

/* ------------------------------- FUNCTIONS -------------------------------- */

/* ################################  GNL  ################################### */

// get_next_line.c
char	*read_better(int fd, char **str, char *newline, int n);
char	*get_next_line(int fd);

// get_next_line_utils.c
int		str_alloc_len(char *str);
void	str_after_n(char *str);
void	*ft_realloc(void *ptr, size_t new_size, int i);

/* ################################  HELPER  ################################ */

// helper1.c
void	print2d_array(char **array);

// helper2.c
int		count_relevant_chars(const char *str, const char *chrs_to_rmv);
void	remove_helper(const char *str, const char *chrs_to_rmv, char *new_s);
char	*remove_chars(const char *s, const char *chrs_to_rmv);

/* ################################  PARSER  ################################ */

// parse_cub_file.c
int		file_line_count(int fd);
int		parse_cub_file(char *cub_file, t_data *data);

// parse_cub_content.c
bool	find_first_map_line(char *str);
char	**extract_map(t_data *data);
void	extract_direction_str(t_data *data);
void	extract_paths(t_data *data);
void	extract_rgb(t_data *data);



//	main.c

#endif

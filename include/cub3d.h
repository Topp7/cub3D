/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:10:05 by stopp             #+#    #+#             */
/*   Updated: 2024/09/09 15:17:21 by chorst           ###   ########.fr       */
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

# include "../MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* ------------------------------ WINDOW SIZE ------------------------------- */

# define WIDTH 256
# define HEIGHT 256
# define PI 3.14159265359

/* -------------------------------- STRUCTS --------------------------------- */

typedef struct s_temp
{
	int				i;
	int				j;
	int				k;
	int				x;
	int				y;
	int				count;
	int				*flag;
	int				fd;
	char			*line;
	char			*str;
}					t_temp;

typedef struct s_pos
{
	float			px;
	float			py;
	float			pa;
	float			pdx;
	float			pdy;
}					t_pos;

typedef struct s_data
{
	char			*temp;
	char			*file;
	char			**cub_cont;
	char			**map;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*ceiling;
	unsigned int	c_rgb;
	char			*floor;
	unsigned int	f_rgb;
	char			p_direction;
	int				map_x;
	t_pos			*p_pos;
	mlx_t			*mlx_ptr;
	mlx_image_t		*img;
	mlx_image_t		*p_img;
}					t_data;

// #############################################################################
// --------------------------- External Files ----------------------------------
// #############################################################################

/* ---------------------------------  GNL  ---------------------------------- */

//	get_next_line.c
char			*read_better(int fd, char **str, char *newline, int n);
char			*get_next_line(int fd);

//	get_next_line_utils.c
int				str_alloc_len(char *str);
void			str_after_n(char *str);
void			*ft_realloc(void *ptr, size_t new_size, int i);

// #############################################################################
// --------------------------------- SRC ---------------------------------------
// #############################################################################

/* ---------------------------  ERROR HANDLER  ------------------------------ */

//	src/error_handling/check_directions.c
int				regognize_direction(char *str);
int				check_directions(t_data data);

//	src/error_handling/check_nonsense.c
int				check_nonsense(t_data data);
int				check_nonsense_1(t_data data);
int				check_nonsense_2(t_data data);

//	src/error_handling/check_rgb.c
int				check_rgb(t_data data);

//	src/error_handling/error_checks.c
int				error_checks(t_data *data);

/* -------------------------------  HELPERS  -------------------------------- */

// src/helper/helper1.c
void			print2d_array(char **array);
void			print_values(t_data *data);
unsigned int	extract_rgb(char *rgb);
void			init_temp_struct(t_temp *temp);

// src/helper/helper2.c
int				count_relevant_chars(char *str, char *chrs_to_rmv);
void			remove_helper(char *str, char *chrs_to_rmv, char *new_s);
char			*remove_chars(char *s, char *chrs_to_rmv);

/* ---------------------------  INITIALIZATION  ---------------------------- */

//	src/initialization/init_data.c
int				init_data(t_data **data);

/* -------------------------------  PARSER  -------------------------------- */

//	src/parser/parse_cub_content.c
bool			find_first_map_line(char *str);
char			**extract_map(char *argv, t_data *data);
void			extract_paths_and_rgbs(t_data *data);
void			extract_player_data(t_data *data);
int				extract_cub_data(char *str, t_data *data);

//	src/parser/parse_cub_file.c
int				file_line_count(int fd);
int				parse_cub_file(char *cub_file, t_data *data);

/* ------------------------------ RAYCASTING ------------------------------ */

//	src/raycasting/raycasting.c
void			raycast_exe(t_data *data);

//	src/raycasting/test_functions.c
void			add_testdata(t_data *data);

//	main.c
int				error_msg(char *str);

#endif

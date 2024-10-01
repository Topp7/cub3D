/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:10:05 by stopp             #+#    #+#             */
/*   Updated: 2024/10/01 11:27:19 by chorst           ###   ########.fr       */
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

# define WIDTH 768
# define HEIGHT 480
# define TILE 32
# define PI 3.14159265359

/* -------------------------------- STRUCTS --------------------------------- */

typedef struct s_ray
{
	float	rlen;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
}	t_ray;

typedef struct s_pos
{
	float	px;
	float	py;
	float	pa;
	float	pdx;
	float	pdy;
}	t_pos;

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
}					t_temp;

typedef struct s_data
{
	char			*temp;
	char			*file;
	char			**cub_cont;
	char			**map;
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*west_tex;
	mlx_texture_t	*east_tex;
	char			*ceiling;
	unsigned int	c_rgb;
	char			*floor;
	unsigned int	f_rgb;
	char			p_direction;
	int				map_x;
	int				left_right;
	int				up_down;
	int				rotate;
	t_pos			*p_pos;
	t_ray			*hr_pos;
	t_ray			*vr_pos;
	mlx_t			*mlx_ptr;
	mlx_image_t		*w_img;
	mlx_image_t		*b_img;
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

//	src/error_handling/check_map.c
int				check_map_structure_lines(t_data data);
int				check_map_surrounded_by_walls(t_data data);
int				check_map_characters(t_data data);
int				check_map_start_pos(t_data data);

// src/error_handling/check_nonsense_helper.c
int				check_nonsense_1helper(char *str);
int				check_nonsense_2helper(char *str);

//	src/error_handling/check_nonsense.c
int				check_nonsense(t_data data);
int				check_nonsense_1(t_data data);
int				check_nonsense_2(t_data data);
int				check_nonsense_3(t_data data);

// src/error_handling/check_paths_validation.c
int				check_paths(t_data *data);

//	src/error_handling/check_rgb.c
void			free_2d_array(char **arr);
int				check_rgb(t_data data);

//	src/error_handling/error_checks.c
int				error_checks(t_data *data);

/* -------------------------------  HELPERS  -------------------------------- */

// src/helper/helper1.c
void			print2d_array(char **array);
void			print_values(t_data *data);
unsigned int	extract_rgb(char *rgb);
void			init_temp_struct(t_temp *temp);
int				is_surrounded_by_walls(char **map, int i, int j);

// src/helper/helper2.c
int				count_relevant_chars(char *str, char *chrs_to_rmv);
void			remove_helper(char *str, char *chrs_to_rmv, char *new_s);
char			*remove_chars(char *s, char *chrs_to_rmv);

// src/helper/helper3.c
int				ft_strpbrk(const char *str, const char *charset);
void			skip_empty_lines(char **cub_cont, int *i, int *j);
void			skip_spaces(char **cub_cont, int *i, int *j);
int				is_empty_line(char *line);
void			init_textures(t_data *data);

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
void			draw_3d(t_data *data);

//	src/raycasting/movement.c
void			move_player(t_data *data);
void			turn_player(t_data *data);
float			adjust_angle(float angle);

//	src/raycasting/test_functions.c
void			add_testdata(t_data *data);
void			keyhandle(mlx_key_data_t keydata, void *param);
void			control_keyhook(void *param);

//	src/raycasting/ray_calcs.c
void			horizontal_rays(t_data *data);
int				wall_hit(float mx, float my, t_data *data);
void			vertical_rays(t_data *data);

//	src/raycasting/draw_minimap.c
int				draw_map(t_data *data);
void			draw_fnc(t_data *data);

//	src/raycasting/textures.c
unsigned int	get_tex_color(mlx_texture_t	*texture, int x, int y);
int				get_tex_y(t_data *data);
mlx_texture_t	*find_texture(t_data *data);

//	main.c
int				error_msg(char *str);

#endif

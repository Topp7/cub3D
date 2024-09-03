/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:10:05 by stopp             #+#    #+#             */
/*   Updated: 2024/09/03 14:22:21 by stopp            ###   ########.fr       */
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

typedef struct s_pos
{
	float	px; // von oben nach unten
	float	py;
	float	pa;
	float	pdx;
	float	pdy;
}	t_pos;

typedef struct s_data
{
	char		*temp;
	char		*file;
	char		**cub_cont;
	char		**map;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*ceiling;
	int			*c_rgb;
	char		*floor;
	char		p_direction;
	t_pos		*p_pos;
	mlx_t		*mlx_ptr;
	mlx_image_t	*img;
	mlx_image_t	*p_img;
}	t_data;

/* ------------------------------- FUNCTIONS -------------------------------- */

//	src/raycasting.c
void	raycast_exe(t_data *data);

// #############################################################################
// --------------------------- External Files ----------------------------------
// #############################################################################

/* ---------------------------------  GNL  ---------------------------------- */

//	get_next_line.c
char	*read_better(int fd, char **str, char *newline, int n);
char	*get_next_line(int fd);

//	get_next_line_utils.c
int		str_alloc_len(char *str);
void	str_after_n(char *str);
void	*ft_realloc(void *ptr, size_t new_size, int i);

// #############################################################################
// ---------------------------- Project Files ----------------------------------
// #############################################################################

/* ---------------------------  ERROR HANDLER  ---------------------------- */

//	project_files/error_handling/error_handler1.c
void	error_handler1(int error_code, t_data *data);

/* -------------------------------  HELPERS  -------------------------------- */

// project_files/helper/helper1.c
void	print2d_array(char **array);
void	print_values(t_data *data);
int		*extract_rgb(char *rgb);
int		int_into_hex(int *rgb);

// project_files/helper/helper2.c
int		count_relevant_chars(const char *str, const char *chrs_to_rmv);
void	remove_helper(const char *str, const char *chrs_to_rmv, char *new_s);
char	*remove_chars(const char *s, const char *chrs_to_rmv);

/* ---------------------------  INITIALIZATION  ---------------------------- */

//	project_files/initialization/init_data.c
void	init_data(t_data *data);

/* -------------------------------  PARSER  -------------------------------- */

//	project_files/parser/parse_cub_content.c
bool	find_first_map_line(char *str);
char	**extract_map(t_data *data);
void	extract_paths_and_rgbs(t_data *data);
void	extract_player_data(t_data *data);
int		extract_cub_data(t_data *data);

//	project_files/parser/parse_cub_file.c
int		file_line_count(int fd);
int		parse_cub_file(char *cub_file, t_data *data);

/* ------------------------------ RAYCASTING ------------------------------ */

//	project_files/raycasting/raycasting.c
void	raycast_exe(t_data *data);

//	project_files/raycasting/test_functions.c
void	add_testdata(t_data *data);

//	main.c

#endif

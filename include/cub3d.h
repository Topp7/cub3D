/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:10:05 by stopp             #+#    #+#             */
/*   Updated: 2024/08/29 17:35:49 by chorst           ###   ########.fr       */
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

typedef struct s_data
{
	char	**map;
	mlx_t	*mlx_ptr;
}	t_data;

typedef struct s_pos
{
	float	x; // von oben nach unten
	float	y;
}	t_pos;


typedef struct s_cub
{
	char			**cub_content;
	char			**map;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*ceiling;
	char			*floor;
	char			player_direction;
	t_pos			player_pos;
}					t_cub;

/* ------------------------------- FUNCTIONS -------------------------------- */

/* ################################  GNL  ################################### */

// get_next_line.c
char	*read_better(int fd, char **str, char *newline, int n);
char	*get_next_line(int fd);

// get_next_line_utils.c
int		str_alloc_len(char *str);
void	str_after_n(char *str);
void	*ft_realloc(void *ptr, size_t new_size, int i);

//	main.c

#endif

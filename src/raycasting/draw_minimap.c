/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:51:53 by stopp             #+#    #+#             */
/*   Updated: 2024/09/27 16:58:10 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_player(t_data *data)
{
	float	x;
	float	y;
	int		i;
	int		j;

	x = HEIGHT / 4 / 2;
	y = WIDTH / 4 / 2;
	i = -4;
	while (i < 4)
	{
		j = -4;
		while (j < 4)
		{
			mlx_put_pixel(data->w_img, y + j, x + i, 0xFF000000 | 255);
			j++;
		}
		i++;
	}
	while (i < 15)
	{
		mlx_put_pixel(data->w_img, y, x, 0x00000000 | 255);
		x += (data->p_pos->pdx);
		y += (data->p_pos->pdy);
		i++;
	}
}

void	draw_floor(t_data *data)
{
	float	x;
	float	y;
	int		i;
	int		j;

	x = data->p_pos->px - (HEIGHT / 4 / 2);
	y = data->p_pos->py - (WIDTH / 4 / 2);
	i = 0;
	while (i < HEIGHT / 4)
	{
		j = 0;
		while (j < WIDTH / 4)
		{
			if (wall_hit((x + i), (y + j), data) == 1)
				mlx_put_pixel(data->w_img, j, i, 0x00FFFF00 | 255);
			else
				mlx_put_pixel(data->w_img, j, i, 0x00808080 | 255);
			j++;
		}
		i++;
	}
}

void	draw_fnc(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->b_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->b_img)
		return ;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i < HEIGHT / 2)
				mlx_put_pixel(data->b_img, j, i, data->c_rgb);
			else
				mlx_put_pixel(data->b_img, j, i, data->f_rgb);
			j++;
		}
		i++;
	}
	mlx_image_to_window(data->mlx_ptr, data->b_img, 0, 0);
}

int	draw_map(t_data *data)
{
	draw_floor(data);
	draw_player(data);
	return (1);
}

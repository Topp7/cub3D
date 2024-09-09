/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:05:20 by stopp             #+#    #+#             */
/*   Updated: 2024/09/09 16:02:52 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	add_testdata(t_data *data)
{
	data->hr_pos = malloc(sizeof(t_ray));
	if (!data->hr_pos)
		return ;
	data->vr_pos = malloc(sizeof(t_ray));
	if (!data->vr_pos)
		return ;
	if (data->p_direction == 'S')
		data->p_pos->pa = 0.5 * PI;
	else if (data->p_direction == 'N')
		data->p_pos->pa = 1.5 * PI;
	else if (data->p_direction == 'W')
		data->p_pos->pa = PI;
	else
		data->p_pos->pa = 0;
	data->hr_pos->ra = data->p_pos->pa;
	data->vr_pos->ra = data->p_pos->pa;
	data->p_pos->pdx = (float)(sin(data->p_pos->pa));
	data->p_pos->pdy = (float)(cos(data->p_pos->pa));
	printf("pdx: %f\n", data->p_pos->pdx);
	printf("pdy: %f\n", data->p_pos->pdy);
}

void	draw_map_blocks(t_data *data, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 29 && ((x * 30) + i) < WIDTH)
	{
		j = 0;
		while (j < 29 && ((y * 30) + j) < HEIGHT)
		{
			mlx_put_pixel(data->img, ((y * 30) + j),
				((x * 30) + i), color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == '1')
				draw_map_blocks(data, x, y, data->c_rgb);
			else if (data->map[x][y] == '0' || data->map[x][y] == data->p_direction)
				draw_map_blocks(data, x, y, data->f_rgb);
			y++;
		}
		x++;
	}
	mlx_image_to_window(data->mlx_ptr, data->img, 0, 0);
}

void	draw_player(t_data *data)
{
	float	x;
	float	y;
	int		i;
	int		j;

	x = data->p_pos->px;
	y = data->p_pos->py;
	data->p_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img)
		return ;
	i = -5;
	while (i < 5)
	{
		j = -5;
		while (j < 5)
		{
			mlx_put_pixel(data->p_img, y + j, x + i, 0x00FF0000 | 255);
			j++;
		}
		i++;
	}
	draw_ray(data);
	printf("pa: %f\n", data->p_pos->pa);
	mlx_image_to_window(data->mlx_ptr, data->p_img,
		0, 0);
}

void	draw_ray(t_data *data)
{
	float	x;
	float	y;
	int		i;

	x = (data->p_pos->px);
	y = (data->p_pos->py);
	i = 0;
	while (i < 10)
	{
		mlx_put_pixel(data->p_img, y, x, 0x000FF000 | 255);
		x += (data->p_pos->pdx);
		y += (data->p_pos->pdy);
		i++;
	}
	update_rays(data);
}

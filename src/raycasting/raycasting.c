/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:41 by stopp             #+#    #+#             */
/*   Updated: 2024/08/30 17:49:43 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	control_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->mlx_ptr);
	}
	if (keydata.key == MLX_KEY_UP)
		data->pl_img->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_DOWN)
		data->pl_img->instances[0].y += 5;
	if (keydata.key == MLX_KEY_LEFT)
		data->pl_img->instances[0].x -= 5;
	if (keydata.key == MLX_KEY_RIGHT)
		data->pl_img->instances[0].x += 5;
}

void	draw_map_blocks(t_data *data, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 99)
	{
		j = 0;
		while (j < 99)
		{
			mlx_put_pixel(data->img, ((y * 100) + j),
				((x * 100) + i), color);
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
				draw_map_blocks(data, x, y, 0xFF000000 | 100);
			else if (data->map[x][y] == '0' || data->map[x][y] == 'S')
				draw_map_blocks(data, x, y, 0x0000FF00 | 100);
			y++;
		}
		x++;
	}
	mlx_image_to_window(data->mlx_ptr, data->img, 0, 0);
}

void	draw_player(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < 25)
	{
		y = 0;
		while (y < 25)
		{
			mlx_put_pixel(data->pl_img, y, x, 0x00FF0000 | 255);
			y++;
		}
		x++;
	}
	mlx_image_to_window(data->mlx_ptr, data->pl_img,
		(data->player_pos->py * 100), (data->player_pos->px * 100));
}

void	raycast_exe(t_data *data)
{
	add_testdata(data);
	data->mlx_ptr = mlx_init(2000, 1000, "Test", true);
	if (!data->mlx_ptr)
		return ;
	data->img = mlx_new_image(data->mlx_ptr, 1000, 1000);
	if (!data->img)
		return ;
	data->pl_img = mlx_new_image(data->mlx_ptr, 1000, 1000);
	if (!data->img)
		return ;
	draw_map(data);
	draw_player(data);
	mlx_key_hook(data->mlx_ptr, control_keyhook, data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}

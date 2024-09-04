/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:41 by stopp             #+#    #+#             */
/*   Updated: 2024/09/03 18:06:27 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_player(t_data *data);

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
	{
		mlx_delete_image(data->mlx_ptr, data->p_img);
		data->p_pos->px += data->p_pos->pdx;
		data->p_pos->py += data->p_pos->pdy;
		draw_player(data);
	}
	if (keydata.key == MLX_KEY_DOWN)
	{
		mlx_delete_image(data->mlx_ptr, data->p_img);
		data->p_pos->px -= data->p_pos->pdx;
		data->p_pos->py -= data->p_pos->pdy;
		draw_player(data);
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		mlx_delete_image(data->mlx_ptr, data->p_img);
		data->p_pos->pa -= 0.1;
		if (data->p_pos->pa < 0)
			data->p_pos->pa += (2 * PI);
		data->p_pos->pdx = (float)(sin(data->p_pos->pa) / 10);
		data->p_pos->pdy = (float)(cos(data->p_pos->pa) / 10);
		draw_player(data);
		printf("pa: %f\n", data->p_pos->pa);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		mlx_delete_image(data->mlx_ptr, data->p_img);
		data->p_pos->pa += 0.1;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa = (data->p_pos->pa - (2 * PI));
		data->p_pos->pdx = (float)(sin(data->p_pos->pa) / 10);
		data->p_pos->pdy = (float)(cos(data->p_pos->pa) / 10);
		draw_player(data);
		printf("pa: %f\n", data->p_pos->pa);
	}
}

void	draw_map_blocks(t_data *data, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 29 && ((x * 30) + i) < 2000)
	{
		j = 0;
		while (j < 29 && ((y * 30) + j) < 2000)
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

void	draw_ray(t_data *data)
{
	float	x;
	float	y;
	int		i;

	x = (data->p_pos->px * 30) + 5;
	y = (data->p_pos->py * 30) + 5;
	i = 0;
	while (i < 30)
	{
		mlx_put_pixel(data->p_img, y, x, 0x000FF000 | 255);
		x += (data->p_pos->pdx * 10);
		y += (data->p_pos->pdy * 10);
		i++;
	}
}

void	draw_player(t_data *data)
{
	float	x;
	float	y;
	int		i;
	int		j;

	x = data->p_pos->px * 30;
	y = data->p_pos->py * 30;
	data->p_img = mlx_new_image(data->mlx_ptr, 2000, 1000);
	if (!data->img)
		return ;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_put_pixel(data->p_img, y + j, x + i, 0x00FF0000 | 255);
			j++;
		}
		i++;
	}
	draw_ray(data);
	mlx_image_to_window(data->mlx_ptr, data->p_img,
		0, 0);
}

void	raycast_exe(t_data *data)
{
	add_testdata(data);
	data->mlx_ptr = mlx_init(2000, 1000, "cub3d", true);
	if (!data->mlx_ptr)
		return ;
	data->img = mlx_new_image(data->mlx_ptr, 2000, 1000);
	if (!data->img)
		return ;
	draw_map(data);
	draw_player(data);
	mlx_key_hook(data->mlx_ptr, control_keyhook, data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}

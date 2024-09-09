/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:41 by stopp             #+#    #+#             */
/*   Updated: 2024/09/09 16:29:49 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	wall_collision(t_data *data, char c)
{
	int	mx;
	int	my;

	if (c == 'f')
	{
		mx = (int)(data->p_pos->px + data->p_pos->pdx * 5) / 30;
		my = (int)(data->p_pos->py + data->p_pos->pdy * 5) / 30;
	}
	else
	{
		mx = (int)(data->p_pos->px - data->p_pos->pdx) / 30;
		my = (int)(data->p_pos->py - data->p_pos->pdy) / 30;
	}
	if (data->map[mx][my] == '1')
		return (1);
	else
		return (0);
}

void	control_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(data->mlx_ptr);
	}
	if (keydata.key == MLX_KEY_UP && wall_collision(data, 'f') == 0)
	{
		mlx_delete_image(data->mlx_ptr, data->p_img);
		data->p_pos->px += data->p_pos->pdx * 5;
		data->p_pos->py += data->p_pos->pdy * 5;
		draw_player(data);
	}
	if (keydata.key == MLX_KEY_DOWN && wall_collision(data, 'b') == 0)
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
		data->p_pos->pdx = (float)(sin(data->p_pos->pa));
		data->p_pos->pdy = (float)(cos(data->p_pos->pa));
		draw_player(data);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		mlx_delete_image(data->mlx_ptr, data->p_img);
		data->p_pos->pa += 0.1;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa -= (2 * PI);
		data->p_pos->pdx = (float)(sin(data->p_pos->pa));
		data->p_pos->pdy = (float)(cos(data->p_pos->pa));
		draw_player(data);
	}
}

void	update_rays(t_data *data)
{
	horizontal_rays(data);
	vertical_rays(data);
	if (data->vr_pos->rlen < data->hr_pos->rlen)
		mlx_put_pixel(data->p_img, data->vr_pos->ry,
			data->vr_pos->rx, 0xFFFFFF00 | 255);
	else
		mlx_put_pixel(data->p_img, data->hr_pos->ry,
			data->hr_pos->rx, 0xFFFFFF00 | 255);
}

void	raycast_exe(t_data *data)
{
	add_testdata(data);
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data->mlx_ptr)
		return ;
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img)
		return ;
	draw_map(data);
	draw_player(data);
	mlx_key_hook(data->mlx_ptr, control_keyhook, data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}

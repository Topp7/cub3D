/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:44:47 by stopp             #+#    #+#             */
/*   Updated: 2024/09/10 16:26:31 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	wall_col_lr(int *mx, int *my, t_data *data, char c)
{
	if (c == 'r')
	{
		data->p_pos->pa -= 0.5 * PI;
		if (data->p_pos->pa < 0)
			data->p_pos->pa += (2 * PI);
		*mx = (int)(data->p_pos->px + (sin(data->p_pos->pa) * 2)) / 30;
		*my = (int)(data->p_pos->py + (cos(data->p_pos->pa) * 2)) / 30;
		data->p_pos->pa += 0.5 * PI;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa -= (2 * PI);
	}
	else if (c == 'l')
	{
		data->p_pos->pa += 0.5 * PI;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa -= (2 * PI);
		*mx = (int)(data->p_pos->px + (sin(data->p_pos->pa) * 2)) / 30;
		*my = (int)(data->p_pos->py + (cos(data->p_pos->pa) * 2)) / 30;
		data->p_pos->pa -= 0.5 * PI;
		if (data->p_pos->pa < 0)
			data->p_pos->pa += (2 * PI);
	}
}

int	wall_collision(t_data *data, char c)
{
	int	mx;
	int	my;

	if (c == 'f')
	{
		mx = (int)(data->p_pos->px + data->p_pos->pdx * 5) / 30;
		my = (int)(data->p_pos->py + data->p_pos->pdy * 5) / 30;
	}
	else if (c == 'b')
	{
		mx = (int)(data->p_pos->px - data->p_pos->pdx) / 30;
		my = (int)(data->p_pos->py - data->p_pos->pdy) / 30;
	}
	else if (c == 'l' || c == 'r')
		wall_col_lr(&mx, &my, data, c);
	else
		return (1);
	if (data->map[mx][my] == '1')
		return (1);
	else
		return (0);
}

void	turn_player(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_LEFT)
	{
		data->p_pos->pa -= 0.1;
		if (data->p_pos->pa < 0)
			data->p_pos->pa += (2 * PI);
		data->p_pos->pdx = (float)(sin(data->p_pos->pa));
		data->p_pos->pdy = (float)(cos(data->p_pos->pa));
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		data->p_pos->pa += 0.1;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa -= (2 * PI);
		data->p_pos->pdx = (float)(sin(data->p_pos->pa));
		data->p_pos->pdy = (float)(cos(data->p_pos->pa));
	}
}

void	move_left_right(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_A && wall_collision(data, 'r') == 0)
	{
		data->p_pos->pa -= 0.5 * PI;
		if (data->p_pos->pa < 0)
			data->p_pos->pa += (2 * PI);
		data->p_pos->px += (float)(sin(data->p_pos->pa) * 2);
		data->p_pos->py += (float)(cos(data->p_pos->pa) * 2);
		data->p_pos->pa += 0.5 * PI;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa -= (2 * PI);
	}
	if (keydata.key == MLX_KEY_D && wall_collision(data, 'l') == 0)
	{
		data->p_pos->pa += 0.5 * PI;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa -= (2 * PI);
		data->p_pos->px += (float)(sin(data->p_pos->pa) * 2);
		data->p_pos->py += (float)(cos(data->p_pos->pa) * 2);
		data->p_pos->pa -= 0.5 * PI;
		if (data->p_pos->pa < 0)
			data->p_pos->pa += (2 * PI);
	}
}

void	move_player(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_W && wall_collision(data, 'f') == 0)
	{
		data->p_pos->px += data->p_pos->pdx * 5;
		data->p_pos->py += data->p_pos->pdy * 5;
	}
	if (keydata.key == MLX_KEY_S && wall_collision(data, 'b') == 0)
	{
		data->p_pos->px -= data->p_pos->pdx;
		data->p_pos->py -= data->p_pos->pdy;
	}
	move_left_right(keydata, data);
}

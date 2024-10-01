/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:44:47 by stopp             #+#    #+#             */
/*   Updated: 2024/09/28 19:51:16 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	wall_col_lr(int *mx, int *my, t_data *data, char c)
{
	if (c == 'r')
	{
		data->p_pos->pa -= 0.5 * PI;
		data->p_pos->pa = adjust_angle(data->p_pos->pa);
		*mx = (data->p_pos->px + (sin(data->p_pos->pa))) / TILE;
		*my = (data->p_pos->py + (cos(data->p_pos->pa))) / TILE;
		data->p_pos->pa += 0.5 * PI;
		data->p_pos->pa = adjust_angle(data->p_pos->pa);
	}
	else if (c == 'l')
	{
		data->p_pos->pa += 0.5 * PI;
		data->p_pos->pa = adjust_angle(data->p_pos->pa);
		*mx = (data->p_pos->px + (sin(data->p_pos->pa))) / TILE;
		*my = (data->p_pos->py + (cos(data->p_pos->pa))) / TILE;
		data->p_pos->pa -= 0.5 * PI;
		data->p_pos->pa = adjust_angle(data->p_pos->pa);
	}
}

int	wall_collision(t_data *data, char c, float add)
{
	int	mx;
	int	my;

	if (c == 'x')
	{
		mx = (data->p_pos->px + (add * 5)) / TILE;
		my = (data->p_pos->py) / TILE;
	}
	else if (c == 'y')
	{
		mx = (data->p_pos->px) / TILE;
		my = (data->p_pos->py + (add * 5)) / TILE;
	}
	else
		return (1);
	if (data->map[mx][my] == '1')
		return (1);
	else
		return (0);
}

void	turn_player( t_data *data)
{
	if (data->rotate == -1)
	{
		data->p_pos->pa -= 0.04;
		data->p_pos->pa = adjust_angle(data->p_pos->pa);
		data->p_pos->pdx = (sin(data->p_pos->pa));
		data->p_pos->pdy = (cos(data->p_pos->pa));
	}
	if (data->rotate == 1)
	{
		data->p_pos->pa += 0.04;
		data->p_pos->pa = adjust_angle(data->p_pos->pa);
		data->p_pos->pdx = (sin(data->p_pos->pa));
		data->p_pos->pdy = (cos(data->p_pos->pa));
	}
}

void	move_left_right(t_data *data)
{
	if (data->left_right == -1)
	{
		data->p_pos->pa -= 0.5 * PI;
		data->p_pos->pa = adjust_angle(data->p_pos->pa);
		if (wall_collision(data, 'x', sin(data->p_pos->pa)) == 0)
			data->p_pos->px += (sin(data->p_pos->pa));
		if (wall_collision(data, 'y', cos(data->p_pos->pa)) == 0)
			data->p_pos->py += (cos(data->p_pos->pa));
		data->p_pos->pa += 0.5 * PI;
		data->p_pos->pa = adjust_angle(data->p_pos->pa);
	}
	if (data->left_right == 1)
	{
		data->p_pos->pa += 0.5 * PI;
		data->p_pos->pa = adjust_angle(data->p_pos->pa);
		if (wall_collision(data, 'x', sin(data->p_pos->pa)) == 0)
			data->p_pos->px += (sin(data->p_pos->pa));
		if (wall_collision(data, 'y', cos(data->p_pos->pa)) == 0)
			data->p_pos->py += (cos(data->p_pos->pa));
		data->p_pos->pa -= 0.5 * PI;
		data->p_pos->pa = adjust_angle(data->p_pos->pa);
	}
}

void	move_player(t_data *data)
{
	if (data->up_down == 1)
	{
		if (wall_collision(data, 'x', data->p_pos->pdx) == 0)
			data->p_pos->px += data->p_pos->pdx;
		if (wall_collision(data, 'y', data->p_pos->pdy) == 0)
			data->p_pos->py += data->p_pos->pdy;
	}
	else if (data->up_down == -1)
	{
		if (wall_collision(data, 'x', (data->p_pos->pdx * -1)) == 0)
			data->p_pos->px -= data->p_pos->pdx;
		if (wall_collision(data, 'y', (data->p_pos->pdy * -1)) == 0)
			data->p_pos->py -= data->p_pos->pdy;
	}
	move_left_right(data);
}

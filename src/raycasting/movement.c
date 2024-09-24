/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:44:47 by stopp             #+#    #+#             */
/*   Updated: 2024/09/24 19:19:26 by stopp            ###   ########.fr       */
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
		*mx = (int)(data->p_pos->px + (sin(data->p_pos->pa))) / TILE;
		*my = (int)(data->p_pos->py + (cos(data->p_pos->pa))) / TILE;
		data->p_pos->pa += 0.5 * PI;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa -= (2 * PI);
	}
	else if (c == 'l')
	{
		data->p_pos->pa += 0.5 * PI;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa -= (2 * PI);
		*mx = (int)(data->p_pos->px + (sin(data->p_pos->pa))) / TILE;
		*my = (int)(data->p_pos->py + (cos(data->p_pos->pa))) / TILE;
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
		mx = (int)(data->p_pos->px + data->p_pos->pdx) / TILE;
		my = (int)(data->p_pos->py + data->p_pos->pdy) / TILE;
	}
	else if (c == 'b')
	{
		mx = (int)(data->p_pos->px - data->p_pos->pdx) / TILE;
		my = (int)(data->p_pos->py - data->p_pos->pdy) / TILE;
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

void	turn_player( t_data *data)
{
	if (data->rotate == -1)
	{
		data->p_pos->pa -= 0.1;
		if (data->p_pos->pa < 0)
			data->p_pos->pa += (2 * PI);
		data->p_pos->pdx = (float)(sin(data->p_pos->pa));
		data->p_pos->pdy = (float)(cos(data->p_pos->pa));
	}
	if (data->rotate == 1)
	{
		data->p_pos->pa += 0.1;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa -= (2 * PI);
		data->p_pos->pdx = (sin(data->p_pos->pa));
		data->p_pos->pdy = (cos(data->p_pos->pa));
	}
}

void	move_left_right(t_data *data)
{
	if (data->left_right == -1 && wall_collision(data, 'r') == 0)
	{
		data->p_pos->pa -= 0.5 * PI;
		if (data->p_pos->pa < 0)
			data->p_pos->pa += (2 * PI);
		data->p_pos->px += (float)(sin(data->p_pos->pa));
		data->p_pos->py += (float)(cos(data->p_pos->pa));
		data->p_pos->pa += 0.5 * PI;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa -= (2 * PI);
	}
	if (data->left_right == 1 && wall_collision(data, 'l') == 0)
	{
		data->p_pos->pa += 0.5 * PI;
		if (data->p_pos->pa > (2 * PI))
			data->p_pos->pa -= (2 * PI);
		data->p_pos->px += (float)(sin(data->p_pos->pa));
		data->p_pos->py += (float)(cos(data->p_pos->pa));
		data->p_pos->pa -= 0.5 * PI;
		if (data->p_pos->pa < 0)
			data->p_pos->pa += (2 * PI);
	}
}

void	move_player(t_data *data)
{
	if (data->up_down == 1 && wall_collision(data, 'f') == 0)
	{
		data->p_pos->px += data->p_pos->pdx ;
		data->p_pos->py += data->p_pos->pdy ;
	}
	else if (data->up_down == -1 && wall_collision(data, 'b') == 0)
	{
		data->p_pos->px -= data->p_pos->pdx;
		data->p_pos->py -= data->p_pos->pdy;
	}
	move_left_right(data);
}

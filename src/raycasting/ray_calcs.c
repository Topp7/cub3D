/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:30:37 by stopp             #+#    #+#             */
/*   Updated: 2024/09/28 20:11:56 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	wall_hit(float mx, float my, t_data *data)
{
	int	xmap;
	int	ymap;

	xmap = floor(mx / TILE);
	ymap = floor(my / TILE);
	if (xmap < 0 || ymap < 0)
		return (0);
	if (xmap > data->map_x || ymap > (int)ft_strlen(data->map[xmap]))
		return (0);
	if (data->map[xmap][ymap] == '1')
		return (0);
	return (1);
}

void	wall_distance_hr(t_data *data)
{
	float	xlen;
	float	ylen;

	if (data->hr_pos->ra > PI)
		data->hr_pos->rx -= 1;
	while (wall_hit(data->hr_pos->rx, data->hr_pos->ry, data) == 1)
	{
		data->hr_pos->rx += data->hr_pos->xo;
		data->hr_pos->ry += data->hr_pos->yo;
	}
	if (data->hr_pos->ra > PI)
		data->hr_pos->rx += 1;
	xlen = (data->hr_pos->rx - data->p_pos->px);
	ylen = (data->hr_pos->ry - data->p_pos->py);
	data->hr_pos->rlen = sqrt((xlen * xlen) + (ylen * ylen));
}

void	wall_distance_vr(t_data *data)
{
	float	xlen;
	float	ylen;

	if (data->vr_pos->ra < (PI * 1.5) && data->vr_pos->ra > (PI * 0.5))
		data->vr_pos->ry -= 1;
	while (wall_hit(data->vr_pos->rx, data->vr_pos->ry, data) == 1)
	{
		data->vr_pos->rx += data->vr_pos->xo;
		data->vr_pos->ry += data->vr_pos->yo;
	}
	if (data->vr_pos->ra < (PI * 1.5) && data->vr_pos->ra > (PI * 0.5))
		data->vr_pos->ry += 1;
	xlen = (data->vr_pos->rx - data->p_pos->px);
	ylen = (data->vr_pos->ry - data->p_pos->py);
	data->vr_pos->rlen = sqrt((xlen * xlen) + (ylen * ylen));
}

void	vertical_rays(t_data *data)
{
	float	ntan;

	ntan = (-tan(data->vr_pos->ra));
	if (data->vr_pos->ra == 1.5 * PI || data->vr_pos->ra == 0.5 * PI)
		return ;
	if (data->vr_pos->ra > (PI * 1.5) || data->vr_pos->ra < (PI * 0.5))
	{
		data->vr_pos->ry = floor(data->p_pos->py / TILE) * TILE + TILE;
		data->vr_pos->rx = ((data->p_pos->py - data->vr_pos->ry) * ntan)
			+ data->p_pos->px;
		data->vr_pos->yo = TILE;
		data->vr_pos->xo = (-data->vr_pos->yo * ntan);
	}
	else if (data->vr_pos->ra < (PI * 1.5) && data->vr_pos->ra > (PI * 0.5))
	{
		data->vr_pos->ry = floor(data->p_pos->py / TILE) * TILE ;
		data->vr_pos->rx = ((data->p_pos->py - data->vr_pos->ry) * ntan)
			+ data->p_pos->px;
		data->vr_pos->yo = -TILE;
		data->vr_pos->xo = (-data->vr_pos->yo * ntan);
	}
	wall_distance_vr(data);
}

void	horizontal_rays(t_data *data)
{
	float	atan;

	atan = -1 / tan(data->hr_pos->ra);
	if (data->hr_pos->ra > PI)
	{
		data->hr_pos->rx = floor(data->p_pos->px / TILE) * TILE ;
		data->hr_pos->ry = ((data->p_pos->px - data->hr_pos->rx) * atan)
			+ data->p_pos->py ;
		data->hr_pos->xo = -TILE;
		data->hr_pos->yo = (-data->hr_pos->xo * atan);
	}
	else if (data->hr_pos->ra < PI)
	{
		data->hr_pos->rx = floor(data->p_pos->px / TILE) * TILE + TILE ;
		data->hr_pos->ry = ((data->p_pos->px - data->hr_pos->rx) * atan)
			+ data->p_pos->py ;
		data->hr_pos->xo = TILE;
		data->hr_pos->yo = (-data->hr_pos->xo * atan);
	}
	else if (data->hr_pos->ra == 0 || data->hr_pos->ra == PI)
		return ;
	wall_distance_hr(data);
}

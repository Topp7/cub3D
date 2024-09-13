/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:30:37 by stopp             #+#    #+#             */
/*   Updated: 2024/09/12 17:27:37 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	wall_distance_hr(t_data *data)
{
	int	mx;
	int	my;
	int	xlen;
	int	ylen;

	mx = data->hr_pos->rx / 30;
	my = data->hr_pos->ry / 30;
	if (my < 0 || my > (30 * 6))
	{
		data->vr_pos->rlen = 20000000;
		return ;
	}
	if (data->hr_pos->ra > PI)
		mx -= 1;
	while (mx > 0 && my > 0 && mx < 5 && my < 5 && data->map[mx][my] != '1')
	{
		data->hr_pos->rx += (int)data->hr_pos->xo;
		data->hr_pos->ry += (int)data->hr_pos->yo;
		mx = data->hr_pos->rx / 30;
		my = data->hr_pos->ry / 30;
		if (data->hr_pos->ra > PI)
			mx -= 1;
	}
	xlen = (data->hr_pos->rx - (int)data->p_pos->px);
	ylen = (data->hr_pos->ry - (int)data->p_pos->py);
	data->hr_pos->rlen = sqrt((xlen * xlen) + (ylen * ylen));
}

void	wall_distance_vr(t_data *data)
{
	int	mx;
	int	my;
	int	xlen;
	int	ylen;

	if (data->vr_pos->rx < 0 || data->vr_pos->rx > (30 * 6))
	{
		data->vr_pos->rlen = 20000000;
		return ;
	}
	mx = data->vr_pos->rx / 30;
	my = data->vr_pos->ry / 30;
	if (data->vr_pos->ra < (PI * 1.5) && data->vr_pos->ra > (PI * 0.5))
		my -= 1;
	while (mx > 0 && my > 0 && mx < 5 && my < 5 && data->map[mx][my] != '1')
	{
		data->vr_pos->rx += (int)data->vr_pos->xo;
		data->vr_pos->ry += (int)data->vr_pos->yo;
		mx = data->vr_pos->rx / 30;
		my = data->vr_pos->ry / 30;
		if (data->vr_pos->ra < (PI * 1.5) && data->vr_pos->ra > (PI * 0.5))
			my -= 1;
	}
	xlen = (data->vr_pos->rx - (int)data->p_pos->px);
	ylen = (data->vr_pos->ry - (int)data->p_pos->py);
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
		data->vr_pos->ry = ((int)data->p_pos->py / 30) * 30 + 30;
		data->vr_pos->rx = ((data->p_pos->py - data->vr_pos->ry) * ntan)
			+ data->p_pos->px;
		data->vr_pos->yo = 30;
		data->vr_pos->xo = (-data->vr_pos->yo * ntan);
	}
	else if (data->vr_pos->ra < (PI * 1.5) && data->vr_pos->ra > (PI * 0.5))
	{
		data->vr_pos->ry = ((int)data->p_pos->py / 30) * 30 ;
		data->vr_pos->rx = ((data->p_pos->py - data->vr_pos->ry) * ntan)
			+ data->p_pos->px;
		data->vr_pos->yo = -30;
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
		data->hr_pos->rx = ((int)data->p_pos->px / 30) * 30;
		data->hr_pos->ry = ((data->p_pos->px - data->hr_pos->rx) * atan)
			+ data->p_pos->py;
		data->hr_pos->xo = -30;
		data->hr_pos->yo = (-data->hr_pos->xo * atan);
	}
	else if (data->hr_pos->ra < PI)
	{
		data->hr_pos->rx = ((int)data->p_pos->px / 30) * 30 + 30;
		data->hr_pos->ry = ((data->p_pos->px - data->hr_pos->rx) * atan)
			+ data->p_pos->py;
		data->hr_pos->xo = +30;
		data->hr_pos->yo = (-data->hr_pos->xo * atan);
	}
	else if (data->hr_pos->ra == 0 || data->hr_pos->ra == PI)
		return ;
	wall_distance_hr(data);
}

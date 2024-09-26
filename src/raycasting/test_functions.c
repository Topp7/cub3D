/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:05:20 by stopp             #+#    #+#             */
/*   Updated: 2024/09/24 19:17:54 by stopp            ###   ########.fr       */
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
	if (!data->p_pos)
		printf("test\n");
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
	data->left_right = 0;
	data->up_down = 0;
	data->rotate = 0;
}

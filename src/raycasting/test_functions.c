/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:05:20 by stopp             #+#    #+#             */
/*   Updated: 2024/09/02 17:06:39 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	add_testdata(t_data *data)
{
	data->p_direction = 'W';
	data->p_pos = malloc(sizeof(t_pos));
	if (!data->p_pos)
		return ;
	data->p_pos->px = 3.5;
	data->p_pos->py = 1.5;
	if (data->p_direction == 'S')
		data->p_pos->pa = 0.5 * PI;
	else if (data->p_direction == 'N')
		data->p_pos->pa = 1.5 * PI;
	else if (data->p_direction == 'W')
		data->p_pos->pa = 0;
	else
		data->p_pos->pa = PI;
	data->p_pos->pdx = (float)(sin(data->p_pos->pa) / 10);
	data->p_pos->pdy = (float)(cos(data->p_pos->pa) / 10);
	printf("pdx: %f\n", data->p_pos->pdx);
	printf("pdy: %f\n", data->p_pos->pdy);
}

// void	calculate_ray(t_data *data)
// {

// }

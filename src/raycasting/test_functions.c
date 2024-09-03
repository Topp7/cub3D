/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:05:20 by stopp             #+#    #+#             */
/*   Updated: 2024/08/30 16:02:12 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	add_testdata(t_data *data)
{
	data->player_direction = 'S';
	data->player_pos = malloc(sizeof(t_pos));
	if (!data->player_pos)
		return ;
	data->player_pos->px = 3;
	data->player_pos->py = 1;
}

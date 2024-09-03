/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:55:01 by chorst            #+#    #+#             */
/*   Updated: 2024/09/03 14:00:41 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	error_check(t_data *data)
{
	if (check_for_directions(data) != 6)
		return (error_msg("Missing directions or doubled directions"));
	if (check_for_nonsense(data))
		return (error_msg("Nonsense in the map"));
	return (0);
}

int	check_for_nonsense(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	while (data->cub_cont[x])
	{
		while (data->cub_cont[x][0] == '\n')
			data->cub_cont[x]++;
		y = 0;
		while (data->cub_cont[x][y] == ' ')
		{
			if (data->cub_cont[x][y + 1] == '\n')
				return (1);
			y++;
		}
		x++;
	}
	return (0);
}

int	check_for_directions(t_data *data)
{
	int		x;
	int		y;
	int		direction_count;

	x = 0;
	direction_count = 0;
	while (data->cub_cont[x])
	{
		y = 0;
		while (data->cub_cont[x][y])
		{
			if (ft_strncmp(data->cub_cont[x] + y, "NO", 2) == 0
				|| ft_strncmp(data->cub_cont[x] + y, "SO", 2) == 0
				|| ft_strncmp(data->cub_cont[x] + y, "WE", 2) == 0
				|| ft_strncmp(data->cub_cont[x] + y, "EA", 2) == 0
				|| ft_strncmp(data->cub_cont[x] + y, "C", 1) == 0
				|| ft_strncmp(data->cub_cont[x] + y, "F", 1) == 0)
				direction_count++;
			y++;
		}
		x++;
	}
	return (direction_count);
}

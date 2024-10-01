/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:04:16 by chorst            #+#    #+#             */
/*   Updated: 2024/10/01 10:25:30 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function to check if there are empty lines in the map
int	check_map_structure_lines(t_data data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (find_first_map_line(data.cub_cont[i]) == false && data.cub_cont[i])
		i++;
	while (data.cub_cont[i])
	{
		if (ft_strpbrk(data.cub_cont[i], "01NESW") == 1
			&& data.cub_cont[i + 1]
			&& ft_strpbrk(data.cub_cont[i + 1], "01NESW") == 0)
			count++;
		i++;
	}
	if (count > 0)
		return (1);
	return (0);
}

// Function to check if the map is surrounded by walls
int	check_map_surrounded_by_walls(t_data data)
{
	int	i;
	int	j;

	i = 0;
	while (find_first_map_line(data.cub_cont[i]) == false && data.cub_cont[i])
		i++;
	while (data.cub_cont[i])
	{
		j = 0;
		while (data.cub_cont[i][j])
		{
			if (data.cub_cont[i][j] == '0' || data.cub_cont[i][j] == 'N'
				|| data.cub_cont[i][j] == 'E' || data.cub_cont[i][j] == 'S'
				|| data.cub_cont[i][j] == 'W')
			{
				if (is_surrounded_by_walls(data.cub_cont, i, j) != 0)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_characters(t_data data)
{
	int	i;
	int	j;

	i = 0;
	while (find_first_map_line(data.cub_cont[i]) == false && data.cub_cont[i])
		i++;
	while (data.cub_cont[i])
	{
		j = 0;
		while (data.cub_cont[i][j])
		{
			if (ft_strpbrk(&data.cub_cont[i][j], " 01NESW\n") == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map_start_pos(t_data data)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (find_first_map_line(data.cub_cont[i]) == false && data.cub_cont[i])
		i++;
	while (data.cub_cont[i])
	{
		j = 0;
		while (data.cub_cont[i][j])
		{
			if (data.cub_cont[i][j] == 'N'
				|| data.cub_cont[i][j] == 'E'
				|| data.cub_cont[i][j] == 'S'
				|| data.cub_cont[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (1);
	return (0);
}

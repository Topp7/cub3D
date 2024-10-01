/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nonsense.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:19:30 by chorst            #+#    #+#             */
/*   Updated: 2024/10/01 11:38:37 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Main function to check for nonsense in the file
int	check_nonsense(t_data data)
{
	if (check_nonsense_1(data))
		return (1);
	if (check_nonsense_2(data))
		return (1);
	if (check_nonsense_3(data))
		return (1);
	return (0);
}

// Function to check for nonsense before Valid Lines in the file
int	check_nonsense_1(t_data data)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (data.cub_cont[i])
	{
		j = 0;
		skip_empty_lines(data.cub_cont, &i, &j);
		skip_spaces(data.cub_cont, &i, &j);
		if (count == 6)
		{
			if (find_first_map_line(data.cub_cont[i]) == false)
				return (1);
			return (0);
		}
		if (regognize_direction(data.cub_cont[i] + j) == 0)
			return (1);
		count++;
		if (check_nonsense_1helper(data.cub_cont[i] + j))
			return (1);
		i++;
	}
	return (0);
}

// Function to check for nonsense after Path's in the file
int	check_nonsense_2(t_data data)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (data.cub_cont[i])
	{
		j = 0;
		skip_empty_lines(data.cub_cont, &i, &j);
		skip_spaces(data.cub_cont, &i, &j);
		if (regognize_direction(data.cub_cont[i] + j) != 0)
		{
			if (check_nonsense_2helper(data.cub_cont[i] + j))
				return (1);
		}
		i++;
	}
	return (0);
}

// Function to check for nonsense in the map
int	check_nonsense_3(t_data data)
{
	int	i;
	int	j;

	i = 0;
	while (find_first_map_line(data.cub_cont[i]) == false && data.cub_cont[i])
		i++;
	i--;
	while (data.cub_cont[i])
	{
		j = 0;
		while (data.cub_cont[i][j])
		{
			if (data.cub_cont[i][j] != ' ' && data.cub_cont[i][j] != '1'
				&& data.cub_cont[i][j] != '0' && data.cub_cont[i][j] != 'N'
				&& data.cub_cont[i][j] != 'S' && data.cub_cont[i][j] != 'W'
				&& data.cub_cont[i][j] != 'E' && data.cub_cont[i][j] != '\n')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

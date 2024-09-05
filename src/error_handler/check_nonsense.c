/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nonsense.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:19:30 by chorst            #+#    #+#             */
/*   Updated: 2024/09/05 13:34:27 by chorst           ###   ########.fr       */
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
	return (0);
}

// Function that checks for nonsense between directions and them values
int	check_nonsense_helper(char *str)
{
	int		i;

	i = 0;
	if ((str[i] == 'N' && str[i + 1] == 'O')
		|| (str[i] == 'S' && str[i + 1] == 'O')
		|| (str[i] == 'W' && str[i + 1] == 'E')
		|| (str[i] == 'E' && str[i + 1] == 'A'))
		i += 2;
	else if (str[i] == 'C' || str[i] == 'F')
		i++;
	while (str[i] == ' ')
		i++;
	if ((str[i] <= '0' || str[i] > '9')
		&& (str[i] != '.' || str[i + 1] != '/'))
		return (1);
	return (0);
}

// Function to check for nonsense before Valid Lines in the file
int	check_nonsense_1(t_data data)
{
	int	i;
	int	j;

	i = 0;
	while (data.cub_cont[i])
	{
		j = 0;
		while (data.cub_cont[i][j] == '\n')
			i++;
		while (data.cub_cont[i][j] == ' ')
			j++;
		if (data.cub_cont[i][j] != '1' && data.cub_cont[i][j] != 'N'
			&& data.cub_cont[i][j] != 'S' && data.cub_cont[i][j] != 'W'
			&& data.cub_cont[i][j] != 'E' && data.cub_cont[i][j] != 'C'
			&& data.cub_cont[i][j] != 'F')
			return (1);
		if (check_nonsense_helper(data.cub_cont[i] + j))
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

	i = 0;
	while (data.cub_cont[i])
	{
		j = 0;
		while (data.cub_cont[i][j] == '\n')
			i++;
		while (data.cub_cont[i][j] != '.' && data.cub_cont[i][j])
			j++;
		if (data.cub_cont[i][++j] == '/')
		{
			while (data.cub_cont[i][j] != ' ' && data.cub_cont[i][j])
				j++;
			while (data.cub_cont[i][j] == ' ')
				j++;
			if (data.cub_cont[i][j] && data.cub_cont[i][j] != '\n')
				return (1);
		}
		i++;
	}
	return (0);
}

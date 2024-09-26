/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:19:45 by chorst            #+#    #+#             */
/*   Updated: 2024/09/26 16:29:57 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function that recognizes the directions in the file
int	regognize_direction(char *str)
{
	if (str[0] == 'N' && str[1] == 'O')
		return (1);
	else if (str[0] == 'S' && str[1] == 'O')
		return (1);
	else if (str[0] == 'W' && str[1] == 'E')
		return (1);
	else if (str[0] == 'E' && str[1] == 'A')
		return (1);
	else if (str[0] == 'C')
		return (2);
	else if (str[0] == 'F')
		return (2);
	return (0);
}

// Function to check the right amount of directions in the file
void	check_direction_ammount(char *str, t_temp *t)
{
	if (str[0] == 'N' && str[1] == 'O')
		t->flag[0] += 1;
	else if (str[0] == 'S' && str[1] == 'O')
		t->flag[1] += 1;
	else if (str[0] == 'W' && str[1] == 'E')
		t->flag[2] += 1;
	else if (str[0] == 'E' && str[1] == 'A')
		t->flag[3] += 1;
	else if (str[0] == 'C')
		t->flag[4] += 1;
	else if (str[0] == 'F')
		t->flag[5] += 1;
	t->count = 0;
	while (t->flag[t->count] == 1)
		t->count++;
}

// Function to check the directions in the file
int	check_directions(t_data data)
{
	t_temp	t;

	init_temp_struct(&t);
	while (data.cub_cont[t.i])
	{
		t.j = 0;
		skip_empty_lines(data.cub_cont, &t.i, &t.j);
		skip_spaces(data.cub_cont, &t.i, &t.j);
		if (find_first_map_line(data.cub_cont[t.i] + t.j) == true)
			return (free(t.flag), 2);
		if (regognize_direction(data.cub_cont[t.i] + t.j) != 0)
		{
			check_direction_ammount(data.cub_cont[t.i] + t.j, &t);
			if (t.count == 6)
				return (free(t.flag), 0);
		}
		t.i++;
	}
	return (free(t.flag), 1);
}

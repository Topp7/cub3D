/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nonsense_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:36:41 by chorst            #+#    #+#             */
/*   Updated: 2024/09/16 15:05:56 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function that checks for nonsense between directions and them values
int	check_nonsense_1helper(char *str)
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
	if ((str[i] < '0' || str[i] > '9')
		&& (str[i] != '.' || str[i + 1] != '/'))
		return (1);
	return (0);
}

// Function that checks for nonsense after Path values
int	check_nonsense_2helper(char *str)
{
	int	i;

	i = 0;
	if (str[i] == 'C' || str[i] == 'F')
		return (0);
	i += 2;
	while (str[i] == ' ')
		i++;
	if ((str[i] == '.' || str[i + 1] == '/'))
	{
		while (str[i] != ' ' && str[i] != '\n' && str[i])
			i++;
		while (str[i] == ' ')
			i++;
		if ((str[i] != '\n' && str[i] != '\0'))
			return (1);
	}
	return (0);
}

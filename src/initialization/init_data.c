/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:26:04 by chorst            #+#    #+#             */
/*   Updated: 2024/09/03 15:37:12 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function that initializes the data structure
int	init_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (*data == NULL)
	{
		printf("Error\n");
		printf("Malloc failed\n");
		return (1);
	}
	(*data)->p_pos = malloc(sizeof(t_pos));
	if ((*data)->p_pos == NULL)
	{
		printf("Error\n");
		printf("Malloc failed\n");
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:23:55 by chorst            #+#    #+#             */
/*   Updated: 2024/08/30 13:26:11 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Helper function that prints a 2D array
void	print2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s", array[i]);
		i++;
	}
}

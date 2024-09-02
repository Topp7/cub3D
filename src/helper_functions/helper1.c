/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:23:55 by chorst            #+#    #+#             */
/*   Updated: 2024/09/02 17:33:52 by chorst           ###   ########.fr       */
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
		printf("%s\n", array[i]);
		i++;
	}
	printf("\n");
}

void	print_values(t_data *data)
{
	printf("\n");
	printf("%s\n", data->north);
	printf("%s\n", data->south);
	printf("%s\n", data->west);
	printf("%s\n", data->east);
	printf("\n");
	printf("%s\n", data->ceiling);
	printf("%s\n", data->floor);
	printf("\n");
	print2d_array(data->map);
	printf("\n");
	printf("Player position: %d %d\n", data->player_pos->px, data->player_pos->py);
	printf("Player direction: %c\n", data->player_direction);
}

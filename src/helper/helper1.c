/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:23:55 by chorst            #+#    #+#             */
/*   Updated: 2024/09/26 16:27:25 by chorst           ###   ########.fr       */
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
		printf("[%i]	%s\n", i, array[i]);
		i++;
	}
	printf("\n");
}

void	print_values(t_data *data)
{
	printf("\n");
	printf("\n");
	printf("Ceiling color: %d\n", data->c_rgb);
	printf("Floor color: %d\n", data->f_rgb);
	printf("\n");
	print2d_array(data->map);
	printf("\n");
	printf("Player position: x(%f) y(%f)\n", data->p_pos->px, data->p_pos->py);
	printf("Player direction: %c\n", data->p_direction);
}

// Function that extracts the RGB values from a string
unsigned int	extract_rgb(char *rgb)
{
	int				*rgb_values;
	char			**rgb_split;
	int				i;
	unsigned int	hex;

	i = 0;
	hex = 0;
	rgb_values = malloc(sizeof(int) * 3);
	if (!rgb_values)
		return (1);
	rgb_split = ft_split(rgb, ',');
	if (!rgb_split)
		return (1);
	rgb_values[0] = ft_atoi(rgb_split[0]);
	rgb_values[1] = ft_atoi(rgb_split[1]);
	rgb_values[2] = ft_atoi(rgb_split[2]);
	while (rgb_split[i])
		free(rgb_split[i++]);
	free(rgb_split);
	hex = rgb_values[0] << 24 | rgb_values[1] << 16 | rgb_values[2] << 8 | 255;
	free(rgb_values);
	return (hex);
}

void	init_temp_struct(t_temp *temp)
{
	temp->i = 0;
	temp->j = 0;
	temp->k = 0;
	temp->x = 0;
	temp->y = 0;
	temp->count = 0;
	temp->flag = malloc(sizeof(int) * 7);
	if (!temp->flag)
		return ;
	while (temp->count < 7)
		temp->flag[temp->count++] = 0;
	temp->count = 0;
	temp->fd = 0;
}

// Helper function to check if the map is surrounded by walls
int	is_surrounded_by_walls(char **map, int i, int j)
{
	if (map[i][j - 1] == ' '
		|| map[i][j + 1] == ' '
		|| map[i][j + 1] == '\n'
		|| map[i - 1][j] == ' '
		|| map[i + 1][j] == ' '
		|| map[i - 1][j - 1] == ' '
		|| map[i - 1][j + 1] == ' '
		|| map[i - 1][j + 1] == '\n'
		|| map[i + 1][j - 1] == ' '
		|| map[i + 1][j + 1] == ' '
		|| map[i + 1][j + 1] == '\n')
		return (1);
	return (0);
}

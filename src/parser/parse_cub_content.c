/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:20 by chorst            #+#    #+#             */
/*   Updated: 2024/09/02 18:47:34 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function that searches for the first line pattern of the map
bool	find_first_map_line(char *str)
{
	int		i;
	bool	found_ones;

	i = 0;
	found_ones = false;
	while (str[i] == ' ' || str[i] == '1')
	{
		if (str[i] == '1')
			found_ones = true;
		i++;
	}
	if (str[i] == '\n' && found_ones == true)
		return (true);
	return (false);
}

// Function that extracts the map from char **cub_content
char	**extract_map(t_data *data)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	while (find_first_map_line(data->cub_cont[i]) == false && data->cub_cont[i])
		i++;
	if (!data->cub_cont[i] || !data->cub_cont[i + 1])
		return (NULL);
	map = malloc(sizeof(char *) * (ft_strlen(*data->cub_cont) - i + 1));
	if (!map)
		return (NULL);
	while (data->cub_cont[i])
		map[j++] = remove_chars(data->cub_cont[i++], "\n");
	map[j] = NULL;
	return (map);
}

// Function that extracts the paths and rgb values from char **cub_content
void	extract_paths_and_rgbs(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->cub_cont[i])
	{
		j = 0;
		while (data->cub_cont[i][j] == ' ')
			j++;
		if (data->cub_cont[i][j] == 'N' && data->cub_cont[i][j + 1] == 'O')
			data->north = remove_chars(&data->cub_cont[i][2 + j], " \n");
		else if (data->cub_cont[i][j] == 'S' && data->cub_cont[i][j + 1] == 'O')
			data->south = remove_chars(&data->cub_cont[i][2 + j], " \n");
		else if (data->cub_cont[i][j] == 'W' && data->cub_cont[i][j + 1] == 'E')
			data->west = remove_chars(&data->cub_cont[i][2 + j], " \n");
		else if (data->cub_cont[i][j] == 'E' && data->cub_cont[i][j + 1] == 'A')
			data->east = remove_chars(&data->cub_cont[i][2 + j], " \n");
		else if (data->cub_cont[i][j] == 'C' && data->cub_cont[i][j + 1] == ' ')
			data->ceiling = remove_chars(&data->cub_cont[i][1 + j], " \n");
		else if (data->cub_cont[i][j] == 'F' && data->cub_cont[i][j + 1] == ' ')
			data->floor = remove_chars(&data->cub_cont[i][1 + j], " \n");
		i++;
	}
}

// Function that extracts the player position and direction from the map
void	extract_player_data(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	data->player_pos = malloc(sizeof(t_pos)); // remove after initialization
	while (data->map[x])
	{
		y = 0;
		while (data->map[x][y])
		{
			if (data->map[x][y] == 'N'
				|| data->map[x][y] == 'E'
				|| data->map[x][y] == 'S'
				|| data->map[x][y] == 'W')
			{
				data->player_pos->px = x;
				data->player_pos->py = y;
				data->player_direction = data->map[x][y];
				return ;
			}
			y++;
		}
		x++;
	}
}

// Main extraction function that calls all the other extraction functions
int	extract_cub_data(t_data *data)
{
	data->map = extract_map(data);
	if (data->map == NULL)
		return (printf("Map extraction failed"));
	extract_paths_and_rgbs(data);
	if (data->north == NULL || data->south == NULL || data->west == NULL
		|| data->east == NULL || data->ceiling == NULL || data->floor == NULL)
		return (printf("Path or RGB extraction failed"));
	extract_player_data(data);
	return (0);
}

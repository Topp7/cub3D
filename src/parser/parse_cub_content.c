/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:20 by chorst            #+#    #+#             */
/*   Updated: 2024/09/26 16:25:49 by chorst           ###   ########.fr       */
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
char	**extract_map(char *argv, t_data *data)
{
	int		i;
	int		x;
	char	**map;
	int		fd;

	i = 0;
	x = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (find_first_map_line(data->cub_cont[i]) == false && data->cub_cont[i])
		i++;
	if (!data->cub_cont[i] || !data->cub_cont[i + 1])
		return (NULL);
	data->map_x = file_line_count(fd) - i;
	map = malloc(sizeof(char *) * (data->map_x + 1));
	if (!map)
		return (close(fd), NULL);
	close(fd);
	while (data->cub_cont[i])
		map[x++] = remove_chars(data->cub_cont[i++], "\n");
	map[x] = NULL;
	data->map_x = x - 1;
	return (map);
}

// Function that extracts the paths and rgb values from char **cub_content
void	extract_paths_and_rgbs(t_data *data)
{
	int		x;
	int		y;

	x = 0;
	while (data->cub_cont[x])
	{
		y = 0;
		while (data->cub_cont[x][y] == ' ')
			y++;
		if (data->cub_cont[x][y] == 'C' && data->cub_cont[x][y + 1] == ' ')
			data->ceiling = remove_chars(&data->cub_cont[x][1 + y], " \n");
		else if (data->cub_cont[x][y] == 'F' && data->cub_cont[x][y + 1] == ' ')
			data->floor = remove_chars(&data->cub_cont[x][1 + y], " \n");
		x++;
	}
	data->c_rgb = extract_rgb(data->ceiling);
	data->f_rgb = extract_rgb(data->floor);
}

// Function that extracts the player position and direction from the map
void	extract_player_data(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
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
				data->p_pos->px = (x + 0.5) * TILE + 0.001;
				data->p_pos->py = (y + 0.5) * TILE + 0.001;
				data->p_direction = data->map[x][y];
				return ;
			}
			y++;
		}
		x++;
	}
}

// Main extraction function that calls all the other extraction functions
int	extract_cub_data(char *argv, t_data *data)
{
	data->map = extract_map(argv, data);
	if (data->map == NULL)
		return (error_msg("Map extraction failed"));
	extract_paths_and_rgbs(data);
	if (data->ceiling == NULL || data->floor == NULL)
		return (error_msg("Path or RGB extraction failed"));
	extract_player_data(data);
	return (0);
}

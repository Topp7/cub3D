/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:23:20 by chorst            #+#    #+#             */
/*   Updated: 2024/08/30 15:37:24 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function that searches for the first line of a map
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

// Function that extracts the map from the cub_content
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
	{
		map[j] = ft_strdup(data->cub_cont[i]);
		i++;
		j++;
	}
	map[j] = NULL;
	return (map);
}

void	extract_direction_str(t_data *data)
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
			data->north = ft_strdup(data->cub_cont[i]);
		if (data->cub_cont[i][j] == 'S' && data->cub_cont[i][j + 1] == 'O')
			data->south = ft_strdup(data->cub_cont[i]);
		if (data->cub_cont[i][j] == 'W' && data->cub_cont[i][j + 1] == 'E')
			data->west = ft_strdup(data->cub_cont[i]);
		if (data->cub_cont[i][j] == 'E' && data->cub_cont[i][j + 1] == 'A')
			data->east = ft_strdup(data->cub_cont[i]);
		if (data->cub_cont[i][j] == 'C' && data->cub_cont[i][j + 1] == ' ')
			data->ceiling = ft_strdup(data->cub_cont[i]);
		if (data->cub_cont[i][j] == 'F' && data->cub_cont[i][j + 1] == ' ')
			data->floor = ft_strdup(data->cub_cont[i]);
		i++;
	}
}

void	extract_paths(t_data *data)
{
	data->temp = NULL;
	extract_direction_str(data);
	data->temp = remove_chars(data->north, " \n");
	free(data->north);
	data->north = ft_strdup(data->temp + 2);
	free(data->temp);
	data->temp = remove_chars(data->south, " \n");
	free(data->south);
	data->south = ft_strdup(data->temp + 2);
	free(data->temp);
	data->temp = remove_chars(data->west, " \n");
	free(data->west);
	data->west = ft_strdup(data->temp + 2);
	free(data->temp);
	data->temp = remove_chars(data->east, " \n");
	free(data->east);
	data->east = ft_strdup(data->temp + 2);
	free(data->temp);
	printf("\n");
	printf("%s\n", data->north);
	printf("%s\n", data->south);
	printf("%s\n", data->west);
	printf("%s\n", data->east);
}

void	extract_rgb(t_data *data)
{
	data->temp = NULL;
	data->temp = remove_chars(data->ceiling, " \n");
	free(data->ceiling);
	data->ceiling = ft_strdup(data->temp + 1);
	free(data->temp);
	data->temp = remove_chars(data->floor, " \n");
	free(data->floor);
	data->floor = ft_strdup(data->temp + 1);
	free(data->temp);
	printf("\n");
	printf("%s\n", data->ceiling);
	printf("%s\n", data->floor);
}

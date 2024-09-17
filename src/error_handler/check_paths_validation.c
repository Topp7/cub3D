/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_paths_validation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:30:20 by chorst            #+#    #+#             */
/*   Updated: 2024/09/16 17:00:15 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	direction(char *str)
{
	if (str[0] == 'N' && str[1] == 'O')
		return (1);
	else if (str[0] == 'S' && str[1] == 'O')
		return (2);
	else if (str[0] == 'W' && str[1] == 'E')
		return (3);
	else if (str[0] == 'E' && str[1] == 'A')
		return (4);
	return (0);
}

void	path_validation(t_data *data)
{
	if (!data->north_tex)
		return ;
	else if (!data->south_tex)
		return ;
	else if (!data->west_tex)
		return ;
	else if (!data->east_tex)
		return ;
}

void	load_path_into_struct(t_data *data, char *path)
{
	if (direction(path) == 1)
		data->north_tex = mlx_load_png(path + 2);
	else if (direction(path) == 2)
		data->south_tex = mlx_load_png(path + 2);
	else if (direction(path) == 3)
		data->west_tex = mlx_load_png(path + 2);
	else if (direction(path) == 4)
		data->east_tex = mlx_load_png(path + 2);
	path_validation(data);
}

int	check_paths(t_data *data)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	while (data->cub_cont[i])
	{
		j = 0;
		skip_empty_lines(data->cub_cont, &i, &j);
		skip_spaces(data->cub_cont, &i, &j);
		if (regognize_direction(data->cub_cont[i] + j) == 1)
		{
			path = remove_chars(data->cub_cont[i] + j, " \n");
			load_path_into_struct(data, path);
			free(path);
			i++;
		}
		i++;
	}
	return (0);
}

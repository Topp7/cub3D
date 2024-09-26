/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:19:59 by chorst            #+#    #+#             */
/*   Updated: 2024/09/26 16:36:27 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_rgb(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
}

int	check_rgb_helper(char *str)
{
	int		i;
	int		j;
	char	*temp;
	char	**rgb;

	i = 0;
	j = 0;
	temp = remove_chars(str, " \n");
	rgb = ft_split(temp, ',');
	free(temp);
	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j] >= '0' && rgb[i][j] <= '9')
			j++;
		if (rgb[i][j] != '\0')
			return (free(rgb), 1);
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (free(rgb), 2);
		i++;
	}
	free_rgb(rgb);
	return (0);
}

int	check_rgb(t_data data)
{
	int	i;
	int	j;

	i = 0;
	while (data.cub_cont[i])
	{
		j = 0;
		while (data.cub_cont[i][j] == '\n')
			if (!data.cub_cont[++i])
				return (0);
		while (data.cub_cont[i][j] == ' ')
			j++;
		if (data.cub_cont[i][j] == 'C' || data.cub_cont[i][j] == 'F')
		{
			if (check_rgb_helper(data.cub_cont[i] + j + 1) == 1)
				return (1);
			if (check_rgb_helper(data.cub_cont[i] + j + 1) == 2)
				return (2);
		}
		if (!data.cub_cont[i])
			return (0);
		i++;
	}
	return (0);
}

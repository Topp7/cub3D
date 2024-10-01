/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 08:41:25 by chorst            #+#    #+#             */
/*   Updated: 2024/10/01 10:18:34 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function returns 0 if the string contains any character from the charset
int	ft_strpbrk(const char *str, const char *charset)
{
	const char	*c;

	while (*str)
	{
		c = charset;
		while (*c)
		{
			if (*str == *c)
				return (0);
			c++;
		}
		str++;
	}
	return (1);
}

void	skip_empty_lines(char **cub_cont, int *i, int *j)
{
	while (cub_cont[*i][*j] == '\n' && cub_cont[*i + 1])
		(*i)++;
}

void	skip_spaces(char **cub_cont, int *i, int *j)
{
	while (cub_cont[*i][*j] == ' ')
		(*j)++;
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '\n' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	init_textures(t_data *data)
{
	data->north_tex = NULL;
	data->south_tex = NULL;
	data->west_tex = NULL;
	data->east_tex = NULL;
}

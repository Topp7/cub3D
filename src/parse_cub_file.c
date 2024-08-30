/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:35:42 by chorst            #+#    #+#             */
/*   Updated: 2024/08/29 18:16:57 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	file_line_count(int fd)
{
	int		count;
	char	*line;

	count = 0;
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (count);
}

char	**file_read(char *cub_file, char **cub_content)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(cub_file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	cub_content = malloc(sizeof(char *) * (file_line_count(fd) + 1));
	if (cub_content == NULL)
		return (close(fd), NULL);
	close(fd);
	fd = open(cub_file, O_RDONLY);
	cub_content[i] = get_next_line(fd);
	while (cub_content[i] != NULL)
	{
		i++;
		cub_content[i] = get_next_line(fd);
	}
	close(fd);
	return (cub_content);
}

int	parse_cub_file(char *cub_file, t_data *data)
{
	char	**cub_content;

	cub_content = NULL;
	cub_content = file_read(cub_file, cub_content);
	if (cub_content == NULL)
		return (1);
	data->cub_content = cub_content;
	return (0);
}

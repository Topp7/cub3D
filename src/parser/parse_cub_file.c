/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:35:42 by chorst            #+#    #+#             */
/*   Updated: 2024/10/01 11:31:01 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Function that counts the number of lines in a file
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

// Function that reads the cub file and stores it in a 2D array
int	parse_cub_file(char *cub_file, t_data *data)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(cub_file, O_RDONLY);
	if (fd == -1)
		return (error_msg("File can not be opened"));
	data->cub_cont = malloc(sizeof(char *) * (file_line_count(fd) + 1));
	if (data->cub_cont == NULL)
		return (close(fd), 1);
	close(fd);
	fd = open(cub_file, O_RDONLY);
	if (fd == -1)
		return (free(data->cub_cont), error_msg("Parsing failed"));
	data->cub_cont[i] = get_next_line(fd);
	while (data->cub_cont[i] != NULL)
	{
		i++;
		data->cub_cont[i] = get_next_line(fd);
	}
	close(fd);
	return (0);
}

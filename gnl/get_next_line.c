/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:42:32 by chorst            #+#    #+#             */
/*   Updated: 2024/08/29 16:56:34 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*read_better(int fd, char **str, char *newline, int n)
{
	int	i;
	int	str_length;

	i = 0;
	while (*str)
	{
		if ((*str)[i] == '\0')
		{
			str_length = read(fd, *str, BUFFER_SIZE);
			if (n > 0 && str_length == 0)
				break ;
			(*str)[str_length] = '\0';
			i = 0;
		}
		if (i == 0 && str_length > 0)
			newline = ft_realloc(newline, n + str_alloc_len(*str) + 1, n);
		if (newline == NULL || str_length <= 0)
			return (free(*str), *str = NULL);
		newline[n++] = (*str)[i++];
		if ((*str)[i - 1] == '\n')
			break ;
	}
	return (str_after_n(*str), newline);
}

char	*get_next_line(int fd)
{
	int			n;
	char		*newline;
	static char	*str;

	n = 0;
	newline = NULL;
	if (str == NULL)
		str = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (read(fd, 0, 0) < 0 || str == NULL)
		return (free(str), str = NULL);
	return (read_better(fd, &str, newline, n));
}

//dshsdhdshdhs

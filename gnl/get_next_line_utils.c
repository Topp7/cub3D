/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:43:03 by chorst            #+#    #+#             */
/*   Updated: 2024/08/29 17:02:42 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	str_alloc_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

void	str_after_n(char *str)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i])
		str[b++] = str[i++];
	str[b] = '\0';
}

void	*ft_realloc(void *ptr, size_t new_size, int n)
{
	void	*new_bigger_ptr;

	if (ptr == NULL)
		ptr = ft_calloc(sizeof(char), new_size);
	new_bigger_ptr = ft_calloc(sizeof(char), new_size);
	if (new_bigger_ptr == NULL || ptr == NULL)
		return (free(new_bigger_ptr), free(ptr), NULL);
	ft_memmove(new_bigger_ptr, ptr, n);
	free(ptr);
	return (new_bigger_ptr);
}

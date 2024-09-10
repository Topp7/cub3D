/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 08:41:25 by chorst            #+#    #+#             */
/*   Updated: 2024/09/10 09:44:43 by chorst           ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:55:01 by chorst            #+#    #+#             */
/*   Updated: 2024/09/04 16:26:15 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	error_checks(t_data *data)
{
	if (check_for_nonsense(*data))
		return (error_msg("There is nonsense in the map!"));
	if (check_for_rgb(*data) == 1)
		return (error_msg("There is nonsense in RGB Values!"));
	if (check_for_rgb(*data) == 2)
		return (error_msg("RGB values are out of range!"));
	// if (check_for_directions(data) != 6)
	// 	return (error_msg("Missing directions or doubled directions"));
	return (0);
}

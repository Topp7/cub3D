/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:55:01 by chorst            #+#    #+#             */
/*   Updated: 2024/09/05 15:03:51 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	error_checks(t_data *data)
{
	if (check_nonsense(*data))
		return (error_msg("There is nonsense in the file!"));
	if (check_directions(*data))
		return (error_msg("Missing or doubled directions"));
	if (check_rgb(*data) == 1)
		return (error_msg("There is nonsense in RGB Values!"));
	if (check_rgb(*data) == 2)
		return (error_msg("RGB values are out of range!"));
	// if (check_order(*data))
	// 	return (error_msg("Wrong order of elements. Map need to be last"));
	return (0);
}

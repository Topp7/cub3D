/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:55:01 by chorst            #+#    #+#             */
/*   Updated: 2024/09/09 16:32:14 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	error_checks(t_data *data)
{
	if (check_nonsense(*data))
		return (error_msg("There is nonsense in the file!"));
	if (check_directions(*data) == 2)
		return (error_msg("Wrong order of elements. Map needs to be last"));
	if (check_directions(*data) == 1)
		return (error_msg("Missing or doubled directions"));
	if (check_rgb(*data) == 1)
		return (error_msg("There is nonsense in RGB Values!"));
	if (check_rgb(*data) == 2)
		return (error_msg("RGB values are out of range!"));
	// if (check_map_surrounded(*data))
	// 	return (error_msg("Map is not completely closed!"));
	// if (check_map_characters(*data))
	// 	return (error_msg("There is a wrong character in the map!"));
	// if (check_start_pos(*data))
	// 	return (error_msg("There is no starting position!"));
	// if (check_map_structure(*data))
	// 	return (error_msg("We do not alow dead lines or blocks!"));
	return (0);
}

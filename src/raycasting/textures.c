/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:38:56 by stopp             #+#    #+#             */
/*   Updated: 2024/09/25 11:44:34 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int	get_rgba(int r, int g, int b, int a)
{
	unsigned int	color;

	color = (r << 24 | g << 16 | b << 8 | a);
	return (color);
}

int	get_tex_y(t_data *data)
{
	int	tex_y;

	if (data->hr_pos->rlen < data->vr_pos->rlen)
		tex_y = data->hr_pos->ry;
	else
		tex_y = data->vr_pos->rx;
	tex_y = (tex_y) % TILE;
	return (tex_y);
}

mlx_texture_t	*find_texture(t_data *data)
{
	if (data->hr_pos->rlen <= data->vr_pos->rlen)
	{
		if (data->hr_pos->ra > PI)
			return (data->north_tex);
		else
			return (data->south_tex);
	}
	else
	{
		if (data->vr_pos->ra < (PI * 1.5) && data->vr_pos->ra > (PI * 0.5))
			return (data->west_tex);
		else
			return (data->east_tex);
	}
}

unsigned int	get_tex_color(mlx_texture_t	*texture, float x, int y)
{
	int				i;

	i = ((int)x * TILE + (int)y) * 4;
	return (get_rgba(texture->pixels[i], texture->pixels[i + 1],
			texture->pixels[i + 2], texture->pixels[i + 3]));
}

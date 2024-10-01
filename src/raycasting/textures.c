/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:38:56 by stopp             #+#    #+#             */
/*   Updated: 2024/09/28 20:11:29 by stopp            ###   ########.fr       */
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
		tex_y = floor(data->hr_pos->ry);
	else
		tex_y = floor(data->vr_pos->rx);
	tex_y = (tex_y) % TILE;
	return (tex_y);
}

mlx_texture_t	*find_texture(t_data *data)
{
	if (data->hr_pos->rlen < data->vr_pos->rlen)
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

unsigned int	get_tex_color(mlx_texture_t	*texture, int x, int y)
{
	int				i;

	if (x < 0 || x >= TILE)
		return (0);
	i = (x * TILE + y) * 4;
	if (i < 0 || i >= (TILE * TILE + TILE) * 4 - 3)
		return (0);
	return (get_rgba(texture->pixels[i], texture->pixels[i + 1],
			texture->pixels[i + 2], texture->pixels[i + 3]));
}

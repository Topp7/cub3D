/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:41 by stopp             #+#    #+#             */
/*   Updated: 2024/09/28 20:12:23 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	calc_line_length(t_data *data, float degree_change)
{
	float	line_h;
	float	dist;

	if (data->vr_pos->rlen > data->hr_pos->rlen)
		dist = data->hr_pos->rlen;
	else
		dist = data->vr_pos->rlen;
	dist = dist * cos(degree_change);
	line_h = (TILE * HEIGHT) / dist;
	return (line_h);
}

void	draw_wall_line(t_data *data, int j, float degree_change)
{
	float	line;
	int		tex_y;
	float	x_step;
	float	offset;
	int		i;

	line = calc_line_length(data, degree_change);
	tex_y = get_tex_y(data);
	x_step = (TILE / line);
	offset = 0;
	if (line > HEIGHT)
	{
		offset = ((line - HEIGHT) / 2) * x_step;
		line = HEIGHT;
	}
	i = 0;
	while (i < line)
	{
		mlx_put_pixel(data->w_img, j, (HEIGHT / 2) - (line / 2) + i,
			get_tex_color(find_texture(data), floor((x_step * i + offset)),
				tex_y));
		i++;
	}
}

float	adjust_angle(float angle)
{
	if (angle > 2 * PI)
		angle -= 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

void	draw_3d(t_data *data)
{
	int		j;
	float	sixty_degree;
	float	degree_change;

	j = -384;
	sixty_degree = ((2 * PI) / 360) * 60;
	data->w_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->w_img)
		return ;
	while (j < 384)
	{
		if (j != 0)
			degree_change = (sixty_degree / WIDTH) * j;
		else
			degree_change = 0;
		data->hr_pos->ra = data->p_pos->pa + degree_change;
		data->vr_pos->ra = data->p_pos->pa + degree_change;
		data->hr_pos->ra = adjust_angle(data->hr_pos->ra);
		data->vr_pos->ra = adjust_angle(data->vr_pos->ra);
		horizontal_rays(data);
		vertical_rays(data);
		draw_wall_line(data, j + 384, degree_change);
		j++;
	}
}

void	raycast_exe(t_data *data)
{
	add_testdata(data);
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data->mlx_ptr)
		return ;
	draw_fnc(data);
	mlx_loop_hook(data->mlx_ptr, control_keyhook, data);
	mlx_key_hook(data->mlx_ptr, keyhandle, data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}

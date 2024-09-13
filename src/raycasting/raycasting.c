/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:41 by stopp             #+#    #+#             */
/*   Updated: 2024/09/13 11:40:48 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_wall_line(t_data *data, int j)
{
	int		line_h;
	int		dist;
	float	offset;
	int		i;

	if (data->vr_pos->rlen > data->hr_pos->rlen)
		dist = data->hr_pos->rlen;
	else
		dist = data->vr_pos->rlen;
	offset = data->p_pos->pa - data->vr_pos->ra;
	if (offset > 2 * PI)
		offset -= 2 * PI;
	if (offset < 0)
		offset += 2 * PI;
	dist *= cos(offset);
	line_h = (30 * HEIGHT) / dist;
	if (line_h > HEIGHT)
		line_h = HEIGHT;
	i = 0;
	while (i < line_h)
	{
		mlx_put_pixel(data->p_img, j, (HEIGHT / 2) - (line_h / 2) + i,
			0x00FF0000 | 255);
		i++;
	}
}

void	adjust_angles(t_data *data)
{
	if (data->hr_pos->ra > 2 * PI)
		data->hr_pos->ra -= 2 * PI;
	if (data->hr_pos->ra < 0)
		data->hr_pos->ra += 2 * PI;
	if (data->vr_pos->ra > 2 * PI)
		data->vr_pos->ra -= 2 * PI;
	if (data->vr_pos->ra < 0)
		data->vr_pos->ra += 2 * PI;
}

void	draw_3d(t_data *data)
{
	int		j;
	float	sixty_degree;
	float	degree_change;

	j = -360;
	sixty_degree = ((2 * PI) / 360) * 60;
	while (j <= 360)
	{
		if (j != 0)
			degree_change = (sixty_degree / 720) * j;
		else
			degree_change = 0;
		data->hr_pos->ra = data->p_pos->pa + degree_change;
		data->vr_pos->ra = data->p_pos->pa + degree_change;
		adjust_angles(data);
		update_rays(data);
		draw_wall_line(data, j + 360);
		j++;
	}
}

void	control_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx_ptr);
	move_player(keydata, data);
	turn_player(keydata, data);
	mlx_delete_image(data->mlx_ptr, data->p_img);
	draw_player(data);
	draw_3d(data);
}

void	update_rays(t_data *data)
{
	horizontal_rays(data);
	vertical_rays(data);
	// if (data->vr_pos->rlen < data->hr_pos->rlen)
	// 	mlx_put_pixel(data->p_img, data->vr_pos->ry,
	// 		data->vr_pos->rx, 0xFFFFFF00 | 255);
	// else
	// 	mlx_put_pixel(data->p_img, data->hr_pos->ry,
	// 		data->hr_pos->rx, 0xFFFFFF00 | 255);
}

void	raycast_exe(t_data *data)
{
	add_testdata(data);
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data->mlx_ptr)
		return ;
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img)
		return ;
	draw_map(data);
	draw_player(data);
	mlx_key_hook(data->mlx_ptr, control_keyhook, data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}

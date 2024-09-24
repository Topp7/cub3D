/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:41 by stopp             #+#    #+#             */
/*   Updated: 2024/09/24 19:24:08 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	calc_line_length(t_data *data)
{
	float	line_h;
	float	dist;
	float	offset;

	if (data->vr_pos->rlen > data->hr_pos->rlen)
		dist = data->hr_pos->rlen;
	else
		dist = data->vr_pos->rlen;
	offset = (data->p_pos->pa - data->vr_pos->ra);
	offset = adjust_angle(offset);
	dist = dist * cos(offset);
	line_h = (TILE * HEIGHT) / dist;
	return (line_h);
}

void	draw_wall_line(t_data *data, int j)
{
	float	line;
	int		tex_y;
	float	x_step;
	int		offset;
	int		i;

	line = calc_line_length(data);
	tex_y = get_tex_y(data);
	x_step = (TILE / line);
	offset = 0;
	if (line > HEIGHT)
	{
		while (x_step * offset < ((line - HEIGHT) / 2))
			offset++;
		line = HEIGHT;
	}
	i = 0;
	while (i < line)
	{
		mlx_put_pixel(data->w_img, j, (HEIGHT / 2) - (line / 2) + i,
			get_tex_color(find_texture(data), x_step * (i + offset), tex_y));
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
	while (j <= 383)
	{
		if (j != 0)
			degree_change = (sixty_degree / 720) * j;
		else
			degree_change = 0;
		data->hr_pos->ra = data->p_pos->pa + degree_change;
		data->vr_pos->ra = data->p_pos->pa + degree_change;
		data->hr_pos->ra = adjust_angle(data->hr_pos->ra);
		data->vr_pos->ra = adjust_angle(data->vr_pos->ra);
		update_rays(data);
		draw_wall_line(data, j + 384);
		j++;
	}
}

void	control_keyhook(void *param)
{
	t_data	*data;

	data = param;
	mlx_delete_image(data->mlx_ptr, data->w_img);
	move_player(data);
	turn_player(data);
	draw_3d(data);
	mlx_image_to_window(data->mlx_ptr, data->w_img, 0, 0);
	draw_map(data);
}

void	update_rays(t_data *data)
{
	horizontal_rays(data);
	vertical_rays(data);
}

void	release(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		data->left_right = 0;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		data->left_right = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		data->up_down = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		data->up_down = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		data->rotate = 0;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		data->rotate = 0;
}

void	keyhandle(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx_ptr);
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		data->left_right = -1;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		data->left_right = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		data->up_down = -1;
	else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		data->up_down = 1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		data->rotate = -1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		data->rotate = 1;
	release(keydata, data);
}

void	raycast_exe(t_data *data)
{
	add_testdata(data);
	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data->mlx_ptr)
		return ;
	draw_fnc(data);
	draw_map(data);
	draw_3d(data);
	mlx_loop_hook(data->mlx_ptr, control_keyhook, data);
	mlx_key_hook(data->mlx_ptr, keyhandle, data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}

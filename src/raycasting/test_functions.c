/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:05:20 by stopp             #+#    #+#             */
/*   Updated: 2024/09/28 19:59:13 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	add_testdata(t_data *data)
{
	data->hr_pos = malloc(sizeof(t_ray));
	if (!data->hr_pos)
		return ;
	data->vr_pos = malloc(sizeof(t_ray));
	if (!data->vr_pos)
		return ;
	if (data->p_direction == 'S')
		data->p_pos->pa = 0.5 * PI;
	else if (data->p_direction == 'N')
		data->p_pos->pa = 1.5 * PI;
	else if (data->p_direction == 'W')
		data->p_pos->pa = PI;
	else
		data->p_pos->pa = 0;
	data->hr_pos->ra = data->p_pos->pa;
	data->vr_pos->ra = data->p_pos->pa;
	data->p_pos->pdx = (float)(sin(data->p_pos->pa));
	data->p_pos->pdy = (float)(cos(data->p_pos->pa));
	data->left_right = 0;
	data->up_down = 0;
	data->rotate = 0;
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

void	control_keyhook(void *param)
{
	t_data	*data;

	data = param;
	mlx_delete_image(data->mlx_ptr, data->w_img);
	move_player(data);
	turn_player(data);
	draw_3d(data);
	draw_map(data);
	mlx_image_to_window(data->mlx_ptr, data->w_img, 0, 0);
}

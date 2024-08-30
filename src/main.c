/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:12:29 by stopp             #+#    #+#             */
/*   Updated: 2024/08/30 14:52:09 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	error_msg(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	return (1);
}

int	input_chk(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc != 2)
		return (error_msg("Wrong amout of Arguments"));
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
		return (error_msg("Wrong filetype"));
	return (0);
}

void	save_map(t_data *data)
{
	(void)data;
}

int	save_input(t_data *data)
{
	int		fd;

	fd = open(data->file, O_RDONLY);
	if (fd <= 0)
		return (0);
	save_map(data);
	data->mlx_ptr = mlx_init(2000, 1000, "Test", true);
	if (!data->mlx_ptr)
		return (0);
	return (1);
}

void	control_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(data->mlx_ptr);
		}
	}
}

// int	main(int argc, char *argv[])
// {
// 	t_data	*data;

// 	if (input_chk(argc, argv) == 1)
// 		return (1);
// 	data = malloc(sizeof(t_data));
// 	if (!data)
// 		return (1);
// 	data->file = argv[1];
// 	save_input(data);
// 	mlx_key_hook(data->mlx_ptr, control_keyhook, data);
// 	mlx_loop(data->mlx_ptr);
// 	mlx_terminate(data->mlx_ptr);
// 	printf("Hello, World!\n");
// }

int main(int argc, char **argv)
{
	t_data	data;
	char	**map;

	if (argc != 2)
		return (error_msg("Wrong amount of arguments"));
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
		return (error_msg("Wrong filetype"));
	if (parse_cub_file(argv[1], &data) == 1)
		return (1);
	if (data.cub_cont == NULL)
		return (error_msg("No file found"));
	map = extract_map(data);
	if (map == NULL)
		return (error_msg("No map found"));
	print2d_array(map);
	extract_paths(&data);
	free(data.cub_cont);
	free(map);
	return (0);
}

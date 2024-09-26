/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:12:29 by stopp             #+#    #+#             */
/*   Updated: 2024/09/26 13:52:46 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	error_msg(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	return (1);
}

int	input_check(int argc, char *argv[])
{
	int	i;
	int	fd;

	fd = 0;
	i = 0;
	if (argc != 2)
		return (error_msg("Wrong amout of Arguments"));
	if (ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub", 4) != 0)
		return (error_msg("Wrong filetype"));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (error_msg("cant open file"));
	close(fd);
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

// void	start_window(t_data *data)
// {
// 	data->mlx_ptr = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
// 	if (!data->mlx_ptr)
// 		exit(1);
// 	data->north_img = mlx_texture_to_image(data->mlx_ptr, data->north_tex);
// 	data->img = mlx_new_image(data->mlx_ptr, 2000, 2000);
// 	if (!data->img)
// 		return ;
// 	mlx_loop(data->mlx_ptr);
// 	mlx_terminate(data->mlx_ptr);
// }

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (input_check(argc, argv))
		return (1);
	if (init_data(&data))
		return (1);
	if (parse_cub_file(argv[1], data))
		return (1);
	if (error_checks(data))
		return (1);
	if (extract_cub_data(argv[1], data))
		return (1);
	// start_window(data);
	raycast_exe(data);
	free(data->cub_cont);
	return (0);
}

// -fsanitize=address vor der Eval entfernen aus der Makefile
// cub3d.dSYM vor der Eval entfernen

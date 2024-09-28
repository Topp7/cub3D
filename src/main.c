/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:12:29 by stopp             #+#    #+#             */
/*   Updated: 2024/09/26 16:52:40 by chorst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_datas(t_data *data)
{
	int	i;

	i = 0;
	while (data->cub_cont[i])
		free(data->cub_cont[i++]);
	i = 0;
	while (data->map[i])
		free(data->map[i++]);
	free(data->map);
	free(data->cub_cont);
	free(data->p_pos);
	free(data->hr_pos);
	free(data->vr_pos);
	mlx_delete_texture(data->north_tex);
	mlx_delete_texture(data->south_tex);
	mlx_delete_texture(data->west_tex);
	mlx_delete_texture(data->east_tex);
	free(data->ceiling);
	free(data->floor);
	free(data);
}

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

// void leak()
// {
// 	system("leaks cub3d");
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
	raycast_exe(data);
	free_datas(data);
	return (0);
}

// -fsanitize=address vor der Eval entfernen aus der Makefile
// cub3d.dSYM vor der Eval entfernen

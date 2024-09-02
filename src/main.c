/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorst <chorst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:12:29 by stopp             #+#    #+#             */
/*   Updated: 2024/09/02 17:37:13 by chorst           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data	*data;

	// implement error handling here
	if (input_chk(argc, argv) == 1)
		return (1);
	// implement initialization here
	data = malloc(sizeof(t_data));
	if (!data)
		return (error_msg("Malloc failed"));
	if (parse_cub_file(argv[1], data) == 1 || extract_cub_data(data) == 1)
		return (1);
	print_values(data);
	// raycast_exe(data);
	free(data->cub_cont);
	return (0);
}

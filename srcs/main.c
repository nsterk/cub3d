/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/27 14:57:00 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/12 02:28:36 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

static void	*start_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (NULL);
	data->window = mlx_new_window(data->mlx, data->res.x, data->res.y, "cub3D");
	if (!data->window)
		return (NULL);
	data->img.ptr = mlx_new_image(data->mlx, data->res.x, data->res.y);
	if (!data->img.ptr)
		return (NULL);
	data->img.addr = mlx_get_data_addr(data->img.ptr, &data->img.bpp,
			&data->img.len, &data->img.endian);
	if (!data->img.addr)
		return (NULL);
	return ("1");
}

int	loops(t_data *data)
{
	mlx_hook(data->window, 17, 0L, exit_window, data);
	mlx_hook(data->window, 2, (1L << 0), key_press, data);
	mlx_loop_hook(data->mlx, &window_loop, data);
	mlx_hook(data->window, 3, (1L << 1), key_release, data);
	mlx_loop(data->mlx);
	return (1);
}

static t_status	validate_input(int argc, char **argv, t_file *file)
{
	size_t	len;

	if (argc > 1 && argc < 4)
	{
		len = ft_strlen(argv[1]);
		if (!ft_strcmp(argv[1] + (len - 4), ".cub"))
			file->path = argv[1];
		else
			return (EXTENSION_ERROR);
		if (argc == 3)
		{
			if (!ft_strcmp(argv[2], "--save"))
				file->BMP = 1;
			else
				return (ARGSAVE_ERROR);
		}
	}
	else
		return (ARGNO_ERROR);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.status = validate_input(argc, argv, &data.file);
	if (data.status != SUCCESS)
		return (exit_window(&data));
	init_data(&data);
	data.status = parse_start(&data);
	if (data.status != SUCCESS)
		return (exit_window(&data));
	start_mlx(&data);
	if (!complete_data(&data))
		return (exit_window(&data));
	loops(&data);
	exit_window(&data);
	return (0);
}

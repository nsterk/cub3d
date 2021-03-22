/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/02 13:44:38 by nsterk        #+#    #+#                 */
/*   Updated: 2021/03/22 15:03:59 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static int	id_path(t_file *file, char *s)
{
	static const t_id	id[3] = {
		[0] = &parse_res,
		[1] = &parse_colour,
	};

	return (((*(u_int16_t *)s == *(u_int16_t *) "R ") && id[0](file, s + 1))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "C ") && id[1](file->ceiling, s + 1))
		|| ((*(u_int16_t *)s == *(u_int16_t *) "F ") && id[1](file->floor, s + 1)));
}

static char	first_char(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (*str);
}
/*
static int	ready_for_map(t_file *file)
{
	if (!file->res.x || file->res.y)
		return (0);
	return (1);
}
*/
int	parse_start(t_file *file)
{
	int		fd;
	int		ret;
	int		i;

	fd = open(file->str, O_RDONLY);
	if (fd < 0)
		return (0);
	ret = get_next_line(fd, &file->line);
	while (ret > 0)
	{
		i = 0;
		if (ft_isalpha(first_char(file->line)))
		{
			while (!ft_isalpha(file->line[i]))
				i++;
			if (!id_path(file, file->line + i))
			{
				return (0);
			}
		}
		free(file->line);
		ret = get_next_line(fd, &file->line);
		/*
		else if (ready_for_map(file) && ft_isdigit(first_char(file->line)))
		*/
	}
	free(file->line);
	printf("res.x: %i, res.y: %i\n", file->res.x, file->res.y);
	close(fd);
	return (1);
}

int	parse_res(t_file *file, char *line)
{
	size_t	i;

	i = 0;
	line = (char *)ft_skipspace(line);
	if (!ft_isdigit(*line))
		return (0);
	file->res.x = ft_atoi(line);
	while (ft_isdigit(line[i]))
		i++;
	line = (char *)ft_skipspace(line + i);
	if (!ft_isdigit(*line))
		return (0);
	file->res.y = ft_atoi(line);
	return (1);
}

int	parse_colour(t_colour *colour, char *line)
{
	char  **str;
	if (file)
		return (1);
	if (line)
		return (1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 09:06:44 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/21 19:15:23 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	gnl_loop(int fd, int i, t_map *map)
{
	char	*temp;

	temp = get_next_line(fd, 0);
	if (temp == NULL)
	{
		get_next_line(fd, 1);
		return (1);
	}
	map->input[i] = ft_split(temp, ' ');
	if (map->input[i] == NULL)
	{
		free (temp);
		get_next_line(fd, 1);
		return (2);
	}
	free (temp);
	return (0);
}

static int	actual_read(char *mapname, char **input, t_map *map)
{
	int		i;
	int		fd;

	count_rows(*input, map);
	fd = open(mapname, O_RDONLY);
	if (fd == -1)
		return (1);
	map->input = ft_calloc(map->rows + 1, sizeof(char *));
	if (map->input == NULL)
		return (11 + close(fd));
	i = -1;
	while (++i < map->rows)
	{
		if (gnl_loop(fd, i, map))
			return (12 + close(fd));
	}
	if (close(fd) == -1)
		return (4);
	get_next_line(fd, 1);
	return (0);
}

static int	read_loop(int fd, int *ret, char **input)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_calloc(100000, sizeof(char));
	if (temp1 == NULL)
		return (3);
	*ret = read(fd, temp1, 99999);
	if (*ret == -1)
	{
		free (temp1);
		return (4);
	}
	temp2 = *input;
	*input = ft_strjoin(*input, temp1);
	free (temp1);
	free (temp2);
	if (*input == NULL || *input[0] == 0)
		return (5);
	return (0);
}

static int	first_read(char *mapname, char **output)
{
	int		fd;
	int		ret;
	char	*input;

	fd = open(mapname, O_RDONLY);
	if (fd == -1)
		return (1);
	ret = 1;
	input = ft_calloc(1, sizeof(char));
	if (input == NULL)
		return (11 + close(fd));
	while (ret != 0)
	{
		if (read_loop(fd, &ret, &input))
		{
			free (input);
			return (12 + close(fd));
		}
	}
	*output = input;
	if (close(fd) == -1)
		return (5);
	return (0);
}

int	handle_input(char *mapname, t_map *map)
{
	char	*input;

	if (first_read(mapname, &input))
		return (1);
	if (actual_read(mapname, &input, map))
	{
		free (input);
		return (2);
	}
	free (input);
	if (count_columns(map))
		return (3);
	if (map_to_coord(map))
		return (4);
	if (coord_to_iso(map))
		return (5);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:44:29 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/23 13:21:50 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	coord_to_iso(t_map *map)
{
	int	previous_x;
	int	previous_y;
	int	count;
	int	i;

	map->fdf = ft_calloc((map->rows * map->columns + 1), sizeof(t_fdf *));
	if (map->fdf == NULL)
		return (1);
	i = -1;
	count = 0;
	while (++i < (map->rows * map->columns))
	{
		previous_x = map->coords[count]->x;
		previous_y = map->coords[count]->y;
		map->fdf[count] = malloc(sizeof(t_fdf));
		if (map->fdf[count] == NULL)
			return (2);
		map->fdf[count]->u = (previous_x - previous_y) * cos(0.523599);
		map->fdf[count]->v = -map->coords[count]->z
			+ (previous_x + previous_y) * sin(0.523599);
		map->fdf[count]->color = map->coords[count]->color;
		count++;
	}
	return (0);
}

static int	ft_get_color(char *input)
{
	int	color;

	color = 0;
	while (*input)
	{
		if (input[0] == '-')
			input++;
		if (ft_isdigit(*input))
			input++;
		if (*input == ',')
		{
			input++;
			color = str_to_hex(input);
			break ;
		}
		if (*input == '\n')
			break ;
	}
	return (color);
}

static int	fill_coord(t_map *map, int i, int j, int count)
{
	map->coords[count] = malloc(sizeof(t_coords));
	if (map->coords[count] == NULL)
		return (1);
	map->coords[count]->x = j - (map->columns / 2);
	map->coords[count]->y = i - (map->rows / 2);
	if (ft_atoi_long(map->input[i][j]) < -2147483648
		|| ft_atoi_long(map->input[i][j]) > 2147483647)
		return (2);
	else
		map->coords[count]->z = ft_atoi_long(map->input[i][j]);
	map->coords[count]->color = ft_get_color(map->input[i][j]);
	if (map->coords[count]->color == 0)
		map->coords[count]->color = ORANGE;
	return (0);
}

int	map_to_coord(t_map *map)
{
	int	i;
	int	j;
	int	count;

	map->coords = ft_calloc((map->rows * map->columns + 1), sizeof(t_coords *));
	if (map->coords == NULL)
		return (1);
	i = -1;
	count = 0;
	while (map->input[++i])
	{
		j = -1;
		while (map->input[i][++j] && ft_strncmp(map->input[i][j], "\n", 1))
		{
			if (fill_coord(map, i, j, count++))
				return (2);
		}
	}
	return (0);
}

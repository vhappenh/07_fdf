/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:08:55 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/26 14:57:04 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_stepvalue(int p1, int p2)
{
	int	s;

	if (p1 < p2)
		s = 1;
	else
		s = -1;
	return (s);
}

int	str_to_hex(char *input)
{
	int	i;
	int	nb;

	i = -1;
	nb = 0;
	while (input[++i])
	{
		if ((input[0] == '0' && input[1] == 'x') && i == 0)
			input = input + 2;
		if (input[i] >= '0' && input[i] <= '9')
			nb = nb * 16 + input[i] - '0';
		else if (input[i] <= 'F' && input[i] >= 'A')
			nb = nb * 16 + input[i] - 55;
		else if (input[i] <= 'f' && input[i] >= 'a')
			nb = nb * 16 + input[i] - 87;
		else if (input[i] <= '\n')
			return (nb);
		else
			return (0);
	}
	return (nb);
}

int	scale_fdf(t_data *data)
{
	int	i;
	int	x;

	x = 0;
	while (++x)
	{
		i = -1;
		while (data->map->fdf[++i])
		{
			if (((data->map->fdf[i]->u * (x + 1) + data->oset_w) < 0)
				|| ((data->map->fdf[i]->u * (x + 1)
						+ data->oset_w) > data->width))
				return (x);
			if (((data->map->fdf[i]->v * (x + 1) + data->oset_h) < 0)
				|| ((data->map->fdf[i]->v * (x + 1)
						+ data->oset_h) > data->height))
				return (x);
		}
	}
	return (x);
}

void	count_rows(char *input, t_map *map)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\n')
			map->rows++;
	}
	if (input[i] == '\0' && input[i - 1] != '\n')
		map->rows++;
}

int	count_columns(t_map *map)
{
	int	i;
	int	j;
	int	check;

	i = -1;
	while (map->input[++i])
	{
		j = -1;
		check = 0;
		while (map->input[i][++j] && ft_strncmp(map->input[i][j], "\n", 1))
			check++;
		if (map->columns == 0)
			map->columns = check;
		if (map->columns != check)
			return (1);
	}
	return (0);
}

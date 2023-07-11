/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 15:34:42 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/08 20:47:06 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	copy_base_fdf(t_data *data, t_map *map)
{
	int	i;

	i = -1;
	data->defmap = ft_calloc((map->rows * map->columns + 1), sizeof(t_fdf *));
	if (data->defmap == NULL)
		return (1);
	i = -1;
	while (++i < (map->rows * map->columns))
	{
		data->defmap[i] = malloc(sizeof(t_fdf));
		if (data->defmap[i] == NULL)
			return (2);
		data->defmap[i]->u = map->fdf[i]->u;
		data->defmap[i]->v = map->fdf[i]->v;
		data->defmap[i]->color = map->fdf[i]->color;
	}
	return (0);
}

int	check_dot_fdf(char *filename)
{
	while (*filename)
		filename++;
	filename = filename - 4;
	if (ft_strncmp(filename, ".fdf", 4))
		return (1);
	return (0);
}

long	ft_atoi_long(const char *nptr)
{
	long			sum;
	int				i;
	int				sign;

	i = 0;
	sum = 0;
	sign = 1;
	while ((nptr[i] <= 13 && nptr[i] > 8) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		sum = sum * 10 + nptr[i] - '0';
		i++;
	}
	return (sum * sign);
}

void	fill_bresen(t_data *data, t_bresen *b, int p1, int p2)
{
	b->u0 = data->map->fdf[p1]->u * data->x;
	b->u1 = data->map->fdf[p2]->u * data->x;
	b->v0 = data->map->fdf[p1]->v * data->x;
	b->v1 = data->map->fdf[p2]->v * data->x;
	b->du = abs(b->u1 - b->u0);
	b->dv = abs(b->v1 - b->v0);
	b->su = get_stepvalue(b->u0, b->u1);
	b->sv = get_stepvalue(b->v0, b->v1);
	b->err = b->du - b->dv;
}

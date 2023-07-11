/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:32:35 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/14 15:47:54 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_input(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	if (map->input)
	{
		while (map->input[++i])
		{
			j = -1;
			while (map->input[i][++j])
				free (map->input[i][j]);
			free (map->input[i]);
		}
		free(map->input);
	}
}

static void	free_coords(t_map *map)
{
	int	i;

	i = -1;
	if (map->coords)
	{
		while (map->coords[++i])
		{
			free (map->coords[i]);
		}
		free (map->coords);
	}
}

static void	free_fdf(t_map *map)
{
	int	i;

	i = -1;
	if (map->fdf)
	{
		while (map->fdf[++i])
			free (map->fdf[i]);
		free (map->fdf);
	}
}

static void	free_defmap(t_data *data)
{
	int	i;

	i = -1;
	if (data->defmap)
	{
		while (data->defmap[++i])
			free (data->defmap[i]);
		free (data->defmap);
	}
}

int	ft_free(t_map *map, t_data *data)
{
	free_input(map);
	free_coords(map);
	free_fdf(map);
	free_defmap(data);
	return (0);
}

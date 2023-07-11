/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:21:16 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/09 14:28:03 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_fdf(t_data *data)
{
	int	i;

	i = -1;
	while (data->map->fdf[++i])
	{
		data->map->fdf[i]->u = data->defmap[i]->u;
		data->map->fdf[i]->v = data->defmap[i]->v;
	}
	data->x = data->max_x;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:45:30 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/09 14:43:35 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_colors(int keysym, t_data *data, int i)
{
	if (keysym == 49)
	{
		data->b_color = PINK;
		while (data->map->fdf[++i])
			if (data->map->fdf[i]->color == THISTLE
				|| data->map->fdf[i]->color == VIOLET)
				data->map->fdf[i]->color = ORANGE;
	}
	else if (keysym == 50)
	{
		data->b_color = GREEN;
		while (data->map->fdf[++i])
			if (data->map->fdf[i]->color == ORANGE
				|| data->map->fdf[i]->color == THISTLE)
				data->map->fdf[i]->color = VIOLET;
	}
	else if (keysym == 51)
	{
		data->b_color = IVORY;
		while (data->map->fdf[++i])
			if (data->map->fdf[i]->color == ORANGE
				|| data->map->fdf[i]->color == VIOLET)
				data->map->fdf[i]->color = THISTLE;
	}
}

static void	handle_movement(int keysym, t_data *data)
{
	int	i;

	i = -1;
	if (keysym == 65361 || keysym == 97)
	{
		while (data->map->fdf[++i])
			data->map->fdf[i]->u--;
	}
	else if (keysym == 65362 || keysym == 119)
	{
		while (data->map->fdf[++i])
			data->map->fdf[i]->v--;
	}
	else if (keysym == 65363 || keysym == 100)
	{
		while (data->map->fdf[++i])
			data->map->fdf[i]->u++;
	}
	else if (keysym == 65364 || keysym == 115)
	{
		while (data->map->fdf[++i])
			data->map->fdf[i]->v++;
	}
}

static void	handle_perspective(int keysym, t_data *data)
{
	int	i;

	i = -1;
	if (keysym == 113)
	{
		while (data->map->fdf[++i])
		{
			data->map->fdf[i]->u = data->map->fdf[i]->u
				/ cos(0.523599) * cos(0.46373398);
			data->map->fdf[i]->v = data->map->fdf[i]->v
				/ sin(0.523599) * sin(0.46373398);
		}
	}
	else
	{
		while (data->map->fdf[++i])
		{
			data->map->fdf[i]->u = data->map->fdf[i]->u
				/ cos(0.46373398) * cos(0.523599);
			data->map->fdf[i]->v = data->map->fdf[i]->v
				/ sin(0.46373398) * sin(0.523599);
		}
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		handle_window_x(data);
	else if (keysym == 65451 || keysym == 93)
		data->x++;
	else if (keysym == 65453 || keysym == 47)
		data->x--;
	else if (keysym == 49 || keysym == 50 || keysym == 51)
		handle_colors(keysym, data, -1);
	else if (keysym == 65361 || keysym == 65362
		|| keysym == 65363 || keysym == 65364
		|| keysym == 119 || keysym == 97
		|| keysym == 115 || keysym == 100)
		handle_movement(keysym, data);
	else if (keysym == 113 || keysym == 101)
		handle_perspective(keysym, data);
	else if (keysym == 114)
		reset_fdf(data);
	return (0);
}

int	handle_window_x(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	ft_free(data->map, data);
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:52:53 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/26 14:57:25 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_background(t_data data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data.height)
	{
		j = 0;
		while (j < data.width)
			img_pix_put(&data.img, j++, i, color);
		++i;
	}
}

static void	bresenham(t_data *data, int p1, int p2)
{
	t_bresen	b;

	fill_bresen(data, &b, p1, p2);
	while (b.u0 != b.u1 || b.v0 != b.v1)
	{
		if (((b.u0 + data->oset_w) <= data->width && (b.u0 + data->oset_w) >= 0)
			&& ((b.v0 + data->oset_h) <= data->height
				&& (b.v0 + data->oset_h) >= 0))
			img_pix_put(&data->img, b.u0 + data->oset_w, b.v0
				+ data->oset_h, data->map->fdf[p1]->color);
		b.e2 = 2 * b.err;
		if (b.e2 > -b.dv)
			b.err -= b.dv;
		if (b.e2 > -b.dv)
			b.u0 += b.su;
		if (b.e2 < b.du)
			b.err += b.du;
		if (b.e2 < b.du)
			b.v0 += b.sv;
	}
	if (((b.u0 + data->oset_w) <= data->width && (b.u0 + data->oset_w) >= 0)
		&& ((b.v0 + data->oset_h) <= data->height
			&& (b.v0 + data->oset_h) >= 0))
		img_pix_put(&data->img, b.u0 + data->oset_w, b.v0
			+ data->oset_h, data->map->fdf[p1]->color);
}

static void	render_line(t_data *data)
{
	int	i;
	int	check_u;
	int	check_v;

	i = -1;
	check_u = 1;
	check_v = 1;
	while (data->map->fdf[++i])
	{
		if (check_u < data->map->columns)
			bresenham(data, i, (i + 1));
		check_u++;
		if (check_v < data->map->rows)
			bresenham(data, i, (i + data->map->columns));
		if (check_u == (data->map->columns + 1))
		{
			check_u = 1;
			check_v++;
		}
	}
}

void	render_fdf(t_data *data)
{
	int	i;

	i = -1;
	if (data->x == 0)
	{
		data->x = scale_fdf(data);
		if (data->max_x == 0)
			data->max_x = data->x;
	}
	render_line(data);
}

void	render_menu(t_data *data)
{
	if (data->b_color == PINK)
		data->menu_color = ORANGE;
	else if (data->b_color == GREEN)
		data->menu_color = VIOLET;
	else if (data->b_color == IVORY)
		data->menu_color = THISTLE;
	mlx_string_put(data->mlx_ptr, data->win_ptr, 2,
		10, data->menu_color, "zoom ............... +-");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 2,
		25, data->menu_color, "move ............. WASD");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 2,
		40, data->menu_color, "fold ............... QE");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 2,
		55, data->menu_color, "color ............. 123");
	mlx_string_put(data->mlx_ptr, data->win_ptr, 2,
		70, data->menu_color, "reset ............... R");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_prep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 08:56:05 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/23 14:08:03 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

static int	render(t_data *data)
{
	data->oset_w = data->width / 2;
	data->oset_h = data->height / 2;
	render_background(*data, data->b_color);
	render_fdf(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.mlx_img, 0, 0);
	render_menu(data);
	return (0);
}

static void	ft_hooker(t_data *data)
{
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, (17), (1L << 17), &handle_window_x, data);
}

int	window_management(t_map *map, t_data *data, char *mapname)
{
	data->map = map;
	data->b_color = PINK;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	mlx_get_screen_size(data->mlx_ptr, &data->width, &data->height);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img,
			&data->img.bpp, &data->img.line_len, &data->img.endian);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->width, data->height, mapname);
	if (data->win_ptr == NULL)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (2);
	}
	mlx_loop_hook(data->mlx_ptr, &render, data);
	ft_hooker(data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

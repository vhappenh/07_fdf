/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:59:24 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/22 13:27:30 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# include "./minilibx-linux/mlx.h"
# include "./libft_ultra/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# define ORANGE 0xEE7600
# define PINK 0xFFC0CB
# define GREEN 0x3CB371
# define VIOLET 0xFF3E96
# define IVORY 0xEEEEE0
# define THISTLE 0xD8BFD8
# define FDF_H

typedef struct s_bresen
{
	int	u0;
	int	u1;
	int	v0;
	int	v1;
	int	du;
	int	dv;
	int	su;
	int	sv;
	int	err;
	int	e2;
}	t_bresen;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_coords
{
	int		x;
	int		y;
	int		z;
	int		color;
}	t_coords;

typedef struct s_fdf
{
	float	u;
	float	v;
	int		color;
}	t_fdf;	

typedef struct s_map
{
	char		***input;
	int			columns;
	int			rows;
	t_coords	**coords;
	t_fdf		**fdf;
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		oset_w;
	int		height;
	int		oset_h;
	int		x;
	int		max_x;
	int		b_color;
	int		menu_color;
	t_fdf	**defmap;
	t_map	*map;
	t_img	img;
}	t_data;

/* main */
int		check_dot_fdf(char *filename);
int		handle_input(char *mapname, t_map *map);
int		ft_free(t_map *map, t_data *data);
int		copy_base_fdf(t_data *data, t_map *map);
int		window_management(t_map *map, t_data *data, char *mapname);

/* handle input */
void	count_rows(char *input, t_map *map);
int		count_columns(t_map *map);
int		map_to_coord(t_map *map);
long	ft_atoi_long(const char *nptr);
int		str_to_hex(char *input);
int		coord_to_iso(t_map *map);

/* window stuff */
void	render_background(t_data data, int color);
void	render_fdf(t_data *data);
int		scale_fdf(t_data *data);
void	fill_bresen(t_data *data, t_bresen *b, int p1, int p2);
int		get_stepvalue(int p1, int p2);
void	render_menu(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);

/* events */
int		handle_keypress(int keysym, t_data *data);
int		handle_window_x(t_data *data);
void	reset_fdf(t_data *data);

#endif

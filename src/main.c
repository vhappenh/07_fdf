/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:52:29 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/22 13:29:41 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	static t_data	data;
	static t_map	map;

	if (argc != 2)
		return (1);
	if (check_dot_fdf(argv[1]))
		return (2);
	if (handle_input(argv[1], &map))
		return (3 + ft_free(&map, &data));
	if (copy_base_fdf(&data, &map))
		return (4 + ft_free(&map, &data));
	if (window_management(&map, &data, argv[1]))
		return (5 + ft_free(&map, &data));
	return (0);
}

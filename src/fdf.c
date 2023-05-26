/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:37:53 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/08 19:19:29 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	map_x(t_data *d)
{
	static int	curr_pos_x = 0;
	static int	curr_pos_y = 0;
	
	if (curr_pos_x == d->map->cols - 1)
	{
		if (curr_pos_y == d->map->rows - 1)
		{
			curr_pos_y = 0;
			curr_pos_x = 0;
			return (0);
		}
		curr_pos_x = 0;
		curr_pos_y++;
	}
	d->point0.x = d->x_offset + d->grid_width * curr_pos_x;
	d->point0.y = d->y_offset + d->grid_width * curr_pos_y;
	d->point0.z = (d->map->map[curr_pos_y][curr_pos_x] * d->grid_width / d->initial_gr_wd);
	d->point1.x = d->x_offset + d->grid_width * (curr_pos_x + 1);
	d->point1.y = d->y_offset + d->grid_width * curr_pos_y;
	d->point1.z = (d->map->map[curr_pos_y][curr_pos_x + 1] * d->grid_width / d->initial_gr_wd);
	curr_pos_x++;
	rotate(&d->point0, d->angle);
	rotate(&d->point1, d->angle);
	return (1);
}

int	map_y(t_data *d)
{
	static int	curr_pos_x = 0;
	static int	curr_pos_y = 0;
	
	if (curr_pos_y == d->map->rows - 1)
	{
		if (curr_pos_x == d->map->cols - 1)
		{
			curr_pos_x = 0;
			curr_pos_y = 0;
			return (0);
		}
		curr_pos_y = 0;
		curr_pos_x++;
	}
	d->point0.y = d->y_offset + d->grid_width * curr_pos_y;
	d->point0.x = d->x_offset + d->grid_width * curr_pos_x;
	d->point0.z = (d->map->map[curr_pos_y][curr_pos_x] * d->grid_width / d->initial_gr_wd);
	d->point1.y = d->y_offset + d->grid_width * (curr_pos_y + 1);
	d->point1.x = d->x_offset + d->grid_width * curr_pos_x;
	d->point1.z = (d->map->map[curr_pos_y + 1][curr_pos_x] * d->grid_width / d->initial_gr_wd);
	curr_pos_y++;
	rotate(&d->point0, d->angle);
	rotate(&d->point1, d->angle);
	return (1);
}

int	key_down_hook(int key, t_data *d)
{
	if (key == 53)
		error(d);
	return (1);
}

int	destroy(t_data *d)
{
	error(d);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (argc == 1)
		return (0);
	init(&d, argv[1]);
	while (map_y(&d))
		connect_points(&d);
	while (map_x(&d))
		connect_points(&d);
		
	mlx_put_image_to_window(d.mlx.mlx, d.mlx.window, d.mlx.img.img, 0, 0);
	mlx_hook(d.mlx.window, 2, 1L<<0, key_down_hook, &d);
	mlx_hook(d.mlx.window, 17, 1L<<0, destroy, &d);
	mlx_loop(d.mlx.mlx);
	return (0);
}
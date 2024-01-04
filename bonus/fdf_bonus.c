/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:37:53 by jofoto            #+#    #+#             */
/*   Updated: 2023/10/28 20:13:50 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"
#include <sys/types.h>

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
	d->point0.z = d->z_multipliar * (d->map->map[curr_pos_y][curr_pos_x] * d->grid_width / d->initial_gr_wd);
	d->point1.x = d->x_offset + d->grid_width * (curr_pos_x + 1);
	d->point1.y = d->y_offset + d->grid_width * curr_pos_y;
	d->point1.z = d->z_multipliar * (d->map->map[curr_pos_y][curr_pos_x + 1] * d->grid_width / d->initial_gr_wd);
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
	d->point0.z = d->z_multipliar * (d->map->map[curr_pos_y][curr_pos_x] * d->grid_width / d->initial_gr_wd);
	d->point1.y = d->y_offset + d->grid_width * (curr_pos_y + 1);
	d->point1.x = d->x_offset + d->grid_width * curr_pos_x;
	d->point1.z = d->z_multipliar *( d->map->map[curr_pos_y + 1][curr_pos_x] * d->grid_width / d->initial_gr_wd);
	curr_pos_y++;
	rotate(&d->point0, d->angle);
	rotate(&d->point1, d->angle);
	return (1);
}

void	key_down_hook(void *ptr)
{
    t_data *d = ptr;

	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
        error(d);
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
        d->angle.y -= 3;
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
        d->angle.y += 3;
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
        d->angle.x += 3;
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
        d->angle.x -= 3;
	if (mlx_is_key_down(d->mlx, MLX_KEY_Q))
        d->angle.z -= 3;
	if (mlx_is_key_down(d->mlx, MLX_KEY_E))
        d->angle.z += 3;
	if (mlx_is_key_down(d->mlx, MLX_KEY_EQUAL))
        d->z_multipliar++;
	if (mlx_is_key_down(d->mlx, MLX_KEY_MINUS))
        d->z_multipliar--;
	/*else if (key == 123 || key == 124 || key == 125 || key == 126)
	{
		d->angle.x_rotation_axis -= 12.0/WINDOW_HEIGHT * (float)(key == 124);
		d->angle.x_rotation_axis += 12.0/WINDOW_HEIGHT * (float)(key == 123);
		d->angle.y_rotation_axis -= 24.0/WINDOW_WIDTH * (float)(key == 125);
		d->angle.y_rotation_axis += 24.0/WINDOW_WIDTH * (float)(key == 126);
	}
	else if (key == 78 || key == 69)
	{
		d->z_multipliar += (key == 69);
		d->z_multipliar -= (key == 78);
	}*/
}

void	scroll_hook(double xdelta, double ydelta, void *ptr)
{
	t_data *d = ptr;
    (void)xdelta;

		d->grid_width += ydelta * 2;
		d->x_offset -=  ydelta * d->map->cols;
		d->y_offset -= ydelta * d->map->rows;
}

void	render_next_frame(void *ptr)
{	
    t_data *d = ptr;

	ft_bzero(d->img->pixels, WINDOW_HEIGHT * WINDOW_WIDTH * sizeof(int));
	while (map_y(d))
		connect_points(d);
	while (map_x(d))
		connect_points(d);
	//mlx_put_image_to_window(d->mlx.mlx, d->mlx.window, d->mlx.img.img, 0, 0);
}

void	destroy(void *d)
{
	error((t_data*)d);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (argc == 1)
		return (0);
	init(&d, argv[1]);
    mlx_loop_hook(d.mlx, key_down_hook, &d);
    mlx_scroll_hook(d.mlx, scroll_hook, &d);
    mlx_close_hook(d.mlx, destroy, &d);
	mlx_loop_hook(d.mlx, render_next_frame, &d);
	mlx_loop(d.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:18:43 by jofoto            #+#    #+#             */
/*   Updated: 2023/10/28 20:15:12 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	get_vars(t_point point0, t_point point1,t_conn_pnts_vars *vars)
{
	vars->up = 1;
	vars->left = 1;
	if (point0.y > point1.y)
		vars->up = -1;
	if (point0.x > point1.x)
		vars->left = -1;
	vars->move_ratio = (float)(point0.y - point1.y) / (float)(point0.x - point1.x);
	vars->move_ratio = fabsf(vars->move_ratio);
	vars->curr_step = vars->move_ratio;
	
	vars->total_steps = abs(point0.x - point1.x) + abs(point0.y - point1.y);
}

void	init_mlx(t_data *d)
{
    if(!(d->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Model", false)))
    {
        int i = write(2, "MLX init error\n", 15);
        i++;
        exit(1); // handle error
    }
    if(!(d->img = mlx_new_image(d->mlx, WINDOW_WIDTH, WINDOW_HEIGHT)))
    {
        int i = write(2, "MLX image init error\n", 21);
        i++;
        exit(1); // handle error
    }
    if(mlx_image_to_window(d->mlx, d->img, 0, 0) == -1)
    {
        int i = write(2, "MLX image to window init error\n", 31);
        i++;
        exit(1); // handle error
    }
}

void	init_map(t_data	*d, char *fpath)
{
	d->map = (s_vector *)malloc(sizeof(s_vector)); //leaking
	if(d->map == NULL)
		exit(1);
	d->map->map = (int **)malloc(sizeof(int *) * 5);
	if (d->map->map == NULL)
	{
		free(d->map);
		exit(1);
	}
	d->map->rows = 0;
	d->map->cols = 0;
	d->map->highest_z = -2147483648;
	d->map->lowest_z = 2147483647;
	d->map->rows_cap = 5;
	
	if (get_map(d, fpath) == 0)
		return ;
}

void	init_coords(t_data *d)
{
	d->angle.x = 0;
	d->angle.y = 0;
	d->angle.z = 0;
	d->angle.x_rotation_axis = 2;
	d->angle.y_rotation_axis = 2;
	
	if(d->map->cols > d->map->rows)
		d->grid_width = WINDOW_HEIGHT / d->map->cols;
	else
		d->grid_width = WINDOW_HEIGHT / d->map->rows;
	
	d->initial_gr_wd = d->grid_width;
	d->x_offset = -((d->map->cols-1) * d->grid_width / 2);
 	d->y_offset = -((d->map->rows-1) * d->grid_width / 2);
	d->initial_x_ofs = d->x_offset;
	d->initial_y_ofs = d->y_offset;
	d->z_multipliar = 1;
}

void    init(t_data	*d, char *fpath)
{
	init_map(d, fpath);
	init_coords(d);
	init_mlx(d);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:31:28 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/08 20:00:13 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	my_mlx_pixel_put(int x, int y, int color, t_data *d)
{
	char	*dst;

	x += WINDOW_WIDTH / d->angle.x_rotation_axis;
	y += WINDOW_HEIGHT / d->angle.y_rotation_axis;
	//printf("%f\n", d->angle.x_rotation_axis);
    if (x < WINDOW_WIDTH && y < WINDOW_HEIGHT * 0.95 && x >= 0 && y >= 0)
    {
	    dst = d->mlx.img.addr + (y * d->mlx.img.line_length + x * (d->mlx.img.bits_per_pixel / 8));
	    *(unsigned int*)dst = color;
    }
}

void	my_mlx_pixel_put2(t_img_data *img, int x, int y, int color)
{
	char	*dst;

    if (x < WINDOW_WIDTH && y < WINDOW_HEIGHT && x >= 0 && y >= 0)
    {
	    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	    *(unsigned int*)dst = color;
    }
}

/* int		pick_color(t_point point0)
{
 //printf("z: %i\n", z);
	int lowest = pick_color(*d); // 16777215
	int	highest	= 0xff0000; // 16711680
	//int l = 0;

	if (z == 0)
		return (lowest);
	int h = 30;
	int ret;
	//lowest + (lowest - hghest) * h / z
	ret = lowest + (highest - lowest) * z / h;
	//printf("%#x\n", ret);
	return (ret);

	int lowest = pick_color(*d);
	int	highest	= 0xff0000;
	int z;
	z = sin(angle) * point0.x  - cos(angle) * z;
	
	
} */

/* void    rev_rotate_x(int *yy, int *zz, float angle)
{
    int y;
    int z;
    
    z = *zz;
    y = *yy;
    
    *yy = y * cos(angle) + z * sin(angle);
    *zz = y * (-sin(angle)) + z * cos(angle);
}

void    rev_rotate_y(int *xx, int *zz, float angle)
{
    int x;
    int z;
    
    z = *zz;
    x = *xx;
    
    *xx = x * cos(angle) - z * sin(angle);
    *zz = x * sin(angle) + z * cos(angle);
}

void    rev_rotate_z(int *yy, int *xx, float angle)
{
    int x;
    int y;
    y = *yy;
    x = *xx;
    
    *xx = x * cos(angle) + y * sin(angle);
    *yy = -x * sin(angle) + y * cos(angle);
}

void    rev_rotate(int *x, int *y, int *z, t_data d)
{
    rev_rotate_z(y, x, d.angle.z);
    rev_rotate_y(x, z, d.angle.y);
    rev_rotate_x(y, z, d.angle.x);
}

int	pick_color(t_conn_pnts_vars vars, t_data d, int restart, int lowest, int highest)
{
	static int high;
	static int	low;
	int	ret;
	static int curr_steps;

	if (restart == 1)
	{
		rev_rotate(&d.point0.x, &d.point0.y, &d.point0.z, d);
		rev_rotate(&d.point1.x, &d.point1.y, &d.point1.z, d);
		low = lowest + (highest - lowest) * d.point0.z/d.map->highest_z;
		high = lowest + (highest - lowest) * d.point1.z/d.map->highest_z;
		curr_steps = 0;
	}
	ret = low + (high - low) * (float)curr_steps/vars.total_steps;         //(d.point1.z - d.map->lowest_z) / d.map->highest_z;
	curr_steps++;
	//printf("%x\n", ret); 
	return (ret);
} */

// pick color by first reversing the points and then !doing some cacls between z and x or y!
//get 
void	connect_points(t_data *d)
{
    t_conn_pnts_vars vars;

	get_vars(d->point0, d->point1, &vars);
	if (d->point0.x == d->point1.x)
	{
		while(d->point0.y != d->point1.y)
		{
			my_mlx_pixel_put(d->point0.x, d->point0.y, 0xffffff, d);
			d->point0.y += vars.up;
		}
		return ;
	}
	while(d->point0.x != d->point1.x)
	{
		while(vars.curr_step >= 1)
		{
			my_mlx_pixel_put(d->point0.x, d->point0.y, 0xffffff, d);
			vars.curr_step--;
			d->point0.y += vars.up;
		}
		my_mlx_pixel_put(d->point0.x, d->point0.y, 0xffffff, d);
		vars.curr_step += vars.move_ratio;
		d->point0.x += vars.left;
	}
}

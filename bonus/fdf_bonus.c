/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 15:37:53 by jofoto            #+#    #+#             */
/*   Updated: 2023/05/20 20:25:27 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/*void	print_map(s_vector *map)
{
	int i = 0;
	int j = 0;
	
	printf("rows: %i\n", map->rows);
	printf("rows_cap: %i\n", map->rows_cap);
	printf("cols: %i\n", map->cols);
	
	while(j < map->rows)
	{
		while (i < map->cols)
		{
			printf("%i ", map->map[j][i]);
			i++;
		}
		printf("\n");
		i = 0;
		j++;
	}
} */

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

int	key_down_hook(int key, t_data *d)
{
	if (key == 53)
		error(d);
	if (key == 0 || key == 2 || key == 1 || key == 13 || key == 12 || key == 14)
	{
		d->angle.x += 3 * (key == 13);
		d->angle.x -= 3 * (key == 1);
		d->angle.y += 3 * (key == 2);
		d->angle.y -= 3 * (key == 0);
		d->angle.z += 3 * (key == 14);
		d->angle.z -= 3 * (key == 12);
	}
	else if (key == 123 || key == 124 || key == 125 || key == 126)
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
	}
	return (1);
}

int	mouse_hook(int key, int x, int y, t_data *d)
{
	(void)x;
	(void)y;
	if (key == 4 || (key == 5 && d->grid_width > 0))
	{
		d->grid_width += (key == 4) * 2;
		d->x_offset -=  (key == 4) * d->map->cols;
		d->y_offset -= (key == 4) * d->map->rows;
		d->grid_width -= (key == 5) * 2;
		d->x_offset +=  (key == 5) * d->map->cols;
		d->y_offset += (key == 5) * d->map->rows;
	}
	return (1);
}

int	render_next_frame(t_data *d)
{	
	ft_bzero(d->mlx.img.addr, WINDOW_HEIGHT * (d->mlx.img.line_length * 0.95) + WINDOW_WIDTH * d->mlx.img.bits_per_pixel);
	//blah(d->mlx.img, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	while (map_y(d))
		connect_points(d);
	while (map_x(d))
		connect_points(d);
	mlx_put_image_to_window(d->mlx.mlx, d->mlx.window, d->mlx.img.img, 0, 0);
	return (1);
}

int	destroy(t_data *d)
{
	error(d);
	exit(0);
}

/* int	validate_thread_input(char *line)
{
	int	i;
	int	spaces;

	i = 0;
	spaces = 0;
	while(line[i] != '\n')
	{
		if (line[i] == ' ')
			spaces++;
		else if(ft_isdigit(line[i]) == 0)
				return (0);
		i++;
	}
	if(spaces > 2)
		return (0);
	return (1);
}

void	*routine(void *data)
{
	t_data	*d;
	char	*line;
	int		i;
	
	d = (t_data *)data;
	while(1)
	{
		line = get_next_line(0);
		if (!validate_thread_input(line))
		{
			write(1, "Wrong Input!\n", 14);
			write(1, "Try giving an angle for x, y and z, respectively, seperated by a space.\n", 72);
			write(1, "e.g: 45 -45 30\n", 15);
			free(line);
			continue ;
		}
		d->angle.x = ft_atoi(line);
		d->angle.y = ft_atoi(ft_strchr(line, ' ') + 1);
		d->angle.z = ft_atoi(ft_strrchr(line, ' ') + 1);
		free(line);
	}
} */

/*when you get map check if ret == 0 then exit*/
int	main(int argc, char **argv)
{
	t_data	d;
	//pthread_t thread;

	if (argc == 1)
		return (0);
	init(&d, argv[1]);
	//pthread_create(&thread, NULL, routine, &d);
	mlx_hook(d.mlx.window, 2, 1L<<0, key_down_hook, &d);
	mlx_hook(d.mlx.window, 17, 1L<<0, destroy, &d);
	mlx_mouse_hook(d.mlx.window, mouse_hook, &d);
	mlx_loop_hook(d.mlx.mlx, render_next_frame, &d);
	mlx_loop(d.mlx.mlx);
	return (0);
}

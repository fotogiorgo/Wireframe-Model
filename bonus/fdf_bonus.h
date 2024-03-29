/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <jofoto@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:17:58 by jofoto            #+#    #+#             */
/*   Updated: 2023/10/28 20:15:50 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <libft.h>
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define RADIANT_CONV 0.01745329251

typedef struct	s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
}				t_point;

typedef struct s_con_pnt_vars
{
	float   move_ratio;
    float   curr_step;
    int     up;
	int		left;
	int		total_steps;
}				t_conn_pnts_vars;

typedef	struct s_angles
{
	int		x;
	int		y;
	int		z;
	float	x_rotation_axis;
	float	y_rotation_axis;
}				t_angles;


typedef	struct s_vector
{
	int	**map;
	int	rows;
	int	cols;
	int	lowest_z;
	int	highest_z;
	int	rows_cap;
}				s_vector;

typedef	struct s_mlx_data
{
	t_img_data	img;
	void		*mlx;
	void		*window;
}				t_mlx_data;

typedef	struct s_data
{
    mlx_t       *mlx;	
	mlx_image_t	*img;
	t_point		point0;
	t_point		point1;
	t_angles	angle;
	s_vector	*map;
	int			z_multipliar;
	int			grid_width;
	int			initial_gr_wd;
	int 		x_offset;
	int 		y_offset;
	int			initial_x_ofs;
	int			initial_y_ofs;
}				t_data;


void	init(t_data	*data, char *fpath);
void	get_vars(t_point point0, t_point point1,t_conn_pnts_vars *vars);
int		get_map(t_data *data, char *fpath);
void	rotate(t_point	*coords, t_angles	angle);
void	connect_points(t_data *d);
void	blah(t_img_data img, int x, int y);
void	error(t_data *d);
void	free_map(int **map, int rows);
void	free_split(char **split);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 09:35:01 by abquaoub          #+#    #+#             */
/*   Updated: 2024/07/17 20:22:53 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	check_wall(t_data *data, int x, int y)
{
	char	**map;

	map = data->mm.map;
	int i, j;
	j = x / data->size;
	i = y / data->size;
	if (i < 0 || j < 0 || i > 6 || j > 15 || map[i][j] != '0')
		return (1);
	return (0);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw(t_data *data, int i, int j, int color)
{
	int	x;
	int	y;
	int	co;

	co = 0;
	x = 0;
	y = 0;
	while (x < data->size)
	{
		y = 0;
		while (y < data->size)
		{
			co = color;
			if (!y || !x || y + 1 == data->size || x + 1 == data->size)
				co = 11;
			my_mlx_pixel_put(&data->img, x + i, j + y, co);
			y++;
		}
		x++;
	}
}

void	dda_alg(t_data *data, double x, double y, double x0, double y0)
{
	int		res;
	double	yi;
	double	xi;

	double a, b;
	int dx, dy;
	dx = x0 - x;
	dy = y0 - y;
	res = (abs(dx) > abs(dy)) * abs(dx) + !(abs(dx) > abs(dy)) * abs(dy);
	yi = dy / (double)res;
	xi = dx / (double)res;
	a = x;
	b = y;
	while (!check_wall(data, a, b))
	{
		my_mlx_pixel_put(&data->img, a, b, 15212062);
		a += xi;
		b += yi;
	}
	printf("x == %f y == %f\n", a, b);
}

void	ft_draw_angel(t_data *data)
{
	double	res;
	double	x;
	double	y;

	res = cos(data->p.rotaion);
	x = data->p.x + res * 100;
	res = sin(data->p.rotaion);
	y = data->p.y + res * 100;
	// printf("%f  " ,30 / cos(0.523599));
	// printf("%f  " , sin(0.523599) * (30 / cos(0.523599)));
	// printf("x == %f   -- y == %f   angel == %f\n", x, y, data->p.rotaion);
	dda_alg(data, data->p.x, data->p.y, x, y);
	// int i = 17;
	// int j = 0;
	// while(j < i)
	// {
	// 	dda_alg(data, data->p.x, data->p.y, x + (-1) * j, y);
	// 	dda_alg(data, data->p.x, data->p.y, x +  j, y);
	// 	j++;
	// }
	// while (j < 30)
	// {
	// 	mlx_pixel_put(data->mlx, data->win, x, y - j, 15212062);
	// 	j++;
	// }
	//  ft_draw_line(data ,  x + 5 ,  y, 20 );
	// int i = 45;
	// int k = 0;
	// while(k < i)
	// {
	// 	mlx_pixel_put(data->mlx, data->win, data->p.x + 5 + (k * -1) ,
	// 			data->p.y  + (j * -1), 15212062);
	// // 	mlx_pixel_put(data->mlx, data->win, data->p.x + 5 + k , data->p.y
	// + (j
	// 				* -1), 15212062);
	// k++;
	// }
}

void	ft_draw_palyer(t_data *data)
{
	int	i;
	int	j;

	(void)data;
	i = 0;
	j = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
			my_mlx_pixel_put(&data->img, data->p.x + j++ - 5, i + data->p.y - 5,
					143062);
		i++;
	}
}

void	ft_creat_2d(t_data *data)
{
	int		i;
	int		j;
	int		color;
	char	c;
	char	**map;

	map = data->mm.map;
	color = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			c = map[i][j];
			color = (c == '1') * 4210752 + (c == '0') * 14012110;
			color += (c == ' ') * 10472114 + ft_strchr("NOSE", c) * 14831182;
			ft_draw(data, j * data->size, i * data->size, color);
			j++;
		}
		i++;
	}
}

int	ft_release(int ky, void *dd)
{
	t_data	*data;

	data = (t_data *)dd;
	if (ky == 'w')
		data->keys[0] = 0;
	if (ky == 'a')
		data->keys[1] = 0;
	if (ky == 's')
		data->keys[2] = 0;
	if (ky == 'd')
		data->keys[3] = 0;
	return (0);
}

int	ft_press(int ky, void *dd)
{
	t_data	*data;
	int		px;
	int		py;
	int		x;
	int		y;

	data = (t_data *)dd;
	px = data->p.x;
	py = data->p.y;
	if (ky == 65307)
		exit(11);
	x = (ky == 65362 || ky == 'd') + -(ky == 65364 || ky == 'a');
	y = (ky == 65362 || ky == 'w') + -(ky == 65364 || ky == 's');
	data->p.x += cos(data->p.rotaion) * x * data->p.movespeed;
	data->p.y += sin(data->p.rotaion) * y * data->p.movespeed;
	data->p.rotaion += (ky == 65363) * 0.174533 + (ky == 65361) * -0.174533;
	if (check_wall(data, data->p.x, data->p.y))
	{
		data->p.x = px;
		data->p.y = py;
	}
	return (0);
}

void	ft_events(t_data *data)
{
	(void)data;
	// printf("[%d|%d]\n", data->keys[0], data->keys[1]);
}

int	ft_render(void *dd)
{
	t_data	*data;

	data = dd;
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	ft_creat_2d(data);
	ft_draw_palyer(data);
	ft_draw_angel(data);
	ft_events(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_map		map;
	t_data		data;
	t_player	p;
	double		pi;

	data.keys[0] = 0;
	data.keys[1] = 0;
	data.keys[2] = 0;
	data.keys[3] = 0;
	map.C = 0;
	map.F = 0;
	map.x = 0;
	map.y = 0;
	map.x_win = 0;
	map.y_win = 0;
	data.size = 64;
	data.x_line = 0;
	data.y_line = 0;
	data.ac = 0;
	if (ac != 2 || ft_Read_Map(av[1], &map))
	{
		printf("Error\n");
		return (2);
	}
	printf("a = %f\n", 30 * cos(0.523599));
	printf("b = %f ", 34.641021 * sin(0.523599));
	// exit(0);
	data.rot = 0;
	pi = 3.14159;
	p.x = map.x * data.size - 16;
	p.y = map.y * data.size - 16;
	p.rotaion = (90) * (pi / 180);
	p.turnDer = 0;
	p.movespeed = 7.0;
	p.rot_speed = p.rotaion;
	data.p = p;
	data.x_win = map.x_win * data.size;
	data.y_win = map.y_win * data.size;
	data.mm = map;
	data.p.x -= 20;
	data.p.y -= 20;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.x_win, data.y_win, "cub_ 3D!");
	mlx_hook(data.win, 3, 1L << 1, ft_release, &data);
	mlx_hook(data.win, 2, 1L << 0, ft_press, &data);
	data.img.img = mlx_new_image(data.mlx, data.x_win, data.y_win);
	mlx_loop_hook(data.mlx, ft_render, &data);
	mlx_loop(data.mlx);
}

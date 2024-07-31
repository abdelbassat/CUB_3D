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
			if (color == 0x1EABB7)
				co = 0xdddd;
			else
				co = 0x239E37;
			mlx_pixel_put(data->mlx, data->win, x + i, j + y, co);
			y++;
		}
		x++;
	}
}

char	**convert_to_do(t_list *head)
{
	int		size;
	char	**arr;
	int		i;

	size = ft_lstsize(head);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (head)
	{
		arr[i] = ft_strdup((char *)head->content);
		i++;
		head = head->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	ft_creat_2d(t_data *data, char **map)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	j = 0;
	color = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			color = 0;
			if (j == data->pos.pos_x && i == data->pos.pos_y)
				color = 0x1EABB7;
			ft_draw(data, j * data->size, i * data->size, color);
			j++;
		}
		i++;
	}
}

void	save_pos(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N')
			{
				data->pos.pos_x = j;
				data->pos.pos_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	ft_close(int keycode, void *dd)
{
	t_data	*data;
	int		x;
	int		y;

	data = (t_data *)dd;
	x = data->pos.pos_x;
	y = data->pos.pos_y;
	if (keycode == 65307)
		exit(11);
	if (keycode == 65363)
		data->pos.pos_x += 1;
	if (keycode == 65361)
		data->pos.pos_x -= 1;
	if (keycode == 65362)
		data->pos.pos_y -= 1;
	if (keycode == 65364)
		data->pos.pos_y += 1;
	if (data->pos.pos_x >= 53 || data->pos.pos_y >= 28 || data->pos.pos_y < 0
		|| data->pos.pos_x < 0)
	{
		data->pos.pos_x = x;
		data->pos.pos_y = y;
		return (0);
	}
	ft_creat_2d(data, data->map);
	return (1);
}

int	main(int ac, char **av)
{
	t_map	map;

	// t_data	data;
	// char	**map;
	map.C = 0;
	map.F = 0;
	// (void)av;
	// data.pos.pos_x = 0;
	// data.pos.pos_y = 0;
	// save_pos(&data, map);
	// data.size = 10;
	// data.map = map;
	if (ac != 2 || ft_Read_Map(av[1], &map))
	{
		printf("Error\n");
		return (2);
	}
	printf("EA = %s\n", map.EA);
	printf("WE = %s\n", map.WE);
	printf("NO = %s\n", map.NO);
	printf("SO = %s\n", map.SO);
	printf("C = %d\nF = %d \n", map.C, map.F);
	free(map.EA);
	free(map.WE);
	free(map.NO);
	free(map.SO);
	// data.mlx = mlx_init();
	// data.win = mlx_new_window(data.mlx, (53 * 10), (28 * 10), "cub_ 3D!");
	// mlx_hook(data.win, 2, 1L << 0, ft_close, &data);
	// ft_creat_2d(&data, map);
	// mlx_loop(data.mlx);
}

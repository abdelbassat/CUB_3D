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

void	ft_parse_color(t_list *head)
{
	char	*res;

	while (head)
	{
		res = ft_substr((char *)head->content, 1,
				ft_strlen((char *)head->content) - 1);
		printf("%s\n", res);
		head = head->next;
	}
}

int	ft_len(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	ft_free(char **ar)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}

void	ft_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void	ft_for_path(t_list **head, char *str, int flag)
{
	char	**split;
	t_list	*node;

	node = ft_lstnew(str);
	split = ft_split(str, ' ');
	if (flag == 0)
	{
		if (!strcmp(split[0], "SO"))
			node->id = 1;
		else if (!strcmp(split[0], "NO"))
			node->id = 2;
		else if (!strcmp(split[0], "WE"))
			node->id = 3;
		else if (!strcmp(split[0], "EA"))
			node->id = 4;
	}
	else
	{
		if (!strcmp(split[0], "C"))
			node->id = 1;
		else if (!strcmp(split[0], "F"))
			node->id = 2;
	}
	ft_lstadd_back(head, node);
	ft_free(split);
}

void	read_map(char *file, t_map *data)
{
	int		fd;
	char	*str;
	char	**split;
	int		i;

	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	split = ft_split(str, '\n');
	i = 0;
	while (split[i])
	{
		ft_lstadd_back(&data->map, ft_lstnew(split[i]));
		i++;
	}
}

void	ft_display(t_list *head)
{
	while (head)
	{
		printf("%s\n", (char *)head->content);
		head = head->next;
	}
}

int	ft_ss(char c, char *ss)
{
	int	i;

	i = 0;
	while (ss[i])
	{
		if (c == ss[i])
			return (1);
		i++;
	}
	return (0);
}

char	**convert(t_list *head)
{
	int		i;
	char	**ss;

	ss = (char **)malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	i = 0;
	while (head)
	{
		ss[i] = ft_strdup((char *)head->content);
		i++;
		head = head->next;
	}
	ss[i] = NULL;
	return (ss);
}

int	ft_search(t_list *head)
{
	int		i;
	int		count;
	int		j;
	char	**map;

	map = convert(head);
	i = 0;
	j = 0;
	count = 0;
	while (map[i] && count <= 1)
	{
		j = 0;
		while (map[i][j])
		{
			if ((i == 0 || !map[i + 1]) && !ft_ss(map[i][j], " 1"))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	parse_map(t_map *data)
{
	t_list	*head;
	int		count1;
	int		count2;

	head = data->path;
	count1 = 0;
	count2 = 0;
	while (head)
	{
		count1 += head->id;
		head = head->next;
	}
	head = data->color;
	while (head)
	{
		count2 += head->id;
		head = head->next;
	}
	if (count1 != 10 || count2 != 3 || ft_search(data->map) > 1)
		ft_error();
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
	t_data	data;
	char	**map;

	(void)ac;
	map = ft_split("11111111111111111111111111111111111111111111111111111 10000000001100000100001000010000000001000010000100001 10110000011100000100001000000000000001000010000100001 10010000000000000100001000000000000001000010000100001 11111111101100000100001000010000000001000010000100001 11111111101100000100001000010000000001000010000100001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 1100000000110N000100000000000000000000000000000000001 11111111111111111111111111111111111111111111111111111", ' ');
	(void)av;
	data.pos.pos_x = 0;
	data.pos.pos_y = 0;
	save_pos(&data, map);
	data.size = 10;
	data.map = map;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, (53 * 10), (28 * 10), "cub_ 3D!");
	mlx_hook(data.win, 2, 1L << 0, ft_close, &data);
	ft_creat_2d(&data, map);
	mlx_loop(data.mlx);
}

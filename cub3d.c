/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:58:46 by abquaoub          #+#    #+#             */
/*   Updated: 2024/06/24 18:38:35 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	if (strcmp(ft_strrchr(file, '.'), ".cub"))
		ft_error();
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("cub3d");
		exit(1);
	}
	str = get_next_line(fd);
	split = ft_split(str, '\n');
	i = 0;
	while (split[i])
	{
		if (i < 4)
			ft_for_path(&data->path, split[i], 0);
		else if (i < 6)
			ft_for_path(&data->color, split[i], 1);
		else
			ft_lstadd_back(&data->map, ft_lstnew(split[i]));
		i++;
	}
	ft_free(split);
	free(str);
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

void	ft_draw(t_data *data)
{
	int	i;
	int	x;
	int	y;
	i = 0;
	x = 700 / 2;
	y = 500 / 2;
	while (i < 50)
	{
		x += 1;
		// y+=1;
		mlx_pixel_put(data->mlx, data->win, x, y, 0xFFFFFF);
		i++;
	}
}
int	ft_close(void *dd)
{
	(void)dd;
	exit(11);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		ft_error();
	t_map map;
	t_data data;
	map.path = NULL;
	map.color = NULL;
	map.map = NULL;
	read_map(av[1], &map);

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 700, 500, "cub_ 3D!");
	mlx_hook(data.win, 2, 1L << 0, ft_close, NULL);
	ft_draw(&data);
	mlx_loop(data.mlx);
}
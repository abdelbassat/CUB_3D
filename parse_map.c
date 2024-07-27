/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelbassat <abdelbassat@student.42.fr>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-27 09:39:22 by abdelbassat       #+#    #+#             */
/*   Updated: 2024-07-27 09:39:22 by abdelbassat      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	ft_CheckPath(char *file, char *ex)
{
	int	fd;
	int	res;

	res = -2;
	if (!strcmp(ft_strrchr(file, '.'), ex))
		res = (fd = open(file, O_RDONLY)) < 0 ? fd : 0;
	return (res);
}

char	*get_next_line(char *file)
{
	char	*buff;
	char	*data;
	int		fd;

	buff = malloc(2);
	data = NULL;
	fd = open(file, O_RDONLY);
	while (1)
	{
		if (!read(fd, buff, 1))
			break ;
		buff[1] = 0;
		data = ft_strjoin(data, buff);
	}
	return (free(buff), close(fd), data);
}

int	ft_print_err(int er)
{
	if (er == -1)
		perror("CUB3D ");
	else if (er == -2)
		ft_putstr_fd("extention Error\n", 2);
	return (er);
}

void	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	ft_parse_color(t_list *head)
{
	char	**split;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (head && !flag)
	{
		i = 0;
		split = ft_split((char *)head->content, ',');
		while (split[i] && !flag)
		{
			if ((i == 0 ? ft_atoi(&split[i][1]) : ft_atoi(split[i])) > 255)
				flag = 1;
			i++;
		}
		head = head->next;
	}
	return (flag);
}

int	ft_parse_path(t_list **pp)
{
	int		flag;
	t_list	*head;

	head = *pp;
	flag = 0;
	while (head)
	{
		(*pp)->path = ft_split((char *)head->content, ' ');
		if (!strcmp(head->path[0], "NO") && !ft_CheckPath(head->path[1],
				".xpm"))
			flag += 1;
		else if (!strcmp(head->path[0], "SO") && !ft_CheckPath(head->path[1],
					".xpm"))
			flag += 2;
		else if (!strcmp(head->path[0], "WE") && !ft_CheckPath(head->path[1],
					".xpm"))
			flag += 3;
		else if (!strcmp(head->path[0], "EA") && !ft_CheckPath(head->path[1],
					".xpm"))
			flag += 4;
		head = head->next;
	}
	return (flag == 10 ? 0 : 1);
}
// int	ft_search(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 	}
// }

// int	ft_parse_map(t_list *head)
// {
// 	int	flag;
// 	int	size;

// 	flag = 0;
// 	size = ft_lstsize(head);
// 	while (head)
// 	{
// 		head = head->next;
// 	}
// 	return (flag == 10 ? 5 : 7);
// return (flag != 10)
// }

void	ft_add(t_list *head, char *str)
{
	ft_lstadd_back(&head, ft_lstnew(str));
}

void	ft_Read_Map(char *file, t_map *map)
{
	char	**rd_file;
	int		flag;
	t_list	**head;
	char	*strtrim;
	int		i;

	head = NULL;
	if (ft_print_err(ft_CheckPath(file, ".cub")))
		return ;
	rd_file = ft_split(get_next_line(file), 10);
	flag = 0;
	i = 0;
	(void)map;
	while (rd_file && rd_file[i])
	{
		strtrim = ft_strtrim(rd_file[i], "1 ");
		if (!(*strtrim) && !flag)
			flag = 1;
		if (!ft_strchr(rd_file[i], 44) && !flag)
			head = &map->path;
		else if (ft_strchr(rd_file[i], 44) && !flag)
			head = &map->color;
		else if (flag)
			head = &map->map;
		ft_lstadd_back(head, ft_lstnew(rd_file[i]));
		i++;
		free(strtrim);
	}
	ft_free(rd_file);
}

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

void	ft_Display(t_list *head)
{
	while (head)
	{
		printf("%s\n", (char *)head->content);
		head = head->next;
	}
}

void	ft_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("--%s--\n", str[i]);
		i++;
	}
}

char	*ft_join(char *str, int max)
{
	int		i;
	char	*arr;
	int		len;

	len = ft_strlen(str);
	i = 0;
	arr = malloc(sizeof(char *) * (max + 1));
	while (str[i] || i < max)
	{
		if (i < len)
			arr[i] = str[i];
		else
			arr[i] = ' ';
		i++;
	}
	arr[i] = 0;
	return (arr);
}

int	ft_CheckPath(char *file, char *ex)
{
	int	fd;
	int	res;

	res = -2;
	if (!strcmp(ft_strrchr(file, '.'), ex) && (fd = open(file, O_RDONLY)))
		res = ((fd < 0) * fd + !(fd < 0) * 0);
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

char	*ft_return(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (&str[i]);
		i++;
	}
	return (str);
}

int	ft_count(char **ss)
{
	int	i;

	i = 0;
	while (ss[i])
		i++;
	return (i);
}

int	ft_check_num(char *num, t_map *map)
{
	char	**ss;
	int		count;
	char	**child;
	int		i;
	int		n;

	i = 0;
	ss = ft_split(num, ',');
	count = (ft_count(ss) == 3) * 0 + ((ft_count(ss) != 3) * 10);
	while (ss[i] && !count)
	{
		if (!i)
		{
			child = ft_split(ss[i], ' ');
			n = ft_atoi(child[1]);
			if (ft_count(child) != 2 || n > 255)
				count++;
			map->color += n * 65536;
			i++;
			ft_free(child);
		}
		else
		{
			n = ft_atoi(ss[i]);
			map->color += (i == 1) * (n * 256) + (i != 1) * n;
			count += ((n <= 255) * 0 + (n > 255) * 1);
		}
		i++;
	}
	return (ft_free(ss), count);
}

int	ft_check_char(char *str, t_map *map)
{
	int		i;
	int		count;
	char	*tr;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strchr("0123456789 ,CF", str[i]))
			count++;
		if ((ft_strchr("C,", str[i]) && count++) || (str[i] == 'F' && (count
					+= 2)))
			count *= 1;
		i++;
	}
	tr = ft_strtrim(str, " ");
	count = ft_check_num(tr, map) + count;
	return (free(tr), count);
}

int	ft_path(char *str)
{
	char	**split;
	int		flag;

	flag = 0;
	split = ft_split(str, ' ');
	if (!strcmp(split[0], "NO") && !ft_CheckPath(split[1], ".xpm"))
		flag += 1;
	else if (!strcmp(split[0], "SO") && !ft_CheckPath(split[1], ".xpm"))
		flag += 2;
	else if (!strcmp(split[0], "WE") && !ft_CheckPath(split[1], ".xpm"))
		flag += 3;
	else if (!strcmp(split[0], "EA") && !ft_CheckPath(split[1], ".xpm"))
		flag += 4;
	return (flag);
}

int	Check_space(char **map, int i, int j)
{
	if ((!map[i][j + 1] || ft_strchr("1 ", map[i][j + 1])) && (!j
			|| ft_strchr("1 ", map[i][j - 1])) && (!i || ft_strchr("1 ", map[i
				- 1][j])) && (!map[i + 1] || ft_strchr("1 ", map[i + 1][j])))
		return (1);
	return (0);
}

int	ft_parse_map(char **map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if ((((!i || !map[i + 1]) || (!j || !map[i][j + 1]))
					&& !ft_strchr("1 ", map[i][j])) || ft_strchr("NOSE",
					map[i][j]))
				count++;
			if (map[i][j] == ' ' && !Check_space(map, i, j)
				&& ft_strchr("NOSE 01", map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return ((count == 1) * 0 + (count != 1) * 1);
}

char	**ft_convertt(char *str)
{
	int		i;
	int		num;
	char	**ss;
	int		max;
	char	*save;

	i = 0;
	ss = ft_split(str, '\n');
	max = 0;
	while (ss[i])
	{
		num = ft_strlen(ss[i]);
		if (num > max)
			max = num;
		i++;
	}
	i = 0;
	while (ss[i])
	{
		save = ss[i];
		ss[i] = ft_join(ss[i], max);
		free(save);
		i++;
	}
	return (ss);
}
int	ft_Read_Map(char *file, t_map *map)
{
	char	**rd_file;
	char	*strtrim;
	int		i;
	int		count;
	char	*join;

	(void)map;
	join = NULL;
	count = 0;
	if (ft_print_err(ft_CheckPath(file, ".cub")))
		return (1);
	rd_file = ft_split(get_next_line(file), 10);
	i = 0;
	while (rd_file && rd_file[i])
	{
		strtrim = ft_strtrim(rd_file[i], " ");
		if (ft_strchr(rd_file[i], '.'))
			count += ft_path(rd_file[i]);
		else if (ft_strchr(rd_file[i], ','))
			count += ft_check_char(rd_file[i], map);
		else if (*strtrim)
		{
			join = ft_strjoin(join, rd_file[i]);
			join = ft_strjoin(join, "\n");
		}
		free(strtrim);
		i++;
	}
	return (count + ft_parse_map(ft_convertt(join)));
}

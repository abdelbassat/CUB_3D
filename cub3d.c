/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:58:46 by abquaoub          #+#    #+#             */
/*   Updated: 2024/06/23 20:37:02 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_len(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}


void ft_free(char **ar)
{
	int i = 0;
	while(ar[i])
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}


void ft_error()
{
	ft_putstr_fd("Error\n" , 2);
	exit(1);
}

void ft_for_path(t_list **head ,  char *str , int flag)
{
	char **split;
	t_list *node = ft_lstnew(str);
	split = ft_split(str , ' ');
	if(flag == 0)
	{

	if(!strcmp(split[0], "SO"))
		node->id = 1;
	else if(!strcmp(split[0], "NO"))
		node->id = 2;
	else if(!strcmp(split[0], "WE"))
		node->id = 3;
	else if(!strcmp(split[0], "EA"))
		node->id = 4;
	}
	else
	{
		if(!strcmp(split[0], "C"))
		node->id = 1;
	else if(!strcmp(split[0], "F"))
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

	if(strcmp(ft_strrchr(file , '.') , ".cub"))
		ft_error();
	fd = open(file, O_RDONLY);
	if(fd == -1)
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
			ft_for_path(&data->path ,  split[i] , 0);
		else if (i < 6)
			ft_for_path(&data->color ,  split[i] , 1);
		else
			ft_lstadd_back(&data->map, ft_lstnew(split[i]));
		i++;
	}
	ft_free(split);
	free(str);
}

void ft_display(t_list *head)
{
	while(head)
	{
		printf("%s\n" , (char *)head->content);
		head = head->next;
	}

	

}


void parse_map(t_map *data)
{
	t_list *head = data->path;
	int count1 = 0;
	int count2 = 0;
	while(head)
	{
		count1 += head->id;	
		head = head->next;
	}

	head = data->color;
	while(head)
	{
		count2 += head->id;	
		head = head->next;
	}
	
	if(count1 == 10 && count2 == 3)
		return;
	ft_error();
}






int	main(int ac, char **av)
{
	if(ac != 2)
		ft_error();
	t_map data;
	data.path = NULL;
	data.color = NULL;
	data.map = NULL;
	read_map(av[1], &data);
	parse_map(&data);
	ft_display(data.path);
}
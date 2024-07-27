/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:59:17 by abquaoub          #+#    #+#             */
/*   Updated: 2024/07/17 13:42:26 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_pos
{
	int		pos_x;
	int		pos_y;

}			t_pos;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	**map;
	int		size;
	t_pos	pos;

}			t_data;

typedef struct s_map
{
	char	**rd_file;
	t_list	*path;
	t_list	*color;
	t_list	*map;

}			t_map;

void		ft_Read_Map(char *file, t_map *map);
int			ft_parse_color(t_list *map);
int			ft_parse_path(t_list **pp);

#endif

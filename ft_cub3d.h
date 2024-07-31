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
	int color ;
	char	**map;

}			t_map;

int 		ft_Read_Map(char *file, t_map *map);
char	*ft_join(char *str, int max);
int			ft_parse_color(t_list *map);
int			ft_parse_path(t_list *pp);
int			ft_parse_map(char **map);
char		**ft_convert(t_list *head);
void		ft_print(char **str);
void		ft_Display(t_list *head);

#endif

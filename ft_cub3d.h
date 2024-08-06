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
# include <math.h>
# include <stdio.h>
typedef struct s_pos
{
	int			pos_x;
	int			pos_y;

}				t_pos;

typedef struct s_player
{
	double			x;
	double			y;
	double rotaion;
	double turnDer;
	double movespeed ;
	double rot_speed;

}				t_player;

typedef struct s_map
{
	int			F;
	int			C;
	int			x;
	int			y;
	int			x_win;
	int			y_win;
	char		**map;
	char		*SO;
	char		*EA;
	char		*WE;
	char		*NO;

}				t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

}				t_img;

typedef struct s_data
{
	int x_line;
	int y_line;
	int keys[4];
	double rot;
	int			x_win;
	int			y_win;
	void		*mlx;
	void		*win;
	// char		*img;
	int ac;
	int			size;
	double eng;

	int		bpp; /* bits per pixel */
    int		line_len;
	t_map		mm;
	t_player	p;
	t_img img;

}				t_data;

int				ft_Read_Map(char *file, t_map *map);
char			*ft_join(char *str, int max);
int				ft_parse_map(char **map);
void			ft_print(char **str);
int				ft_jock(char **str, int flag);

#endif

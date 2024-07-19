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

#include <mlx.h>

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>



typedef struct s_pos
{
  int pos_x;
  int pos_y;
       
}t_pos;



typedef struct s_data
{
  void *mlx;
  void *win;
  void *img;  
  char **map;
  int size;
  t_pos pos;
       
}t_data;



typedef struct s_map
{
   t_list *path;
   t_list *color;
   t_list *map;
       
}t_map;


#endif

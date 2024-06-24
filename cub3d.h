/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:59:17 by abquaoub          #+#    #+#             */
/*   Updated: 2024/06/24 18:27:07 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>



typedef struct s_data
{
  void *mlx;
  void *win;
       
}t_data;



typedef struct s_map
{
   t_list *path;
   t_list *color;
   t_list *map;
       
}t_map;


#endif

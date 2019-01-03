/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 03:08:28 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/22 03:25:59 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef UI_H
# define UI_H

typedef struct		s_size
{
	size_t			height;
	size_t			width;
}					t_size;

typedef struct		s_pixel
{
	int				x;
	int				y;
	int				color;
}					t_pixel;

typedef struct		s_color
{
	u_int8_t		r;
	u_int8_t		g;
	u_int8_t		b;
	u_int8_t		a;
}					t_color;

t_color				ft_color(u_int8_t r, u_int8_t g, u_int8_t b);
t_color				ft_i_color(int c);
int					ft_color_i(t_color c);
t_color				ft_color_gradient(t_color a, t_color b, float percent);

t_pixel				ft_pixel_add(t_pixel a, t_pixel b);
t_pixel				ft_pixel_sub(t_pixel a, t_pixel b);
t_pixel				ft_pixel_div(t_pixel a, t_pixel b);
t_pixel				ft_pixel_mul(t_pixel a, t_pixel b);

#endif
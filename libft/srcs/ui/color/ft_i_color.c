/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 03:20:27 by llelievr          #+#    #+#             */
/*   Updated: 2018/12/22 03:27:13 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_color		ft_i_color(int c)
{
	return (ft_color((u_int8_t)((c & 0xFF0000) >> 16),
		(u_int8_t)((c & 0xFF00) >> 8),
		(u_int8_t)(c & 0xFF)));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:57:46 by pguthaus          #+#    #+#             */
/*   Updated: 2019/01/03 14:23:33 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				close_main(char *msg, int status)
{
	if (msg)
		ft_putendl(msg);
	return (status);
}

int				main(int argc, char **argv)
{
	t_fillit	fillit;

	if (argc < 2)
		return (close_main("usage: ./fillit [teriminos_file]", 1));
	if (!(ft_read(argv[1], &fillit)))
		return (close_main("error", 1));
	fillit.grid_size = 2;
	ft_bzero(fillit.map, 4046);
	ft_fillit(&fillit);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 14:48:11 by llelievr          #+#    #+#             */
/*   Updated: 2019/01/03 14:47:57 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	fill_with_newlines(uint8_t *map, uint16_t size)
{
	int	i;

	i = 0;
	while (i < size)
		map[i++ * size] = '\n';
}

void		print(t_tetri *tetriminos, uint16_t size)
{
	uint8_t		map[4096];
	uint8_t		i;
	int8_t		j;
	int8_t		shift;
	uint8_t		line;

	i = 0;
	ft_memset(map, '.', sizeof(map));
	while (tetriminos[i].value)
	{
		shift = 4;
		while (--shift >= 0)
		{
			line = (tetriminos[i].value >> (4 * shift)) & 0xF;
			j = 4;
			while (--j >= 0)
				if ((line >> j) & 1)
					map[(tetriminos[i].y + (3 - shift))
						* size + tetriminos[i].x + 4 - j] = 'A' + i;
		}
		i++;
	}
	fill_with_newlines(map, size);
	write(1, map + 1, size * (size - 1));
}

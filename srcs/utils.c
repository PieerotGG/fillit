/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 14:49:35 by llelievr          #+#    #+#             */
/*   Updated: 2019/01/15 12:52:15 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		place_bits(uint8_t *data, size_t pos, uint8_t to_place)
{
	data[pos / 8] ^= to_place >> (pos % 8);
	data[pos / 8 + 1] ^= to_place << (8 - (pos % 8));
}

int			test_bits(uint8_t *data, size_t pos, uint8_t to_test)
{
	return (data[pos / 8] & (to_test >> (pos % 8))
		|| data[pos / 8 + 1] & (to_test << (8 - (pos % 8))));
}

t_bool		tetri_value(t_tetri tetri, int index)
{
	return ((tetri.value >> (15 - index)) & 1);
}

void		organize_tetri(t_tetri *t)
{
	while (!(t->value & 0x8888) || !(t->value & 0xF000))
	{
		if (!(t->value & 0xF000))
			t->value <<= 4;
		if (!(t->value & 0x8888))
			t->value <<= 1;
	}
	t->cols = !!(t->value & 0x8888) + !!(t->value & 0x4444)
		+ !!(t->value & 0x2222) + !!(t->value & 0x1111);
	t->rows = !!(t->value & 0xF000) + !!(t->value & 0x0F00)
		+ !!(t->value & 0x00F0) + !!(t->value & 0x000F);
}

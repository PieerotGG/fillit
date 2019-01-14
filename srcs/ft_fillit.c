/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:14:27 by pguthaus          #+#    #+#             */
/*   Updated: 2019/01/14 12:33:25 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int				check_tetrimino(uint8_t *map, uint16_t s, t_tetri *t)
{
	return (test_bits(map, t->y * s + t->x, ((t->value >> 12) & 0xF) << 4)
	|| test_bits(map, (t->y + 1) * s + t->x, ((t->value >> 8) & 0xF) << 4)
	|| test_bits(map, (t->y + 2) * s + t->x, ((t->value >> 4) & 0xF) << 4)
	|| test_bits(map, (t->y + 3) * s + t->x, (t->value & 0xF) << 4));
}

void			place_tetrimino(uint8_t *map, uint16_t size, t_tetri *t)
{
	place_bits(map, t->y * size + t->x, ((t->value >> 12) & 0xF) << 4);
	place_bits(map, (t->y + 1) * size + t->x, ((t->value >> 8) & 0xF) << 4);
	place_bits(map, (t->y + 2) * size + t->x, ((t->value >> 4) & 0xF) << 4);
	place_bits(map, (t->y + 3) * size + t->x, (t->value & 0xF) << 4);
}

static int		solve(t_fillit *inst, size_t i)
{
	t_tetri		*t;

	if (i >= inst->t_triminos_count)
		return (1);
	t = &inst->t_triminos[i];
	if (inst->grid_size < t->cols || inst->grid_size < t->rows)
		return (0);
	t->y = (t->same ? t->same->y : 0);
	while (t->y + t->rows <= inst->grid_size)
	{
		t->x = (t->same && t->same->y == t->y ? t->same->x : 0);
		while (t->x + t->cols <= inst->grid_size)
		{
			if (!check_tetrimino(inst->map, inst->grid_size, t))
			{
				place_tetrimino(inst->map, inst->grid_size, t);
				if (solve(inst, i + 1))
					return (1);
				place_tetrimino(inst->map, inst->grid_size, t);
			}
			t->x++;
		}
		t->y++;
	}
	return (0);
}

t_bool			ft_fillit(t_fillit *fillit)
{
	while (fillit->grid_size * fillit->grid_size < fillit->t_triminos_count * 4)
		fillit->grid_size++;
	while (!solve(fillit, 0) && fillit->grid_size <= 16)
		fillit->grid_size++;
	print(fillit->t_triminos, fillit->grid_size + 1);
	return (FALSE);
}

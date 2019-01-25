/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:46:32 by pguthaus          #+#    #+#             */
/*   Updated: 2019/01/25 14:27:58 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

static int		count_adjacent(t_tetri t, int index)
{
	int		count;

	count = 0;
	if (index - 1 >= 0 && tetri_value(t, index - 1))
		count++;
	if (index + 1 < 16 && tetri_value(t, index + 1))
		count++;
	if (index - 4 >= 0 && tetri_value(t, index - 4))
		count++;
	if (index + 4 < 16 && tetri_value(t, index + 4))
		count++;
	return (count);
}

static t_bool	check_tetri(t_fillit *inst)
{
	size_t	curr;
	int		parts;
	int		adjacents;
	int		add;
	int		i;

	curr = 0;
	while (curr < inst->t_triminos_count)
	{
		parts = 0;
		adjacents = 0;
		i = -1;
		while (++i < 16)
			if (tetri_value(inst->t_triminos[curr], i))
			{
				if ((add = count_adjacent(inst->t_triminos[curr], i)) == 0)
					return (FALSE);
				adjacents += add;
				parts++;
			}
		if (parts != 4 || adjacents < 6)
			return (FALSE);
		curr++;
	}
	return (TRUE);
}

static void		compare(int current_te, t_tetri *t, t_fillit *fillit)
{
	int		i;

	i = -1;
	while (++i < current_te)
		if (fillit->t_triminos[i].value == t->value)
			t->same = fillit->t_triminos + i;
}

static uint16_t	ft_next_tetriminos(int fd, uint8_t *done)
{
	uint16_t	res;
	uint8_t		x;
	uint8_t		y;
	char		buff[BUFF_SIZE];
	int8_t		rd_res;

	y = 0;
	res = 0;
	while (y < 4 && (rd_res = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (rd_res != BUFF_SIZE || buff[BUFF_SIZE - 1] != '\n')
			return (TETRIMINO_ERROR);
		x = 0;
		while (x < 4)
		{
			res <<= 1;
			if (buff[x++] == '#')
				res += 1;
		}
		y++;
	}
	if (y == 4 && ((rd_res = read(fd, buff, 1)) == 1) && (buff[0] == '\n'))
		return (res);
	else if (y == 4 && res == 0)
		return (TETRIMINO_EMPTY);
	else if (y == 4 && rd_res == 0)
		*done = 1;
	else
		return (TETRIMINO_ERROR);
	return (res);
}


t_bool			ft_read(const char *file, t_fillit *state)
{
	uint8_t		current;
	int16_t		fd;
	uint8_t		done;
	t_tetri		*t;

	if ((fd = open (file, O_RDONLY)) < 0)
		return (FALSE);
	done = 0;
	ft_bzero((void *)&state->t_triminos, sizeof(t_tetri) * 26);
	current = 0;
	while ((state->t_triminos[current].value = ft_next_tetriminos(fd, &done)) != 0)
	{
		if (state->t_triminos[current].value == TETRIMINO_ERROR || state->t_triminos[current].value == TETRIMINO_EMPTY)
			return (FALSE);
		t = &state->t_triminos[current];
		organize_tetri(t);
		compare(current++, t, state);
		if (done == 1)
			break;
	}
	state->t_triminos_count = current;
	return (current <= 26 && current > 0 && check_tetri(state));
}

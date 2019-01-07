/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:46:32 by pguthaus          #+#    #+#             */
/*   Updated: 2019/01/07 14:08:28 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static uint16_t	ft_next_tetriminos(int fd)
{
	uint16_t	tetriminos;
	size_t		current_line;
	char		buff[BUFF_SIZE];
	int			rd_res;
	size_t		chr;

	current_line = 0;
	tetriminos = 0;
	while (current_line < 4 && (rd_res = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (rd_res != BUFF_SIZE)
			return (0);
		chr = 0;
		while (chr < 4)
		{
			tetriminos <<= 1;
			if (buff[chr++] == '#')
				tetriminos += 1;
		}
		current_line++;
	}
	return (rd_res <= 0 ? 0 : tetriminos);
}

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

t_bool			ft_read(const char *file, t_fillit *fillit)
{
	char		c;
	int			current_te;
	int			fd;
	t_tetri		*t;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (FALSE);
	ft_bzero((void *)&fillit->t_triminos, sizeof(t_tetri) * 26);
	current_te = 0;
	while ((fillit->t_triminos[current_te].value = ft_next_tetriminos(fd)))
	{
		t = &fillit->t_triminos[current_te];
		organize_tetri(t);
		t->cols = !!(t->value & 0x8888) + !!(t->value & 0x4444)
			+ !!(t->value & 0x2222) + !!(t->value & 0x1111);
		t->rows = !!(t->value & 0xF000) + !!(t->value & 0x0F00)
			+ !!(t->value & 0x00F0) + !!(t->value & 0x000F);
		compare(current_te++, t, fillit);
		read(fd, &c, 1);
	}
	fillit->t_triminos_count = current_te;
	return (current_te <= 26 && current_te > 0 && check_tetri(fillit));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llelievr <llelievr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 17:07:46 by pguthaus          #+#    #+#             */
/*   Updated: 2019/01/03 14:31:17 by llelievr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdint.h>
# include <stdlib.h>
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# define BUFF_SIZE 5

typedef struct	s_tetri
{
	uint16_t		value;
	size_t			cols;
	size_t			rows;
	size_t			x;
	size_t			y;
	struct s_tetri	*same;
}				t_tetri;

typedef struct	s_fillit
{
	t_tetri		t_triminos[26];
	size_t		t_triminos_count;
	uint8_t		map[4096];
	size_t		grid_size;
}				t_fillit;

typedef enum	e_bool
{
	TRUE = 1,
	FALSE = 0
}				t_bool;

t_bool		ft_fillit(t_fillit *fillit);
void		print(t_tetri *tetriminos, uint16_t size);
void		place_bits(uint8_t *data, size_t pos, uint8_t to_place);
int			test_bits(uint8_t *data, size_t pos, uint8_t to_test);
t_bool		tetri_value(t_tetri tetri, int index);
void		organize_tetri(t_tetri *tetri);
t_bool		ft_read(const char *file, t_fillit	*fillit);
#endif

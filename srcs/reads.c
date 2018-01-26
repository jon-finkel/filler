/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 18:26:03 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/26 17:53:06 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

#define PAD(x) (x + 4)

static inline int8_t			get_origin(t_data *data, int x, int y)
{
	data->E[0] = x;
	data->E[1] = y;
	data->N[0] = x;
	data->N[1] = y;
	data->S[0] = x;
	data->S[1] = y;
	data->W[0] = x;
	data->W[1] = y;
	KTHXBYE;
}

static inline void				get_op_move(t_data *data, int x, int y)
{
	data->op_pos[0] = x;
	data->op_pos[0] = y;
}

inline bool						up_map(t_data *restrict data,
								const char *restrict line, int8_t r_pos)
{
	int		x;
	int		y;

	x = -1;
	y = ft_atoi(line);
	while (line[PAD(++x)])
	{
		if (r_pos == 42 && ((line[PAD(x)] == 'O' && data->self == 'O')
			|| (line[PAD(x)] == 'X' && data->self == 'X')))
			r_pos = get_origin(data, x, y);
		if (line[PAD(x)] == 'O')
		{
			if (data->opponent == 'X' && r_pos && !(r_pos = 0))
				get_op_move(data, x, y);
			data->map[y][x] = 'O';
		}
		else if (line[PAD(x)] == 'X')
		{
			if (data->opponent == 'X' && r_pos && !(r_pos = 0))
				get_op_move(data, x, y);
			data->map[y][x] = 'X';
		}
	}
	GIMME(r_pos);
}

inline int						pc_coord(char *restrict line, int *restrict y)
{
	*y = ft_atoi(line + 6);
	GIMME(ft_atoi(line + ft_intlen((intmax_t)*y) + 6));
}

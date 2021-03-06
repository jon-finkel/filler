/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 18:26:03 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/03 18:24:22 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

#define PAD(x) (x + 4)

static inline void			get_op_move(t_data *data, const int x, const int y)
{
	data->op_pos[0] = x;
	data->op_pos[1] = y;
}

inline bool					up_map(t_data *data, const char *line, bool r_pos)
{
	int		x;
	int		y;

	x = -1;
	y = ft_atoi(line);
	while (line[PAD(++x)])
	{
		if (line[PAD(x)] == 'O')
		{
			if (r_pos == true && data->op == 'O' && data->map[y][x] == '.'
				&& !(r_pos = false))
				get_op_move(data, x, y);
			data->map[y][x] = 'O';
		}
		else if (line[PAD(x)] == 'X')
		{
			if (r_pos == true && data->op == 'X' && data->map[y][x] == '.'
				&& !(r_pos = false))
				get_op_move(data, x, y);
			data->map[y][x] = 'X';
		}
	}
	GIMME(r_pos);
}

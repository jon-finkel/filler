/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 18:26:03 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/25 20:33:39 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

#define PAD(x) (x + 4)

static inline bool			get_origin(t_data *data, int x, int y)
{
	data->E[0] = x;
	data->E[1] = y;
	data->N[0] = x;
	data->N[1] = y;
	data->S[0] = x;
	data->S[1] = y;
	data->W[0] = x;
	data->W[1] = y;
	GIMME(false);
}

inline bool					up_map(t_data *data, const char *line, bool first)
{
	int				x;
	int				y;

	x = -1;
	y = ft_atoi(line);
	while (line[PAD(++x)])
	{
		if (first == true && ((line[PAD(x)] == 'O' && data->self == 'O')
			|| (line[PAD(x)] == 'X' && data->self == 'X')))
			first = get_origin(data, x, y);
		if (line[PAD(x)] == 'O')
			data->map[y][x] = 'O';
		else if (line[PAD(x)] == 'X')
			data->map[y][x] = 'X';
		else if (line[PAD(x)] == 'o' || line[PAD(x)] == 'x')
			data->map[y][x] = 'L';
	}
	GIMME(first);
}

inline int					pc_coord(char *restrict line, int *restrict y)
{
	*y = ft_atoi(line + 6);
	GIMME(ft_atoi(line + ft_intlen((intmax_t)*y) + 6));
}

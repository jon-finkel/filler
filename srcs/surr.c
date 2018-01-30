/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 13:52:51 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/30 22:41:03 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static inline void			check_sides(t_data *data, const int x, const int y)
{
	if (x && y && data->map[y - 1][x - 1] == '.')
		data->map[y - 1][x - 1] = '*';
	if (x && y < data->my - 1 && data->map[y + 1][x - 1] == '.')
		data->map[y + 1][x - 1] = '*';
	if (y && x < data->mx - 1 && data->map[y - 1][x + 1] == '.')
		data->map[y - 1][x + 1] = '*';
	if (x < data->mx - 1 && y < data->my - 1
		&& data->map[y + 1][x + 1] == '.')
		data->map[y + 1][x + 1] = '*';
	if (x && data->map[y][x - 1] == '.')
		data->map[y][x - 1] = '*';
	if (x < data->mx - 1 && data->map[y][x + 1] == '.')
		data->map[y][x + 1] = '*';
	if (y && data->map[y - 1][x] == '.')
		data->map[y - 1][x] = '*';
	if (y < data->my - 1 && data->map[y + 1][x] == '.')
		data->map[y + 1][x] = '*';
}

t_data						*strat_map(t_data *data)
{
	int		k;
	int		p;

	k = -1;
	while (data->map[++k])
	{
		p = -1;
		while (data->map[k][++p])
			if (data->map[k][p] == (data->op == 'X' ? 'X' : 'O'))
				check_sides(data, p, k);
	}
	GIMME(data);
}

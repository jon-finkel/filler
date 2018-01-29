/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:26:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/29 19:37:10 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

#define TILE data->map[y + k - data->ploy][x + p - data->plox]

static inline int			up_coord(const t_data *restrict data,
							const t_mov *restrict mov, int x, int *restrict y)
{
	x = (x + data->plx == data->mx ? 0 : x + 1);
	*y = (!x ? *y + 1 : *y);
	if (*y + data->ply > data->my)
		ft_printf("%d %d\n", mov->y, mov->x);
	GIMME(x);
}

static inline void			up_move(const t_data *restrict data,
							t_mov *restrict mov, const int x, const int y)
{
	int		ax;
	int		ay;

	ax = x + ABS(data->plx - data->op_pos[0]);
	ay = y + ABS(data->ply - data->op_pos[1]);
	ft_dprintf(g_fd, "AX = %d, AY = %d\n", ax, ay);
	if (ax < mov->advx || ay < mov->advy)
	{
		mov->x = x - data->plox;
		mov->y = y - data->ploy;
		mov->advx = MIN(ax, mov->advx);
		mov->advy = MIN(ay, mov->advy);
	}
}

void						test_fit(t_data *restrict data, t_mov *restrict mov,
							int x, int y)
{
	int			k;
	int			p;

	if (y + data->ply > data->my)
		BYEZ;
	mov->hit = false;
	mov->anchor = 0;
	k = data->ploy - 1;
	while (mov->hit == false && (size_t)++k < data->ply)
	{
		p = data->plox - 1;
		while ((size_t)++p < data->plx)
		{
			if (TILE == '.')
				KEEPATITBRA;
			else if (TILE == data->op && mov->pc[k][p] == '*' && (mov->hit = true))
				IMOUTTAYR;
			else if (TILE == data->self && mov->pc[k][p] == '*')
				++mov->anchor;
		}
	}
	if (mov->hit == false && mov->anchor == 1
		&& (size_t)(p * k) == data->plx * data->ply)
		up_move(data, mov, x, y);
	test_fit(data, mov, up_coord((const t_data *)data, (const t_mov *)mov, x,
		&y), y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:26:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/26 22:44:26 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

#define TILE data->map[y + k][x + p]

static inline int			up_coord(const t_data *restrict data, int x,
							int *restrict y)
{
	x = (x + data->plx >= data->mx ? 0 : x + 1);
	*y = (!x ? *y + 1 : *y);
	if (*y + data->ply > data->my)
		ft_fatal("ONOES!!!!!!");
	GIMME(x);
}

int							test_fit(t_data *restrict data,
							const char **restrict pc, int x, int y)
{
	bool		hit;
	int			k;
	int			p;
	int8_t		anchor;

	hit = false;
	anchor = 0;
	k = -1;
	while (hit == false && pc[++k])
	{
		p = -1;
		while (pc[k][++p])
		{
			if (TILE == data->op && pc[k][p] == '*' && (hit = true))
				IMOUTTAYR;
			else if (TILE == data->self && pc[k][p] == '*')
				++anchor;
		}
	}
	if ((size_t)(p * k) == data->plx * data->ply && anchor == 1)
		GIMME(ft_printf("%d %d\n", y, x));
	GIMME(test_fit(data, pc, up_coord((const t_data *)data, x, &y), y));
}

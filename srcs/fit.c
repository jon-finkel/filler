/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:26:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/27 17:01:48 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

#define TILE data->map[y + k][x + p]

static inline int			up_coord(const t_data *restrict data, int x,
							int *restrict y)
{
	x = (x + data->plx == data->mx ? 0 : x + 1);
	*y = (!x ? *y + 1 : *y);
	if (*y + data->ply > data->my)
		ft_putendl("ONOES");
	GIMME(x);
}

void						test_fit(t_data *restrict data,
							const char **restrict pc, int x, int y)
{
	bool		hit;
	int			k;
	int			p;
	int8_t		anchor;

	if (y + data->ply > data->my)
		BYEZ;
	hit = false;
	anchor = 0;
	k = -1;
	while (hit == false && (size_t)++k < data->ply)
	{
		p = -1;
		while ((size_t)++p < data->plx)
		{
			if (TILE == data->op && pc[k][p] == '*' && (hit = true))
				IMOUTTAYR;
			else if (TILE == data->self && pc[k][p] == '*')
				++anchor;
		}
	}
	if ((size_t)(p * k) == data->plx * data->ply && anchor == 1)
		ft_printf("%d %d\n", y, x);
	else
		test_fit(data, pc, up_coord((const t_data *)data, x, &y), y);
}

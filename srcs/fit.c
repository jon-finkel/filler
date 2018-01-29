/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:26:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/29 04:32:44 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

#define TILE data->map[y + k - data->ploy][x + p - data->plox]

static inline int			up_coord(const t_data *restrict data, int x,
							int *restrict y)
{
	x = (x + data->plx == data->mx ? 0 : x + 1);
	*y = (!x ? *y + 1 : *y);
	if (*y + data->ply > data->my)
		ft_putendl("0 0");
	GIMME(x);
}

void						test_fit(t_data *restrict data, t_mov *restrict mov,
							int x, int y)
{
	bool		hit;
	int			k;
	int			p;
	int8_t		anchor;

	if (y + data->ply > data->my)
		BYEZ;
	hit = false;
	anchor = 0;
	k = data->ploy - 1;
	while (hit == false && (size_t)++k < data->ply)
	{
		p = data->plox - 1;
		while ((size_t)++p < data->plx)
		{
			if (TILE == '.')
				KEEPATITBRA;
			else if (TILE == data->op && mov->pc[k][p] == '*' && (hit = true))
				IMOUTTAYR;
			else if (TILE == data->self && mov->pc[k][p] == '*')
				++anchor;
		}
	}
	if (hit == false && anchor == 1 && (size_t)(p * k) == data->plx * data->ply)
		ft_printf("%d %d\n", y - data->ploy, x - data->plox);
	else
		test_fit(data, mov, up_coord((const t_data *)data, x, &y), y);
}

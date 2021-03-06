/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:26:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/08 16:58:07 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

#define TICX (crd->x + crd->p - data->plox)
#define TICY (crd->y + crd->k - data->ploy)
#define TILE data->map[TICY][TICX]

static inline t_crd			*up_coord(const t_data *data, const t_mov *mov,
							t_crd *crd)
{
	crd->x = (crd->x + data->plx - data->plox == data->mx ? 0 : crd->x + 1);
	if (!crd->x)
		++crd->y;
	if (crd->y + data->ply - data->ploy > data->my)
		ft_printf("%d %d\n", mov->y, mov->x);
	GIMME(crd);
}

static inline void			check_move(const t_data *data, t_mov *mov,
							t_crd *crd)
{
	if (TILE == data->op && mov->pc[crd->k][crd->p] == '*' && (mov->hit = true))
		BYEZ;
	else if (TILE == data->self && mov->pc[crd->k][crd->p] == '*')
		if ((mov->anchor += 1) > 1)
			BYEZ;
	if (mov->pc[crd->k][crd->p] == '*')
	{
		if (TILE == '*' && ++mov->contact)
			BYEZ;
		else if (!mov->contact)
			mov->reach = POW2(TICX - data->op_pos[0]) +\
				POW2(TICY - data->op_pos[1]);
	}
}

void						test_fit(t_data *data, t_mov *mov, t_crd *crd)
{
	if (crd->y + data->ply - data->ploy > data->my)
		BYEZ;
	mov->hit = false;
	mov->anchor = 0;
	mov->contact = 0;
	mov->reach = 0;
	crd->k = data->ploy - 1;
	while (mov->anchor < 2 && mov->hit == false && ++crd->k < data->ply)
	{
		crd->p = data->plox - 1;
		while (mov->anchor < 2 && mov->hit == false && ++crd->p < data->plx)
			check_move(data, mov, crd);
	}
	if (mov->hit == false && mov->anchor == 1 && (mov->contact > mov->prio
		|| (!mov->prio && mov->rprio > mov->reach)))
	{
		mov->prio = mov->contact;
		mov->rprio = mov->reach;
		mov->x = crd->x - data->plox;
		mov->y = crd->y - data->ploy;
	}
	test_fit(data, mov, up_coord(data, mov, crd));
}

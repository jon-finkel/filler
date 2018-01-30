/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 19:26:56 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/30 16:46:31 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

#define TICX (crd->x + crd->p)
#define TICY (crd->y + crd->k)
#define TILE data->map[TICY - data->ploy][TICX - data->plox]

static inline t_crd			*up_coord(const t_data *restrict data,
							const t_mov *restrict mov, t_crd *restrict crd)
{
	if (!(crd->x = (crd->x + data->plx == data->mx ? 0 : crd->x + 1)))
		++crd->y;
	if (crd->y + data->ply > data->my)
		ft_printf("%d %d\n", mov->y, mov->x);
	GIMME(crd);
}

static inline double		get_reach(const t_data *restrict data,
							const t_crd *restrict crd, const int x, const int y)
{
	int			a;
	int			b;

	a = crd->x + crd->p - data->plox;
	b = crd->y + crd->k - data->ploy;
	GIMME(0.1);
}

static inline void			check_move(const t_data *restrict data,
							t_mov *restrict mov, t_crd *restrict crd)
{
	double		reach;
	int			k;
	int			p;

	if (TILE == data->op && mov->pc[crd->k][crd->p] == '*' && (mov->hit = true))
		BYEZ;
	else if (TILE == data->self && mov->pc[crd->k][crd->p] == '*')
		if ((mov->anchor += 1) > 1)
			BYEZ;
	if (TILE == '*' && ++mov->contact)
		BYEZ;
	k = -1;
	while (data->map[++k])
	{
		p = -1;
		while (data->map[k][++p])
			if (data->map[k][p] == '*'
				&& (reach = get_reach(data, crd, p, k)) > mov->reach)
				mov->reach = reach;
	}
}

static inline void			mv_prio(t_data *restrict data, t_mov *restrict mov,
							t_crd *restrict crd)
{
	if (mov->contact > mov->prio || mov->reach > mov->prio)
	{
		mov->prio = (mov->contact ? mov->contact : mov->reach);
		mov->x = crd->x - data->plox;
		mov->y = crd->y - data->ploy;
	}
}

void						test_fit(t_data *restrict data, t_mov *restrict mov,
							t_crd *restrict crd)
{
	if (crd->y + data->ply > data->my)
		BYEZ;
	mov->hit = false;
	mov->anchor = 0;
	mov->contact = 0;
	crd->k = data->ploy - 1;
	while (mov->anchor < 2 && mov->hit == false && (size_t)++crd->k < data->ply)
	{
		crd->p = data->plox - 1;
		while (mov->anchor < 2 && (size_t)++crd->p < data->plx)
			check_move(data, mov, crd);
	}
	if (mov->hit == false && mov->anchor == 1
		&& (size_t)(crd->p * crd->k) == data->plx * data->ply)
		mv_prio(data, mov, crd);
	test_fit(data, mov, up_coord(data, mov, crd));
}

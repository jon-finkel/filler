/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 21:33:34 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/02 23:45:55 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

static inline void			big_endian(char **aptr, const int color)
{
	**aptr = (color & 0xff000000) >> 24;
	++*aptr;
	**aptr = (color & 0xff0000) >> 16;
	++*aptr;
	**aptr = (color & 0xff00) >> 8;
	++*aptr;
	**aptr = color & 0xff;
	++*aptr;
}

static inline void			little_endian(char **aptr, const int color)
{
	**aptr = color & 0xff;
	++*aptr;
	**aptr = (color & 0xff00) >> 8;
	++*aptr;
	**aptr = (color & 0xff0000) >> 16;
	++*aptr;
	**aptr = (color & 0xff000000) >> 24;
	++*aptr;
}

inline void					color_square(t_mlx *mlx, const int color)
{
	char		*ptr;
	int			k;
	int			p;

	ptr = mlx->sqr;
	k = -1;
	while (++k < mlx->sqrlen)
	{
		p = -1;
		while (++p < mlx->sl / 4)
		{
			if (mlx->endian)
				big_endian(&ptr, color);
			else
				little_endian(&ptr, color);
		}
	}
}

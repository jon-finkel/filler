/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 18:49:45 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/05 13:17:21 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

static inline void			big_endian(char **aptr, int color, const int x,
							const int y)
{
	if (x > y)
		color += 0x101010;
	**aptr = (color & 0xff000000) >> 24;
	++*aptr;
	**aptr = (color & 0xff0000) >> 16;
	++*aptr;
	**aptr = (color & 0xff00) >> 8;
	++*aptr;
	**aptr = color & 0xff;
	++*aptr;
}

static inline void			little_endian(char **aptr, int color, const int x,
							const int y)
{
	if (x > y)
		color += 0x101010;
	**aptr = color & 0xff;
	++*aptr;
	**aptr = (color & 0xff00) >> 8;
	++*aptr;
	**aptr = (color & 0xff0000) >> 16;
	++*aptr;
	**aptr = (color & 0xff000000) >> 24;
	++*aptr;
}

static inline void			do_colors(const t_mlx *mlx, char *ptr, int color)
{
	int		k;
	int		p;
	int		x;

	x = mlx->sl / 4;
	k = -1;
	while (++k < mlx->sqrlen)
	{
		p = -1;
		while (++p < x)
		{
			if (!p || !k || k == mlx->sqrlen - 1 || p == mlx->sl / 4 - 1)
			{
				if (mlx->endian)
					big_endian(&ptr, 0x2c2c2c, 0, 0);
				else
					little_endian(&ptr, 0x2c2c2c, 0, 0);
			}
			else if (mlx->endian)
				big_endian(&ptr, color, p, k);
			else
				little_endian(&ptr, color, p, k);
		}
	}
}

static inline void			do_clean(const t_mlx *mlx, char *ptr)
{
	int		k;
	int		p;
	int		x;
	int		y;

	x = mlx->sl / 4;
	y = 22;
	k = -1;
	while (++k < y)
	{
		p = -1;
		while (++p < x)
		{
			if (mlx->endian)
				big_endian(&ptr, 0x202020, 0, 0);
			else
				little_endian(&ptr, 0x202020, 0, 0);
		}
	}
}

int							color_squares(t_mlx *mlx)
{
	FAILZ(mlx->bsqr = mlx_new_image(_MLX, mlx->sqrlen, mlx->sqrlen), -1);
	do_colors(mlx, mlx_get_data_addr(mlx->bsqr, &mlx->bppx, &mlx->sl,\
		&mlx->endian), 0x2c2c2c);
	FAILZ(mlx->sqrp1 = mlx_new_image(_MLX, mlx->sqrlen, mlx->sqrlen), -1);
	do_colors(mlx, mlx_get_data_addr(mlx->sqrp1, &mlx->bppx, &mlx->sl,\
		&mlx->endian), _P1C);
	FAILZ(mlx->sqrp2 = mlx_new_image(_MLX, mlx->sqrlen, mlx->sqrlen), -1);
	do_colors(mlx, mlx_get_data_addr(mlx->sqrp2, &mlx->bppx, &mlx->sl,\
		&mlx->endian), _P2C);
	FAILZ(mlx->clean = mlx_new_image(_MLX, WIN_X / 3 * 2, 22), -1);
	do_clean(mlx, mlx_get_data_addr(mlx->clean, &mlx->bppx, &mlx->sl,\
		&mlx->endian));
	KTHXBYE;
}

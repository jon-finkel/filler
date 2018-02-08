/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 18:49:45 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/08 15:25:11 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _GET_ADDR(x) mlx_get_data_addr((x), &mlx->bppx, &mlx->sl, &mlx->endian)

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

static void					do_square(const t_mlx *mlx, char *ptr, int color)
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

static void					do_rectangle(const t_mlx *mlx, char *ptr,
							const int x, const int y)
{
	int				color;
	int				k;
	int				p;
	static int		n = 0;

	if (n == 1 || n == 2)
		color = (n == 1 ? _P1C : _P2C);
	else
		color = (!n ? 0x1b0331 : 0x22073a);
	k = -1;
	while (++k < y)
	{
		p = -1;
		while (++p < x)
		{
			if (mlx->endian)
				big_endian(&ptr, color, 0, 0);
			else
				little_endian(&ptr, color, 0, 0);
		}
	}
	++n;
}

int							color_squares(t_mlx *mlx)
{
	FAILZ(mlx->bsqr = mlx_new_image(_MLX, mlx->sqrlen, mlx->sqrlen), -1);
	do_square(mlx, _GET_ADDR(mlx->bsqr), 0x2c2c2c);
	FAILZ(mlx->sqrp1 = mlx_new_image(_MLX, mlx->sqrlen, mlx->sqrlen), -1);
	do_square(mlx, _GET_ADDR(mlx->sqrp1), _P1C);
	FAILZ(mlx->sqrp2 = mlx_new_image(_MLX, mlx->sqrlen, mlx->sqrlen), -1);
	do_square(mlx, _GET_ADDR(mlx->sqrp2), _P2C);
	FAILZ(mlx->bg = mlx_new_image(_MLX, WIN_X / 2, WIN_X / 2), -1);
	do_rectangle(mlx, _GET_ADDR(mlx->bg), WIN_X / 2, WIN_X / 2);
	FAILZ(mlx->clean1 = mlx_new_image(_MLX, 150, 30), -1);
	do_rectangle(mlx, _GET_ADDR(mlx->clean1), 150, 30);
	FAILZ(mlx->clean2 = mlx_new_image(_MLX, 150, 30), -1);
	do_rectangle(mlx, _GET_ADDR(mlx->clean2), 150, 30);
	FAILZ(mlx->bclean = mlx_new_image(_MLX, 100, 100), -1);
	do_rectangle(mlx, _GET_ADDR(mlx->bclean), 100, 100);
	KTHXBYE;
}

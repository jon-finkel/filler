/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 18:49:45 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/08 11:51:23 by nfinkel          ###   ########.fr       */
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

static inline void			do_clean(const t_mlx *mlx, char *ptr, const int x,
							const int y)
{
	int				color;
	int				k;
	int				p;
	static int		n = 0;

	if (!n)
		color = 0x1b0331;
	else
		color = (n == 1 ? _P1C : _P2C);
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
	do_colors(mlx, mlx_get_data_addr(mlx->bsqr, &mlx->bppx, &mlx->sl,\
		&mlx->endian), 0x2c2c2c);
	FAILZ(mlx->sqrp1 = mlx_new_image(_MLX, mlx->sqrlen, mlx->sqrlen), -1);
	do_colors(mlx, mlx_get_data_addr(mlx->sqrp1, &mlx->bppx, &mlx->sl,\
		&mlx->endian), _P1C);
	FAILZ(mlx->sqrp2 = mlx_new_image(_MLX, mlx->sqrlen, mlx->sqrlen), -1);
	do_colors(mlx, mlx_get_data_addr(mlx->sqrp2, &mlx->bppx, &mlx->sl,\
		&mlx->endian), _P2C);
	FAILZ(mlx->bg = mlx_new_image(_MLX, WIN_X / 2, WIN_X / 2), -1);
	do_clean(mlx, mlx_get_data_addr(mlx->bg, &mlx->bppx, &mlx->sl,\
		&mlx->endian), WIN_X / 2, WIN_X / 2);
	FAILZ(mlx->clean1 = mlx_new_image(_MLX, 150, 30), -1);
	do_clean(mlx, mlx_get_data_addr(mlx->clean1, &mlx->bppx, &mlx->sl,\
		&mlx->endian), 150, 30);
	FAILZ(mlx->clean2 = mlx_new_image(_MLX, 150, 30), -1);
	do_clean(mlx, mlx_get_data_addr(mlx->clean2, &mlx->bppx, &mlx->sl,\
		&mlx->endian), 150, 30);
	KTHXBYE;
}

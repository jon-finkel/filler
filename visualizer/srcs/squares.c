/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 18:49:45 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/03 19:30:15 by nfinkel          ###   ########.fr       */
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

static inline void			do_colors(t_mlx *mlx, char *ptr, const int color)
{
	int			k;
	int			p;

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

void						color_squares(t_mlx *mlx)
{
	KEEPATITBRA(mlx->bsqr = mlx_new_image(_MLX, mlx->sqrlen, mlx->sqrlen));
	do_colors(mlx, mlx_get_data_addr(mlx->bsqr, &mlx->bppx, &mlx->sl,\
		&mlx->endian), 0x2c2c2c);
	KEEPATITBRA(mlx->sqrp1 = mlx_new_image(_MLX, mlx->sqrlen, mlx->sqrlen));
	do_colors(mlx, mlx_get_data_addr(mlx->sqrp1, &mlx->bppx, &mlx->sl,\
		&mlx->endian), _P1C);
	KEEPATITBRA(mlx->sqrp2 = mlx_new_image(_MLX, mlx->sqrlen, mlx->sqrlen));
	do_colors(mlx, mlx_get_data_addr(mlx->sqrp2, &mlx->bppx, &mlx->sl,\
		&mlx->endian), _P2C);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strhdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:29:27 by fsabatie          #+#    #+#             */
/*   Updated: 2018/02/10 15:26:06 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _BPATH "./visualizer/ressources/letters/"
#define _SPATH "./visualizer/ressources/letters/small/"
#define BUFF_SIZE 512

t_vector				g_vec_null = {NULL, 0, 0, sizeof(void *)};
t_vector				*g_vec = &g_vec_null;

/*
** Padding for font, 6th row is for digits,
** 8th and 11th rows for 'a' - 'm',
** 9th and 12th rows for 'n' - 'z'.
*/
static const int		g_pad[128] =
{
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
	5, 5, 5, 5, 5, 5, 5,
	30, 30, 30, 30, 30, 30, 30, 30, 20, 25, 30, 30, 30,
	30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
	5, 5, 5, 5, 5, 5,
	30, 30, 30, 30, 30, 30, 30, 30, 20, 25, 30, 30, 30,
	30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30,
	5, 5, 5, 5, 5
};

const inline t_mlx			*put_swstr(const t_mlx *mlx, const char *str, int x,
							const int y)
{
	int		k;
	int		size;

	k = 9;
	size = (WIN_X == 1920) ? 1 : 2;
	while (*str && k)
	{
		--k;
		if (k)
			mlx_put_image_to_window(_MLX, _WIN, mlx->font[(int)*str], x, y);
		else
			mlx_put_image_to_window(_MLX, _WIN, mlx->font[0], x, y);
		x += g_pad[(k ? (int)*str : 0)] / size;
		++str;
	}
	GIMME(mlx);
}

int							do_font(t_mlx *mlx)
{
	char		path[BUFF_SIZE];
	char		*s;
	int			k;
	int			x;
	int			y;

	s = (WIN_X == 1920 ? _BPATH : _SPATH);
	k = -1;
	while (++k < 128)
	{
		if (k >= 'a' && k <= 'z')
			ft_snprintf(path, BUFF_SIZE, "%s%c.xpm", s, k);
		else if (k >= 'A' && k <= 'Z')
			ft_snprintf(path, BUFF_SIZE, "%s%c.xpm", s, k + 32);
		else if (k >= '0' && k <= '9')
			ft_snprintf(path, BUFF_SIZE, "%s%d.xpm", s, k - '0');
		else
			ft_snprintf(path, BUFF_SIZE, "%sqmark.xpm", s);
		*(void **)ft_vecpush(g_vec) = mlx_xpm_file_to_image(_MLX, path, &x, &y);
	}
	mlx->font = g_vec->buff;
	KTHXBYE;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strhdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsabatie <fsabatie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:29:27 by fsabatie          #+#    #+#             */
/*   Updated: 2018/02/06 10:09:02 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define BUFF_SIZE 512
#define _LPATH "./ressources/letters/" // Cette ligne marche chez nfinkel.
//#define _LPATH "./visualizer/ressources/letters/" // Cette ligne marche chez fsabatie.

t_vector				g_vec_null = {NULL, 0, 0, sizeof(char *)};
t_vector				*g_vec = &g_vec_null;
/*
** Padding for font, 6th rows is for digits,
** 8th and 11th for 'a' - 'm',
** 9th and 12th for 'n' - 'z'.
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

	k = 9;
	while (*str && k)
	{
		--k;
		if (k)
			mlx_put_image_to_window(_MLX, _WIN, mlx->font[(int)*str], x, y);
		else
			mlx_put_image_to_window(_MLX, _WIN, mlx->font[0], x, y);
		x += g_pad[(k ? (int)*str : 0)];
		++str;
	}
	GIMME(mlx);
}

int							do_font(t_mlx *mlx)
{
	char		path[BUFF_SIZE];
	int			k;
	int			x;
	int			y;
	void		*xpm;

	k = -1;
	while (++k < 128)
	{
		if (k >= 'a' && k <= 'z')
			ft_snprintf(path, BUFF_SIZE, "%s%c.xpm", _LPATH, k);
		else if (k >= 'A' && k <= 'Z')
			ft_snprintf(path, BUFF_SIZE, "%s%c.xpm", _LPATH, k + 32);
		else if (k >= '0' && k <= '9')
			ft_snprintf(path, BUFF_SIZE, "%s%d.xpm", _LPATH, k - '0');
		else
			ft_snprintf(path, BUFF_SIZE, "%sdot.xpm", _LPATH);
		if (!(xpm = mlx_xpm_file_to_image(_MLX, path, &x, &y)))
			ft_fatal("could not locate the xpm file");
		FAILZ(*(void **)ft_vecpush(g_vec) = xpm, -1);
	}
	mlx->font = g_vec->buff;
	KTHXBYE;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:29:27 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/01 19:43:27 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _MAP_FILE "map.xpm"
#define _TITLE "Filler visualizer, by nfinkel"

static t_mlx			*init_mlx(t_mlx *mlx)
{
	int		k;
	int		p;

	FAILZ(mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx)), NULL);
	FAILZ(_MLX = mlx_init(), NULL);
	FAILZ(_WIN = mlx_new_window(_MLX, WIN_X, WIN_Y, _TITLE), NULL);
	k = WIN_PAD - 1;
	while (++k < WIN_Y - WIN_PAD)
	{
		p = (WIN_X / 2) + WIN_PAD - 1;
		while (++p < WIN_X - WIN_PAD)
			mlx_pixel_put(_MLX, _WIN, p, k, 0x202020);
	}
	FAILZ(mlx->xpm = mlx_xpm_file_to_image(_MLX, _MAP_FILE, &k, &p), NULL);
	FAILZ(mlx_put_image_to_window(_MLX, _WIN, mlx->xpm, 0, 0), NULL);
	GIMME(mlx);
}

int						main(void)
{
	t_mlx		*mlx;

	IMOUTTAHERE(mlx = init_mlx(NULL));
	mlx_loop(_MLX);
	KTHXBYE;
}

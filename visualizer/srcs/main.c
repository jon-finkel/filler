/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:29:27 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/01 16:48:05 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define MAP_FILE "map.xpm"
#define TITLE "Filler visualizer, by nfinkel"

static t_mlx			*init_mlx(t_mlx *mlx)
{
	int		x;
	int		y;

	FAILZ(mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx)), NULL);
	FAILZ(mlx->mlx = mlx_init(), NULL);
	FAILZ(mlx->win = mlx_new_window(MLX, WIN_X, WIN_Y, TITLE), NULL);
	FAILZ(mlx->xpm = mlx_xpm_file_to_image(MLX, MAP_FILE, &x, &y), NULL);
	FAILZ(mlx_put_image_to_window(MLX, mlx->win, mlx->xpm, 0, 0), NULL);
	GIMME(mlx);
}

int						main(void)
{
	t_mlx		*mlx;

	IMOUTTAHERE(mlx = init_mlx(NULL));
	mlx_loop(MLX);
	KTHXBYE;
}

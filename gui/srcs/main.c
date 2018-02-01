/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 00:10:40 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/01 13:49:26 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gui.h"

#define MLX (mlx->id)
#define PATH "../ressources/map.xpm"
#define TITLE_WIN "Filler gui"

static t_mlx			*init_mlx(t_mlx *mlx)
{
	FAILZ(mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx)), NULL);
	KEEPATITBRA(mlx->id = mlx_init());
	mlx->x = WIN_X;
	mlx->y = WIN_Y;
	KEEPATITBRA(mlx->win_ptr = mlx_new_window(MLX, WIN_X, WIN_Y, TITLE_WIN));
	GIMME(mlx);
}

int			main(void)
{
	t_mlx		*mlx;

	if (!(mlx = init_mlx(NULL)))
		ft_fatal("General error");
	mlx_loop(MLX);
	KTHXBYE;
}

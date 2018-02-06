/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 17:15:39 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/05 20:52:09 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _RES "running..."
#define _PAUSE "paused"

int							hook_key(int key, t_mlx *mlx)
{
	if (key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	else if (key == MLX_KEY_SPACE && mlx->mouse)
		mlx->play = (mlx->play == false ? true : false);
	KTHXBYE;
}

static inline void			do_grid(t_mlx *mlx, const int y)
{
	int		k;

	k = -1;
	while (++k < mlx->map_x)
		mlx_put_image_to_window(_MLX, _WIN, mlx->bsqr, _PADX + _ADJUST(k),\
			_PADY + _ADJUST(y));
}

int							hook_loop(t_mlx *mlx)
{
	char			*line;
	static int		p1score = 0;
	static int		p2score = 0;
	static int		y = 0;

	if (mlx->mouse && y < mlx->map_y)
		do_grid(mlx, y++);
	else if (y == mlx->map_y && ++y && init_map(mlx) == -1)
		ft_fatal("allocation failed.");
	else if (mlx->mouse && mlx->play)
	{
		if (get_next_line(STDIN_FILENO, &line) < 0)
			ft_fatal("allocation failed.");
		else if (line[0] == ' ')
			if (do_map(mlx, &p1score, &p2score) == -1)
				ft_fatal("allocation failed.");
		ft_strdel(&line);
	}
	KTHXBYE;
}

int							hook_mouse(int button, int x, int y, t_mlx *mlx)
{
	(void)button;
	if (!mlx->mouse && x >= 770 && x <= 1130 && y >= 140 && y <= 510)
	{
		mlx_put_image_to_window(_MLX, _WIN, mlx->bg, WIN_X / 4, 0);
		mlx->mouse = true;
	}
	KTHXBYE;
}

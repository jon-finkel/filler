/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 17:15:39 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/08 15:50:44 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _LIGHT "./visualizer/ressources/assets/LSWLarge.xpm"
#define _DARK "./visualizer/ressources/assets/DSWLarge.xpm"
#define _LIGHT_SMALL "./visualizer/ressources/assets/LSWSmall.xpm"
#define _DARK_SMALL "./visualizer/ressources/assets/DSWSmall.xpm"
#define _PAUSE mlx->bpause
#define _PLAY mlx->bplay

int							hook_key(int key, t_mlx *mlx)
{
	if (key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	else if (key == MLX_KEY_SPACE && mlx->mouse)
	{
		mlx_put_image_to_window(_MLX, _WIN, mlx->bclean, WIN_X / 2 - 50,\
			WIN_X / 2 + 5);
		mlx_put_image_to_window(_MLX, _WIN, mlx->play ? _PAUSE: _PLAY, 0, 0);
		mlx->play = (mlx->play == false ? true : false);
	}
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

static inline void			do_winner(t_mlx *mlx)
{
	char		*path;
	int			x;
	int			y;
	void		*xpm;

	if (mlx->p1score > mlx->p2score)
		path = (WIN_X == 1920 ? _LIGHT : _LIGHT_SMALL);
	else
		path = (WIN_X == 1920 ? _DARK : _DARK_SMALL);
	xpm = mlx_xpm_file_to_image(_MLX, path, &x, &y);
	mlx_put_image_to_window(_MLX, _WIN, xpm, 0, 0);
}

int							hook_loop(t_mlx *mlx)
{
	static bool		end = false;
	char			*line;
	int				ret;
	static int		y = 0;

	if (mlx->mouse && y < mlx->map_y)
		do_grid(mlx, y++);
	else if (y == mlx->map_y && ++y && init_map(mlx) == -1)
		ft_fatal("allocation failed");
	else if (!end && mlx->mouse && mlx->play)
	{
		if ((ret = get_next_line(STDIN_FILENO, &line)) < 0)
			ft_fatal("allocation failed");
		else if (line[0] == ' '
			&& do_map(mlx, &mlx->p1score, &mlx->p2score) == -1)
			ft_fatal("allocation failed");
		else if (!ret && (end = true))
			do_winner(mlx);
		ft_strdel(&line);
	}
	KTHXBYE;
}

int							hook_mouse(int button, int x, int y, t_mlx *mlx)
{
	(void)button;
	if (!mlx->mouse)
		if ((WIN_X == 1920 && x >= 770 && x <= 1130 && y >= 140 && y <= 510)
			|| (WIN_X == 1200 && x >= 485 && x <= 710 && y >= 90 && y <= 315))
	{
		mlx_put_image_to_window(_MLX, _WIN, mlx->bg, WIN_X / 4, 0);
		mlx->mouse = true;
	}
	KTHXBYE;
}

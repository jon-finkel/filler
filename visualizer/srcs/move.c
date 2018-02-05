/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:34:00 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/05 13:34:50 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _DO_TILE(x, y, z) mlx_put_image_to_window(_MLX, _WIN, x, y, z)

inline int					init_map(const t_mlx *mlx)
{
	char			*line;
	int				k;
	int				p;

	k = -2;
	while (++k < mlx->map_y)
	{
		EPICFAILZ(get_next_line(STDIN_FILENO, &line), -1);
		p = -1;
		while (++p < mlx->map_x)
			if (line[p + 4] == 'O' || line[p + 4] == 'X')
				_DO_TILE((line[p + 4] == 'O' ? _P1 : _P2),\
					_ADJUST(p, mlx->pad_x), _ADJUST(k, mlx->pad_y));
		ft_strdel(&line);
	}
	KTHXBYE;
}

static inline int			output_score(const t_mlx *mlx, const int p1s,
							const int p2s)
{
	char		*s;

	s = ft_itoa(p1s);
	mlx_put_image_to_window(_MLX, _WIN, mlx->clean, WIN_X - 90, _P1Y);
	mlx_string_put(_MLX, _WIN, WIN_X - 90, _P1Y, _P1C, s);
	free(s);
	s = ft_itoa(p2s);
	mlx_put_image_to_window(_MLX, _WIN, mlx->clean, WIN_X - 90, _P2Y);
	mlx_string_put(_MLX, _WIN, WIN_X - 90, _P2Y, _P2C, s);
	KTHXBYE;
}

int							do_map(t_mlx *mlx, int *p1score, int *p2score)
{
	bool		score;
	char		*line;
	int			k;
	int			p;

	k = -1;
	score = false;
	while (++k < mlx->map_y)
	{
		EPICFAILZ(get_next_line(STDIN_FILENO, &line), -1);
		p = -1;
		while (++p < mlx->map_x)
			if (line[p + 4] == 'o' || line[p + 4] == 'x')
			{
				_DO_TILE((line[p + 4] == 'o' ? _P1 : _P2),\
					_ADJUST(p, mlx->pad_x), _ADJUST(k, mlx->pad_y));
				if (score == false && line[p + 4] == 'o' && (score = true))
					++*p1score;
				else if (score == false && (score = true))
					++*p2score;
			}
		ft_strdel(&line);
	}
	GIMME(output_score(mlx, *p1score, *p2score));
}

inline int					do_bars(void *restrict mlx, void *restrict win)
{
	int		k;
	int		p;

	k = _P1Y + 40 - 1;
	while (++k < _P1Y + 60)
	{
		p = _PX - 1;
		while (++p < WIN_X - 50)
			mlx_pixel_put(mlx, win, p, k, _P1C - 0x202020);
	}
	k = _P2Y + 40 - 1;
	while (++k < _P2Y + 60)
	{
		p = _PX - 1;
		while (++p < WIN_X - 50)
			mlx_pixel_put(mlx, win, p, k, _P2C - 0x202020);
	}
	KTHXBYE;
}

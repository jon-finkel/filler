/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:34:00 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/04 21:54:59 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _DO_TILE(x, y, z) mlx_put_image_to_window(_MLX, _WIN, x, y, z)

int					init_map(const t_mlx *mlx)
{
	char			*line;
	int				k;
	int				p;

	k = -1;
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

static int			output_score(const t_mlx *mlx, const int p1s, const int p2s)
{
	(void)mlx;
	(void)p1s;
	(void)p2s;
	KTHXBYE;
}

int					do_map(t_mlx *mlx, int *p1score, int *p2score)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:34:00 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/04 20:58:26 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _DLIST ((struct s_move *)(dlist->data))
#define _DO_TILE(x, y, z) mlx_put_image_to_window(_MLX, _WIN, x, y, z)

static inline void			input_move(t_dlist *dlist, const t_mlx *mlx,
							const char *line, const int y)
{
	int		x;
	int		k;

	x = -1;
	k = -1;
	if (dlist->next && dlist->next->next)
		_DLIST->score = ((struct s_move *)(dlist->next->next))->score;
	while (++x < mlx->map_x)
		if (line[x + 4] == 'o' || line[x + 4] == 'x')
		{
			if (!_DLIST->player)
				_DLIST->player = (line[x + 4] == 'o' ? 'O' : 'X');
			_DLIST->score += 1;
			++_DLIST->nb;
			_DLIST->crd[++k][0] = x;
			_DLIST->crd[k][1] = y;
			_DO_TILE((line[x + 4] == 'o' ? _P1 : _P2), _ADJUST(x, mlx->pad_x),\
				_ADJUST(y, mlx->pad_y));
		}
}

int							do_map(t_dlist **adlst, t_mlx *mlx)
{
	char				*line;
	int					k;
	struct s_move		*move;
	t_dlist				*dlist;

	FAILZ(move = (struct s_move *)ft_memalloc(sizeof(struct s_move)), -1);
	FAILZ(dlist = ft_dlstnew(move, sizeof(struct s_move)), -1);
	ft_dlstadd(adlst, dlist);
	dlist = *adlst;
	ft_memdel((void **)&move);
	k = -1;
	while (++k < mlx->map_y)
	{
		EPICFAILZ(get_next_line(STDIN_FILENO, &line), -1);
ft_printf("%s\n", line);
		input_move(dlist, mlx, line, k);
		ft_strdel(&line);
	}
	KTHXBYE;
}

t_dlist						*init_dlist(t_dlist *dlist, const t_mlx *mlx)
{
	char				*line;
	int					k;
	int					p;
	struct s_move		*move;

	FAILZ(move = (struct s_move *)ft_memalloc(sizeof(struct s_move)), NULL);
	FAILZ(dlist = ft_dlstnew(move, sizeof(struct s_move)), NULL);
	ft_memdel((void **)&move);
	k = -1;
	while (++k < mlx->map_y)
	{
		EPICFAILZ(get_next_line(STDIN_FILENO, &line), NULL);
		p = -1;
		while (++p < mlx->map_x)
			if (line[p + 4] == 'O' || line[p + 4] == 'X')
				_DO_TILE((line[p + 4] == 'O' ? _P1 : _P2),\
					_ADJUST(p, mlx->pad_x), _ADJUST(k, mlx->pad_y));
		ft_strdel(&line);
	}
	GIMME(dlist);
}

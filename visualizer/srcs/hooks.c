/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 17:15:39 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/04 20:55:35 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _DLIST ((struct s_move *)(data->dlist->data))
#define _DO_TILE(x, y, z) mlx_put_image_to_window(_MLX, _WIN, x, y, z)

static inline void			do_rewind(t_data *data)
{
	int8_t		k;
	t_mlx		*mlx;

	if (!data->dlist->next)
		BYEZ;
	mlx = data->mlx;
	mlx->play = false;
	k = -1;
	while ((uint8_t)++k < _DLIST->nb)
		_DO_TILE(_SQR, _ADJUST(_DLIST->crd[k][0], mlx->pad_x),\
			_ADJUST(_DLIST->crd[k][1], mlx->pad_y));
	data->dlist = data->dlist->next;
}

static inline void			do_forward(t_data *data)
{
	int8_t		k;
	t_mlx		*mlx;

	if (!data->dlist->prev)
		BYEZ;
	data->dlist = data->dlist->prev;
	mlx = data->mlx;
	mlx->play = false;
	k = -1;
	while ((uint8_t)++k < _DLIST->nb)
		_DO_TILE(_DLIST->player == 'O' ? _P1 : _P2,\
			_ADJUST(_DLIST->crd[k][0], mlx->pad_x),\
			_ADJUST(_DLIST->crd[k][1], mlx->pad_y));
}

int							hook_key(int key, t_data *data)
{
	if (key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	else if (key == MLX_KEY_SPACE)
		data->mlx->play = (data->mlx->play == false ? true : false);
	else if (key == MLX_KEY_L_ARROW)
		do_rewind(data);
	else if (key == MLX_KEY_R_ARROW)
		do_forward(data);
	KTHXBYE;
}

int							hook_loop(t_data *data)
{
	char		*line;
	int			ret;

	if (data->mlx->play)
	{
		ret = get_next_line(STDIN_FILENO, &line);
		if (ret < 0)
			ft_fatal("allocation failed.");
		else if (line[0] == ' ')
			if (do_map(&data->dlist, data->mlx) == -1)
				ft_fatal("allocation failed.");
		ft_strdel(&line);
	}
	KTHXBYE;
}

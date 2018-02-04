/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 17:15:39 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/04 21:48:12 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

int							hook_key(int key, t_mlx *mlx)
{
	if (key == MLX_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	else if (key == MLX_KEY_SPACE)
		mlx->play = (mlx->play == false ? true : false);
	KTHXBYE;
}

int							hook_loop(t_mlx *mlx)
{
	char			*line;
	int				ret;
	static int		p1score = 0;
	static int		p2score = 0;

	if (mlx->play)
	{
		ret = get_next_line(STDIN_FILENO, &line);
		if (ret < 0)
			ft_fatal("allocation failed.");
		else if (line[0] == ' ')
			if (do_map(mlx, &p1score, &p2score) == -1)
				ft_fatal("allocation failed.");
		ft_strdel(&line);
	}
	KTHXBYE;
}

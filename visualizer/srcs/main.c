/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:29:27 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/05 16:58:42 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _MAP_FILE "./ressources/map.xpm"
#define _TITLE "Filler visualizer, by nfinkel and fsabatie"
#define BUFF_SIZE 32

static inline t_mlx			*get_sqrlen(t_mlx *mlx)
{
	size_t		nb;
	size_t		width;

	nb = MAX(mlx->map_x, mlx->map_y);
	width = WIN_X / 2;
	mlx->sqrlen = (width - (nb - 1)) / nb;
	mlx->pad_x = (width - ((mlx->map_x * mlx->sqrlen) + mlx->map_x - 1)) / 2;
	mlx->pad_y = (width - ((mlx->map_y * mlx->sqrlen) + mlx->map_y - 1)) / 2;
	GIMME(mlx);
}

static t_mlx				*output_grid(t_mlx *mlx)
{
	char		*line;
	int			k;
	int			p;

	if (!mlx)
		ZOMG;
	EPICFAILZ(get_next_line(STDIN_FILENO, &line), NULL);
	mlx->map_y = ft_atoi(line + 8);
	mlx->map_x = ft_atoi(line + ft_intlen(mlx->map_y) + 9);
	if (mlx->map_x > 100 || mlx->map_y > 100)
		ft_fatal("map size isn't supported by visualizer");
	ft_strdel(&line);
	EPICFAILZ(color_squares(get_sqrlen(mlx)), NULL);
	k = -1;
	while (++k < mlx->map_y)
	{
		p = -1;
		while (++p < mlx->map_x)
			mlx_put_image_to_window(_MLX, _WIN, mlx->bsqr, _PADX + _ADJUST(p),\
				_PADY + _ADJUST(k));
	}
	GIMME(mlx);
}

static t_mlx				*do_players(t_mlx *mlx)
{
	char		p1n[BUFF_SIZE];
	char		p2n[BUFF_SIZE];
	char		*line;
	int			k;

	k = 10;
	while (--k)
	{
		EPICFAILZ(get_next_line(STDIN_FILENO, &line), NULL);
		if (line[0] == '$' && line[10] == '1')
			ft_snprintf(p1n, BUFF_SIZE, "%s", ft_strrchr(line, '/') + 1);
		else if (line[0] == '$' && line[10] == '2')
			ft_snprintf(p2n, BUFF_SIZE, "%s", ft_strrchr(line, '/') + 1);
		else if (line[0] == '.' || ft_strequ(line, "error:"))
			errhdl(mlx, line);
		else if (line[0] != 'l' && line[0] != '#' && line[0] != 'P')
			ft_fatal("wrong input");
		ft_strdel(&line);
	}
	*ft_strchr(&p1n[0], '.') = '\0';
	*ft_strchr(&p2n[0], '.') = '\0';
//	mlx_string_put(_MLX, _WIN, _PX, _P1Y, _P1C, p1n);
//	mlx_string_put(_MLX, _WIN, _PX, _P2Y, _P2C, p2n);
	GIMME(mlx);
}

int							main(void)
{
	int			k;
	int			p;
	t_mlx		*mlx;
	void		*xpm;

	if (!(mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx))) || !(_MLX = mlx_init())
		|| (!(_WIN = mlx_new_window(_MLX, WIN_X, WIN_Y, _TITLE))))
		ft_fatal("allocation failed.");
	if (!(xpm = mlx_xpm_file_to_image(_MLX, _MAP_FILE, &k, &p)))
		ft_fatal("could not locate xpm file, restart from filler directory");
	mlx_put_image_to_window(_MLX, _WIN, xpm, 0, 0);
	if (!output_grid(do_players(mlx)) || init_map(mlx) < 0)
		ft_fatal("allocation failed.");
	mlx_key_hook(_WIN, &hook_key, mlx);
	mlx_loop_hook(_MLX, &hook_loop, mlx);
	mlx_loop(_MLX);
	KTHXBYE;
}

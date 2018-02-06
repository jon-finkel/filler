/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:29:27 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/06 16:03:32 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _MAP_FILE "./ressources/map.xpm" // Cette ligne marche chez nfinkel.
//#define _MAP_FILE "visualizer/ressources/map.xpm" // Cette ligne marche chez fsabatie.
#define _TITLE "Filler visualizer, by nfinkel and fsabatie"
#define BUFF_SIZE 32

static t_mlx				*output_grid(t_mlx *mlx)
{
	char		*line;
	size_t		nb;
	size_t		width;

	if (!mlx)
		ZOMG;
	EPICFAILZ(get_next_line(STDIN_FILENO, &line), NULL);
	mlx->map_y = ft_atoi(line + 8);
	mlx->map_x = ft_atoi(line + ft_intlen(mlx->map_y) + 9);
	if (mlx->map_x > 100 || mlx->map_y > 100)
		ft_fatal("map size isn't supported by visualizer");
	ft_strdel(&line);
	nb = MAX(mlx->map_x, mlx->map_y);
	width = WIN_X / 2;
	mlx->sqrlen = (width - (nb - 1)) / nb;
	mlx->pad_x = (width - ((mlx->map_x * mlx->sqrlen) + mlx->map_x - 1)) / 2;
	mlx->pad_y = (width - ((mlx->map_y * mlx->sqrlen) + mlx->map_y - 1)) / 2;
	EPICFAILZ(color_squares(mlx), NULL);
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
	EPICFAILZ(do_font(mlx), NULL);
	GIMME((t_mlx *)put_swstr(put_swstr(put_swstr(put_swstr(mlx, p1n, _P1X,\
		_PY), p2n, _P2X, _PY), "0", _P1S, _PXS), "0", _P2S, _PXS));
	GIMME(mlx);
}

static inline int			usage(void)
{
	ft_putendl("Usage: <filler command> | ./visualizer/visualizer [-low]\n"\
		"-low: use 1200x675 resolution");
	KTHXBYE;
}

static inline void			display_board(t_mlx *mlx, int x, int y)
{
	void		*xpm;

	mlx->win_x = x;
	mlx->win_y = y;
	if (!(xpm = mlx_xpm_file_to_image(_MLX, _MAP_FILE, &x, &y)))
		ft_fatal("could not locate xpm file, restart from filler directory");
	mlx_put_image_to_window(_MLX, _WIN, xpm, 0, 0);
	if (!output_grid(do_players(mlx)))
		ft_fatal("allocation failed.");
	mlx_destroy_image(_MLX, xpm);
}

int							main(int argc, const char *argv[])
{
	int			x;
	int			y;
	t_mlx		*mlx;

	if (argc > 1)
	{
		if (ft_strequ(argv[1], "-low"))
			x = 1200;
		else
			GIMME(usage());
	}
	else
		x = 1920;
	y = (x == 1920 ? 1080 : 675);
	if (!(mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx))) || !(_MLX = mlx_init())
		|| (!(_WIN = mlx_new_window(_MLX, x, y, _TITLE))))
		ft_fatal("allocation failed.");
	display_board(mlx, x, y);
	mlx_mouse_hook(_WIN, &hook_mouse, mlx);
	mlx_key_hook(_WIN, &hook_key, mlx);
	mlx_loop_hook(_MLX, &hook_loop, mlx);
	GIMME(mlx_loop(_MLX));
}

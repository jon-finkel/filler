/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:29:27 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/03 23:09:45 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"
#define _MAP_FILE "map.xpm"
#define _TITLE "Filler visualizer, by nfinkel"
#define BUFF_SIZE 32

static inline t_mlx			*get_sqrlen(t_mlx *mlx)
{
	size_t		nb;

	nb = MAX(mlx->map_x, mlx->map_y);
	mlx->sqrlen = (WIN_Y - (nb - 1)) / nb;
	while (nb * mlx->sqrlen + (mlx->space + 1) * (nb - 1) <= WIN_Y)
		++mlx->space;
	mlx->pad_x = (WIN_X / 2 - ((mlx->map_x * mlx->sqrlen)\
		+ mlx->space * (mlx->map_x - 1))) / 2;
	mlx->pad_y = (WIN_Y - ((mlx->map_y * mlx->sqrlen)\
		+ mlx->space * (mlx->map_y - 1))) / 2;
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
	ft_strdel(&line);
	color_squares(get_sqrlen(mlx));
	k = -1;
	while (++k < mlx->map_y)
	{
		p = -1;
		while (++p < mlx->map_x)
			mlx_put_image_to_window(_MLX, _WIN, mlx->bsqr,\
				_ADJUST(p, mlx->pad_x), _ADJUST(k, mlx->pad_y));
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
		ft_strdel(&line);
	}
	*ft_strchr(&p1n[0], '.') = '\0';
	*ft_strchr(&p2n[0], '.') = '\0';
//	mlx_string_put(_MLX, _WIN, _PX, _P1Y, _P1C, p1n);
//	mlx_string_put(_MLX, _WIN, _PX, _P2Y, _P2C, p2n);
	GIMME(mlx);
}

static t_mlx				*init_mlx(t_mlx *mlx)
{
	int			k;
	int			p;
	void		*xpm;

	FAILZ(mlx = (t_mlx *)ft_memalloc(sizeof(t_mlx)), NULL);
	FAILZ(_MLX = mlx_init(), NULL);
	FAILZ(_WIN = mlx_new_window(_MLX, WIN_X, WIN_Y, _TITLE), NULL);
	k = -1;
	while (++k < WIN_Y)
	{
		p = (WIN_X / 2) - 1;
		while (++p < WIN_X)
			mlx_pixel_put(_MLX, _WIN, p, k, 0x00202020);
	}
	FAILZ(xpm = mlx_xpm_file_to_image(_MLX, _MAP_FILE, &k, &p), NULL);
	mlx_put_image_to_window(_MLX, _WIN, xpm, 0, 0);
	GIMME(mlx);
}

int							main(void)
{
	char		*line;
	int			ret;
	t_dlist		*dlist;
	t_mlx		*mlx;

	if (!(mlx = init_mlx(NULL)) || !output_grid(do_players(mlx))
		|| !(dlist = init_dlist(NULL, mlx)))
		ft_fatal("allocation failed.");
	while ((ret = get_next_line(STDIN_FILENO, &line)))
	{
		if (ret < 0)
			ft_fatal("allocation failed.");
		else if (line[0] == ' ')
			if (do_map(&dlist, mlx) == -1)
				ft_fatal("allocation failed.");
		ft_strdel(&line);
	}
	mlx_loop(_MLX);
	KTHXBYE;
}

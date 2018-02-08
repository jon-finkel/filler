/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:23:16 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/08 11:51:52 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "../../libft/includes/libft.h"
# include "../../libft/includes/mlx_keys.h"
# include "../ressources/mlx/mlx.h"

# define WIN_X mlx->win_x
# define WIN_Y mlx->win_y
# define _ADJUST(x) ((x) * (mlx->sqrlen + 1))
# define _PADX WIN_X / 4 + mlx->pad_x
# define _PADY mlx->pad_y
# define _MLX mlx->mlx
# define _WIN mlx->win_ptr
# define _P1C 0x2e99e3
# define _P2C 0xb71345
# define _P1S (WIN_X == 1920 ? 155 : 95)
# define _P2S (WIN_X == 1920 ? 1555 : 990)
# define _PYS (WIN_X == 1920 ? 820 : 510)

typedef struct		s_mlx
{
	bool			mouse;
	bool			play;
	int				p1score;
	int				p2score;
	struct			s_sqr
	{
		int			__bppx;
		int			__sl;
		int			__endian;
		int			__sqrlen;
	}				__sqr;
	struct			s_window
	{
		short		__win_x;
		short		__win_y;
		uint8_t		__map_x;
		uint8_t		__map_y;
		uint8_t		__pad_x;
		uint8_t		__pad_y;
	}				__win;
	void			*bg;
	void			*bsqr;
	void			*clean1;
	void			*clean2;
	void			*mlx;
	void			*sqrp1;
	void			*sqrp2;
	void			*win_ptr;
	void			**font;
}					t_mlx;

#define bppx __sqr.__bppx
#define endian __sqr.__endian
#define sl __sqr.__sl
#define sqrlen __sqr.__sqrlen
#define win_x __win.__win_x
#define win_y __win.__win_y
#define map_x __win.__map_x
#define map_y __win.__map_y
#define pad_x __win.__pad_x
#define pad_y __win.__pad_y

int					color_squares(t_mlx *mlx);
int					do_font(t_mlx *mlx);
int					do_map(t_mlx *mlx, int *p1score, int *p2score);
void				errhdl(t_mlx *mlx, char *line);
int					hook_key(int key, t_mlx *mlx);
int					hook_mouse(int button, int x, int y, t_mlx *mlx);
int					hook_loop(t_mlx *mlx);
int					init_map(const t_mlx *mlx);
const t_mlx			*put_swstr(const t_mlx *mlx, const char *str, int x,
					const int y);

#endif

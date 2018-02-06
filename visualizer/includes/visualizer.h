/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:23:16 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/06 15:42:44 by nfinkel          ###   ########.fr       */
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
# define _SQR mlx->bsqr
# define _P1 mlx->sqrp1
# define _P2 mlx->sqrp2
# define _WIN mlx->win_ptr
# define _P1X 130
# define _P2X 1560
# define _PY 225
# define _P1C 0x2e99e3
# define _P2C 0xe1225d
# define _P1S 280
# define _P2S 1640
# define _PXS 830

typedef struct		s_mlx
{
	bool			mouse;
	bool			play;
	struct			s_sqr
	{
		int			__bppx;
		int			__sl;
		int			__endian;
		int			__sqrlen;
	}				__sqr;
	short			win_x;
	short			win_y;
	uint8_t			map_x;
	uint8_t			pad_x;
	uint8_t			map_y;
	uint8_t			pad_y;
	void			*bg;
	void			*bsqr;
	void			*clean;
	void			*sqrp1;
	void			*sqrp2;
	void			*mlx;
	void			*win_ptr;
	void			**font;
}					t_mlx;

#define bppx __sqr.__bppx
#define endian __sqr.__endian
#define sl __sqr.__sl
#define sqrlen __sqr.__sqrlen

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

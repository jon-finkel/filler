/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:23:16 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/05 13:34:55 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "../../libft/includes/libft.h"
# include "../../libft/includes/mlx_keys.h"
# include "../ressources/mlx/mlx.h"

# define _ADJUST(x, y) ((x) * (mlx->sqrlen + mlx->space) + (y))
# define _MLX mlx->mlx
# define _SQR mlx->bsqr
# define _P1 mlx->sqrp1
# define _P2 mlx->sqrp2
# define _WIN mlx->win_ptr
# define _PX (WIN_X / 2 + 50)
# define _P1Y (WIN_Y / 2 - 50)
# define _P2Y (WIN_Y * 3 / 4 - 40)
# define _P1C 0x2e6b23
# define _P2C 0xb87920
# define WIN_X 1200
# define WIN_Y 600

typedef struct		s_mlx
{
	bool			play;
	struct			s_sqr
	{
		int			__bppx;
		int			__sl;
		int			__endian;
		int			__space;
		int			__sqrlen;
	}				__sqr;
	uint8_t			map_x;
	uint8_t			pad_x;
	uint8_t			map_y;
	uint8_t			pad_y;
	void			*bsqr;
	void			*clean;
	void			*sqrp1;
	void			*sqrp2;
	void			*mlx;
	void			*win_ptr;
}					t_mlx;

#define bppx __sqr.__bppx
#define endian __sqr.__endian
#define sl __sqr.__sl
#define space __sqr.__space
#define sqrlen __sqr.__sqrlen

int					color_squares(t_mlx *mlx);
int					do_bars(void *mlx, void *win);
int					do_map(t_mlx *mlx, int *p1score, int *p2score);
void				errhdl(t_mlx *mlx, char *line);
int					hook_key(int key, t_mlx *mlx);
int					hook_loop(t_mlx *mlx);
int					init_map(const t_mlx *mlx);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:23:16 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/04 21:04:43 by nfinkel          ###   ########.fr       */
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
//# define _PX (WIN_X / 2 + 50)
//# define _P1Y (WIN_Y / 2 - 50)
//# define _P1SY (_P1Y + 50)
//# define _P2Y (WIN_Y * 3 / 4 - 30)
//# define _P2SY (_P2Y + 50)
# define _P1C 0xe74c3c
# define _P2C 0x3498db
# define WIN_X 1200
# define WIN_Y 600

struct				s_move
{
	char			player;
	int				score;
	uint8_t			nb;
	unsigned short	crd[255][2];
};

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
	unsigned short	map_x;
	unsigned short	pad_x;
	unsigned short	map_y;
	unsigned short	pad_y;
	void			*bsqr;
	void			*sqrp1;
	void			*sqrp2;
	void			*mlx;
	void			*win_ptr;
}					t_mlx;

typedef struct		s_data
{
	t_mlx			*mlx;
	t_dlist			*dlist;
}					t_data;

#define bppx __sqr.__bppx
#define endian __sqr.__endian
#define sl __sqr.__sl
#define space __sqr.__space
#define sqrlen __sqr.__sqrlen

int					color_squares(t_mlx *mlx);
int					do_map(t_dlist **adlst, t_mlx *mlx);
void				errhdl(t_mlx *mlx, char *line);
int					hook_key(int key, t_data *data);
int					hook_loop(t_data *data);
t_dlist				*init_dlist(t_dlist *dlist, const t_mlx *mlx);

#endif

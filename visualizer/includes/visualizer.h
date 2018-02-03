/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:23:16 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/03 00:01:39 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "../../libft/includes/libft.h"
# include "../mlx/mlx.h"

# define _MLX mlx->mlx
# define _SQR mlx->img
# define _WIN mlx->win_ptr
# define _PX (WIN_X / 2 + WIN_PAD + 50)
# define _P1Y (WIN_Y / 2 + WIN_PAD - 50)
# define _P1SY (_P1Y + 50)
# define _P2Y (WIN_Y * 3 / 4 - WIN_PAD - 30)
# define _P2SY (_P2Y + 50)
# define _P1C 0xF0F0F0
# define _P2C 0xFFFFFF
# define WIN_X 1200
# define WIN_Y 600

typedef struct		s_mlx
{
	char			*sqr;
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
	void			*img;
	void			*mlx;
	void			*win_ptr;
}					t_mlx;

#define bppx __sqr.__bppx
#define endian __sqr.__endian
#define sl __sqr.__sl
#define space __sqr.__space
#define sqrlen __sqr.__sqrlen

void				color_square(t_mlx *mlx, int color);

#endif

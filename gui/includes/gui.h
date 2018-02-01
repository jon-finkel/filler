/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 00:11:03 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/01 13:47:34 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "../../libft/includes/libft.h"
# include "../../includes/mlx/mlx.h"

# define WIN_X 1200
# define WIN_Y 600

typedef struct		s_mlx
{
	char			p1[512];
	char			p2[512];
	int				x;
	int				y;
	void			*id;
	void			*map;
	void			*win_ptr;
}					t_mlx;

#endif

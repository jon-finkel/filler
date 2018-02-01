/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:23:16 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/01 19:45:01 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "../../libft/includes/libft.h"
# include "../mlx/mlx.h"

# define _MLX mlx->mlx
# define _WIN mlx->win_ptr
# define WIN_PAD 10
# define WIN_X 1200
# define WIN_Y 600

typedef struct		s_mlx
{
	void			*mlx;
	void			*win_ptr;
	void			*xpm;
}					t_mlx;

#endif

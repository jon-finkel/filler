/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:00:25 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/29 16:52:24 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/includes/libft.h"

typedef struct		s_data
{
	char			**map;
	int8_t			op;
	int8_t			self;
	size_t			mx;
	size_t			my;
	int				plox;
	size_t			plx;
	int				ploy;
	size_t			ply;
	short			op_pos[2];
}					t_data;

typedef struct		s_mov
{
	bool			hit;
	char			**pc;
	int8_t			anchor;
	int				advx;
	int				advy;
	int				x;
	int				y;
}					t_mov;

int g_fd;
#include <fcntl.h>

void				test_fit(t_data *data, t_mov *mov, int x, int y);
bool				up_map(t_data *data, const char *line, bool r_pos);

#endif

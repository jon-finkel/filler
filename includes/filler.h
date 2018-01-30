/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:00:25 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/30 16:09:59 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/includes/libft.h"

typedef struct		s_crd
{
	int				k;
	int				p;
	int				x;
	int				y;
}					t_crd;

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
	double			reach;
	double			prio;
	int8_t			anchor;
	int8_t			contact;
	int				x;
	int				y;
}					t_mov;

int g_fd;
#include <fcntl.h>

t_data				*strat_map(t_data *data);
void				test_fit(t_data *data, t_mov *mov, struct s_crd *crd);
bool				up_map(t_data *data, const char *line, bool r_pos);

#endif

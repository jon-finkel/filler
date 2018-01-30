/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:00:25 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/30 22:49:51 by nfinkel          ###   ########.fr       */
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
	int				mx;
	int				my;
	int				plox;
	int				plx;
	int				ploy;
	int				ply;
	short			op_pos[2];
}					t_data;

typedef struct		s_mov
{
	bool			hit;
	char			**pc;
	int				reach;
	int				prio;
	int				rprio;
	int				anchor;
	int				contact;
	int				x;
	int				y;
}					t_mov;

int g_fd;
#include <fcntl.h>

t_data				*strat_map(t_data *data);
void				test_fit(t_data *data, t_mov *mov, struct s_crd *crd);
bool				up_map(t_data *data, const char *line, bool r_pos);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:00:25 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/27 13:56:40 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include "../libft/includes/libft.h"

#include <fcntl.h>
int		g_fd;

typedef struct		s_data
{
	char			**map;
	int8_t			op;
	int8_t			self;
	short			op_pos[2];
	size_t			mx;
	size_t			my;
	size_t			plx;
	size_t			ply;
}					t_data;

int					pc_coord(char *line, int *x);
void				test_fit(t_data *data, const char **pc, int x, int y);
bool				up_map(t_data *data, const char *line, bool r_pos);

#endif

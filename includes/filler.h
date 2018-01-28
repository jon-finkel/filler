/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:00:25 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/28 19:34:11 by nfinkel          ###   ########.fr       */
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
	short			op_pos[2];
	size_t			mx;
	size_t			my;
	int				plox;
	size_t			plx;
	int				ploy;
	size_t			ply;
}					t_data;

int g_fd;
#include <fcntl.h>

void				test_fit(t_data *data, const char **pc, int x, int y);
bool				up_map(t_data *data, const char *line, bool r_pos);

#endif

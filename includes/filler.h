/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:00:25 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/25 20:25:41 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

#include "../libft/includes/libft.h"

typedef struct		s_data
{
	char			**map;
	int8_t			opponent;
	int8_t			self;
	short			E[2];
	short			N[2];
	short			S[2];
	short			W[2];
}					t_data;

int					pc_coord(char *line, int *x);
bool				up_map(t_data *data, const char *line, bool first);

#endif

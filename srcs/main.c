/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:55:31 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/03 21:06:20 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static inline t_data			*init_data(t_data *dat, int x, int y, int8_t pl)
{
	char			row[x + 1];
	t_vector		*vec;

	FAILZ(vec = (t_vector *)ft_memalloc(sizeof(t_vector)), NULL);
	vec->data_size = sizeof(char *);
	FAILZ(dat = (t_data *)ft_memalloc(sizeof(t_data)), NULL);
	dat->self = (pl == 1 ? 'O' : 'X');
	dat->op = (pl == 1 ? 'X' : 'O');
	dat->mx = x;
	dat->my = y;
	ft_memset(row, '.', x);
	row[x] = '\0';
	while (y--)
		FAILZ(*(char **)ft_vecpush(vec) = ft_strdup(row), NULL);
	dat->map = vec->buff;
	free(vec);
	GIMME(dat);
}

static inline t_data			*get_size(t_data *data, const char **pc)
{
	int			k;
	int			p;

	data->plx = 0;
	data->ply = 0;
	k = -1;
	while (pc[++k])
	{
		p = -1;
		while (pc[k][++p])
			if (pc[k][p] == '*')
			{
				if (data->ploy == INT_MAX)
					data->ploy = k;
				data->plox = MIN(data->plox, p);
				data->plx = MAX(data->plx, p + 1);
				data->ply = MAX(data->ply, k + 1);
			}
	}
	GIMME(data);
}

static int						get_piece(t_data *data, t_mov *mov, int y)
{
	char			*line;
	int				k;
	t_crd			crd;
	t_vector		*vec;

	FAILZ(vec = (t_vector *)ft_memalloc(sizeof(t_vector)), -1);
	vec->data_size = sizeof(char *);
	k = -1;
	while (++k < y)
	{
		EPICFAILZ(get_next_line(STDIN_FILENO, &line), -1);
		FAILZ(*(char **)ft_vecpush(vec) = line, -1);
	}
	ft_memset(mov, '\0', sizeof(t_mov));
	mov->pc = vec->buff;
	mov->rprio = INT_MAX;
	data->plox = INT_MAX;
	data->ploy = INT_MAX;
	crd.x = 0;
	crd.y = 0;
	test_fit(get_size(strat_map(data), (const char **)mov->pc), mov, &crd);
	ft_vecclear(vec, (t_del)(&ft_memdel));
	free(vec);
	KTHXBYE;
}

static inline int				fight(t_data *data)
{
	int8_t		r_pos;
	char		*line;
	int			ret;
	t_mov		mov;

	if (!data)
		ONOES;
	r_pos = true;
	while ((ret = get_next_line(STDIN_FILENO, &line)))
	{
		if (ret < 0)
			ONOES;
		if (ft_isdigit(line[0]))
			r_pos = up_map(data, line, r_pos);
		else if (line[1] == 'i' && (r_pos = true))
			EPICFAILZ(get_piece(data, &mov, ft_atoi(line + 6)), -1);
		ft_strdel(&line);
	}
	KTHXBYE;
}

int								main(void)
{
	char		*line;
	int			x;
	int			y;
	int8_t		pl;

	EPICFAILZ(get_next_line(STDIN_FILENO, &line), -1);
	pl = (line[10] == '1' ? 1 : 2);
	ft_strdel(&line);
	EPICFAILZ(get_next_line(STDIN_FILENO, &line), -1);
	y = ft_atoi(line + 8);
	x = ft_atoi(line + ft_intlen(y) + 9);
	ft_strdel(&line);
	EPICFAILZ(fight(init_data(NULL, x, y, pl)), -1);
	KTHXBYE;
}

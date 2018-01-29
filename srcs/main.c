/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:55:31 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/29 06:32:12 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static t_data					*init_data(t_data *dat, int x, int y, int8_t pl)
{
	char			row[x + 1];
	t_vector		vec_null = {NULL, 0, 0, sizeof(char *)};
	t_vector		*vec = &vec_null;

	while (!(dat = (t_data *)ft_memalloc(sizeof(t_data))))
		KEEPATITBRA;
	dat->self = (pl == 1 ? 'O' : 'X');
	dat->op = (pl == 1 ? 'X' : 'O');
	dat->mx = x;
	dat->my = y;
	ft_memset(row, '.', x);
	row[x] = '\0';
	while (y--)
		if (!(*(char **)ft_vecpush(vec) = ft_strdup(row)))
			ft_fatal("OMGNOEZ");
	dat->map = vec->buff;
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
				data->plx = MAX(data->plx, (size_t)(p + 1));
				data->ply = MAX(data->ply, (size_t)(k + 1));
			}
	}
	GIMME(data);
}

static void						get_piece(t_data *restrict data,
								t_mov *restrict mov, int y)
{
	char			*line;
	int				k;
	t_vector		vec_null = {NULL, 0, 0, sizeof(char *)};
	t_vector		*vec = &vec_null;

	k = -1;
	while (++k < y)
	{
		if (get_next_line(STDIN_FILENO, &line) == -1)
			KEEPATITBRA;
		*(char **)ft_vecpush(vec) = line;
	}
	mov->pc = vec->buff;
	mov->x = 0;
	mov->y = 0;
	data->plox = INT_MAX;
	data->ploy = INT_MAX;
	test_fit(get_size(data, (const char **)mov->pc), mov, 0, 0);
	ft_vecclear(vec, (t_del)&ft_memdel);
}

static void						fight(t_data *data)
{
	int8_t		r_pos;
	char		*line;
	int			ret;
	t_mov		mov;

	r_pos = true;
	while ((ret = get_next_line(STDIN_FILENO, &line)))
	{
		if (ret == -1)
			KEEPATITBRA;
		if (ft_isdigit(line[0]))
			r_pos = up_map(data, line, r_pos);
		else if (line[1] == 'i' && (r_pos = true))
			get_piece(data, &mov, ft_atoi(line + 6));
		ft_strdel(&line);
	}
}

int								main(void)
{
	char		*line;
	int			x;
	int			y;
	int8_t		pl;

	g_fd = open("/Users/jon/42/filler/verbose", O_CREAT | O_TRUNC | O_RDWR, 0600);
	while (get_next_line(STDIN_FILENO, &line) == -1)
		KEEPATITBRA;
	pl = (line[10] == '1' ? 1 : 2);
	ft_strdel(&line);
	while (get_next_line(STDIN_FILENO, &line) == -1)
		KEEPATITBRA;
	y = ft_atoi(line + 8);
	x = ft_atoi(line + ft_intlen(y) + 9);
	ft_strdel(&line);
	fight(init_data(NULL, x, y, pl));
	KTHXBYE;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:55:31 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/27 15:10:31 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static t_data			*init_data(t_data *data, int x, int y, int8_t pl)
{
	char			row[x + 1];
	t_vector		vec_null = {NULL, 0, 0, sizeof(char *)};
	t_vector		*vec = &vec_null;

	while (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
		KEEPATITBRA;
	data->self = (pl == 1 ? 'O' : 'X');
	data->op = (pl == 1 ? 'X' : 'O');
	data->mx = x;
	data->my = y;
	ft_memset(row, '.', x);
	row[x] = '\0';
	while (y--)
		if (!(*(char **)ft_vecpush(vec) = ft_strdup(row)))
			ft_fatal("OMGNOEZ");
	data->map = vec->buff;
	GIMME(data);
}

static void				get_piece(t_data *data, int x, int y)
{
	char		*line;
	char		**pc;
	int			k;
	t_vector		vec_null = {NULL, 0, 0, sizeof(char *)};
	t_vector		*vec = &vec_null;

	data->plx = x;
	data->ply = y;
	k = -1;
	while (++k < y)
	{
		if (get_next_line(STDIN_FILENO, &line) == -1)
			KEEPATITBRA;
ft_dprintf(g_fd, "%s\n", line);
		*(char **)ft_vecpush(vec) = line;
	}
	pc = vec->buff;
	test_fit(data, (const char **)pc, 0, 0);
	ft_cleanup("A", pc);
}

static void				fight(t_data *data)
{
	int8_t		r_pos;
	char		*line;
	int			ret;
	int			y;

	r_pos = true;
	while ((ret = get_next_line(STDIN_FILENO, &line)))
	{
		if (ret == -1)
			KEEPATITBRA;
ft_dprintf(g_fd, "%s\n", line);
		if (ft_isdigit(line[0]))
			r_pos = up_map(data, line, r_pos);
		else if (line[1] == 'i' && (r_pos = true))
			get_piece(data, pc_coord(line, &y), y);
		ft_strdel(&line);
	}
}

int						main(void)
{
	char		*line;
	int			x;
	int			y;
	int8_t		pl;

	g_fd = open("/Users/nfinkel/42/filler/verbose", O_RDWR | O_TRUNC | O_CREAT, 0600);
	while (get_next_line(STDIN_FILENO, &line) == -1)
		KEEPATITBRA;
ft_dprintf(g_fd, "%s\n", line);
	pl = (line[10] == '1' ? 1 : 2);
	ft_strdel(&line);
	while (get_next_line(STDIN_FILENO, &line) == -1)
		KEEPATITBRA;
ft_dprintf(g_fd, "%s\n", line);
	y = ft_atoi(line + 8);
	x = ft_atoi(line + ft_intlen(y) + 9);
	ft_strdel(&line);
	fight(init_data(NULL, x, y, pl));
	KTHXBYE;
}

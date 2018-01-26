/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:55:31 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/25 22:16:10 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static t_data			*init_data(t_data *data, int x, int y, int8_t pl)
{
	char			row[x + 1];
	t_vector		vec_null = {NULL, 0, 0, sizeof(char *)};
	t_vector		*vec = &vec_null;

	while (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
		continue ;
	data->self = (pl == 1 ? 'X' : 'O');
	data->opponent = (data->self == 'X' ? 'o' : 'x');
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
	char		pc[y + 1][x + 1];
	char		*line;
	int			k;

	k = -1;
	while (get_next_line(STDIN_FILENO, &line))
	{
		ft_strcpy(pc[++k], line);
		pc[k][x] = '\0';
		ft_strdel(&line);
	}
	pc[k + 1][0] = '\0';
}

static void				fight(t_data *data)
{
	bool		first;
	char		*line;
	int			ret;
	int			y;

	first = true;
	while ((ret = get_next_line(STDIN_FILENO, &line)))
	{
		if (ret == -1)
			continue ;
		else if (ft_isdigit(line[0]))
			first = up_map(data, line, first);
		else if (line[1] == 'i')
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

	while (get_next_line(STDIN_FILENO, &line) == -1)
		continue ;
	if (!ft_strstr(line, "p1") && !ft_strstr(line, "p2"))
		ft_fatal("Bad player info");
	pl = (line[10] == '1' ? 1 : 2);
	ft_strdel(&line);
	while (get_next_line(STDIN_FILENO, &line) == -1)
		continue ;
	y = ft_atoi(line + 8);
	x = ft_atoi(line + ft_intlen(y) + 9);
	ft_strdel(&line);
	fight(init_data(NULL, x, y, pl));
	KTHXBYE;
}

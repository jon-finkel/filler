/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errhdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 14:45:22 by nfinkel           #+#    #+#             */
/*   Updated: 2018/02/08 12:18:43 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

_Noreturn void			errhdl(t_mlx *mlx, char *line)
{
	ft_memdel((void **)&mlx);
	ft_printf("%s\n", line);
	free(line);
	while (get_next_line(STDIN_FILENO, &line))
	{
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	exit(EXIT_SUCCESS);
}

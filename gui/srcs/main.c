/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 00:10:40 by nfinkel           #+#    #+#             */
/*   Updated: 2018/01/31 16:27:29 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gui.h"

int			main(void)
{
	void		*mlx;

	KEEPATITBRA(mlx = mlx_new_window(mlx_init(), 1920, 1080, "Filler"));
	KTHXBYE;
}

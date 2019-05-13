/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:27:19 by root              #+#    #+#             */
/*   Updated: 2019/05/13 13:49:42 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int		main(int ac, char **av)
{
	int				fd;
	t_tab			*lem_in;
	t_tab			*tmp;
	t_lemin		*here;

	if (ac != 2)
		return (0);
	ft_printf("%s\n", __func__);
	if ((fd = open(av[1], O_RDONLY)) > 0)
		lem_in = init(fd);
	ft_printf("%s:%p\n", "INIT done", lem_in);
	tmp = lem_in;
	while (tmp)
	{
		here = *(t_lemin**)(tmp->content);
		ft_printf("NAME: %s(%d)\t%d\t[%d;%d]\n", here->name, here->ants, here->place, here->y_coord, here->x_coord);
		tmp = tmp->dir[0];
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:27:19 by root              #+#    #+#             */
/*   Updated: 2019/05/19 15:35:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int		main(int ac, char **av)
{
	int				fd;
	t_tab			*lem_in;
	t_tab			*tmp;
	t_lemin		*here;
	int				i;
	int				len;

	if (ac != 2)
		return (0);
	ft_printf("%s\n", __func__);
	if ((fd = open(av[1], O_RDONLY)) > 0)
		lem_in = init(fd);
	ft_printf("%s:%p\n", "INIT done", lem_in);
	tmp = lem_in;
	len = ft_tab_lendir(lem_in, 0);
	while (tmp)
	{
		here = (t_lemin*)(tmp->content);
		ft_printf("NAME: %s(%d)\t%d\t[%d;%d]\n", here->name, here->ants, here->place, here->y_coord, here->x_coord);
		i = -1;
		while (++i < len)
			if (!here->connexions[i])
				ft_printf("%p\t", here->connexions[i]);
			else
				ft_printf("%s\t", ((t_lemin*)here->connexions[i])->name);
		ft_printf("\n");
		tmp = tmp->dir[0];
	}
	return (0);
}

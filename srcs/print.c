/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:30:29 by root              #+#    #+#             */
/*   Updated: 2019/05/25 17:18:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int		print_matrix(t_tab *lem_in)
{
	int				fd;
	t_tab			*tmp;
	t_lemin		*here;
	int				i;
	int				len;

	tmp = lem_in;
	len = ft_tab_lendir(lem_in, 0);
	fd = ft_strlen(((t_lemin*)lem_in->content)->name);
	if (fd < 3)
		fd = 3;
	ft_printf("%*s", fd, " ");
	while (tmp)
	{
		here = (t_lemin*)(tmp->content);
		ft_printf("%~{?*}%*s%s%*s%~{}", here, fd - (ft_strlen(here->name) / 2), " ", here->name, 1 + fd % 2 + (fd - (fd % 2)) - ((ft_strlen(here->name) / 2) + (ft_strlen(here->name) % 2)), " ");
		tmp = tmp->dir[0];
	}
	tmp = lem_in;
	ft_printf("\n");
	while (tmp)
	{
		here = (t_lemin*)(tmp->content);
		ft_printf("%~{?*}%*s%~{}", here, fd, here->name);
		i = -1;
		while (++i < len)
		{
			if (!here->connexions[i])
			{
				// ft_printf("%~{?*}%-*s%~{}", here->connexions[i], fd, "void");
				ft_printf("%*s%~{80;0;100}x%~{}%*s", fd, " ", fd, " ");
				// break ;
			}
			else
			{
				ft_printf("%~{?*}%*s%~{} ", here, fd, here->name);
				ft_printf("%~{?*}%-*s%~{}", here->connexions[i], fd, ((t_lemin*)here->connexions[i])->name);
			}
		}
		ft_printf("\n");
		tmp = tmp->dir[0];
	}
	return (0);
}

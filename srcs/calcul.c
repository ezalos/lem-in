/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:35:56 by root              #+#    #+#             */
/*   Updated: 2019/05/27 18:05:02 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/head.h"

void 		clear_data(t_god *god)
{
		int i;

		i = -1;
		while (++i < god->size)
		{
			god->rooms[i]->from_end = 0;
			god->rooms[i]->from_start = 0;
		}
		god->start->gone = 0;
		god->end->gone = 0;
}

void 		show_nbs(t_god *god)
{
	t_tab		*tmp;
	t_lemin	*here;

	tmp = god->lem_in;
	while (tmp)
	{
		here = tmp->content;
		ft_printf("%~{255;155;255}%*s%~{}(%d)\t", 10, here->name, here->gone);
		ft_printf("start: %d\t", here->from_start);
		ft_printf("end: %d\n", here->from_end);
		tmp = tmp->dir[0];
	}
	ft_printf("\n");
}

int				lets_calcul(t_god *god)
{
	int i;

	how_many_entries_exits(god);
	i = god->goulots;
	while (i--)
	{
		ft_printf("\nSIZE: %d\n", god->size);
		refresh_a_star(god);
		// show_nbs(god);
		find_a_path(god->start);
		clear_data(god);
	}
	return (0);
}

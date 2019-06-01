/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:16:14 by root              #+#    #+#             */
/*   Updated: 2019/06/01 13:20:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				how_many_entries_exits(t_god *god)
{
		int i;
		int			name_size;

		name_size = ft_nb_len(god->end->id, 10);i = -1;
		god->entry_list = ft_memalloc(sizeof(int*) * god->start->nb_of_connexions);
		god->exit_list = ft_memalloc(sizeof(int*) * god->end->nb_of_connexions);
		ft_printf("Start goulot: ");
		while (god->start->connexions[++i])
		{
			clear_data(god);
			god->start->gone = 1;
			if (alternate_piles(god, ((t_lemin*)god->start->connexions[i])->id, god->end->id, 0)
			||  alternate_piles(god, ((t_lemin*)god->start->connexions[i])->id, god->end->id, 1))
			{
				ft_printf("%~{155;255;155}%*d%~{} ", name_size, ((t_lemin*)god->start->connexions[i])->id);
				god->entry_points++;
				god->entry_list[god->entry_points] = ((t_lemin*)god->start->connexions[i])->id;
			}
			else
				ft_printf("%~{255;155;155}%*d%~{} ", name_size, ((t_lemin*)god->start->connexions[i])->id);
		}
		ft_printf("\n");
		ft_printf("  End goulot: ");
		i = -1;
		while (god->end->connexions[++i])
		{
			clear_data(god);
			god->end->gone = 1;
			if (alternate_piles(god, god->start->id, ((t_lemin*)god->end->connexions[i])->id, 0)
			||  alternate_piles(god, god->start->id, ((t_lemin*)god->end->connexions[i])->id, 1))
			{
				ft_printf("%~{155;255;155}%*d%~{} ", name_size, ((t_lemin*)god->end->connexions[i])->id);
				god->exit_points++;
				god->exit_list[god->exit_points] = ((t_lemin*)god->start->connexions[i])->id;
			}
			else
				ft_printf("%~{255;155;155}%*d%~{} ", name_size, ((t_lemin*)god->end->connexions[i])->id);
		}
		ft_printf("\n");
		clear_data(god);
		if (god->exit_points < god->entry_points)
			god->goulots = god->exit_points;
		else
			god->goulots = god->entry_points;
		ft_printf("Goulots %d\tEntry %d\tExit %d\n", god->goulots, god->entry_points, god->exit_points);
		return (god->goulots);
}

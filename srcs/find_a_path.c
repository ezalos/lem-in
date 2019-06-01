/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_a_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:32:03 by root              #+#    #+#             */
/*   Updated: 2019/06/01 13:47:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		print_debug(t_lemin *here)
{
	if (here->place == START)
		ft_printf("%~{255;155;155}");
	else	if (here->place == END)
		ft_printf("%~{155;255;155}");
	ft_printf("%s%~{}\n", here->name);
}

void		save_this_path(t_lemin *here, t_path *ptr)
{
	if (!ptr->path)
		ptr->path = ft_memalloc((*ft_remember_god())->size * sizeof(int));
	ptr->path[0] += 1;
	ptr->path[ptr->path[0]] = here->id;
}

int			compare_rooms(t_lemin *zero, t_lemin *one)
{
	if (one->from[1] < zero->from[1])
		return (1);
	else if (zero->from[1] == one->from[1] && one->from[0] < zero->from[0])
		return (1);
	return (0);
}

void			find_a_path(t_lemin *here, t_path *ptr)
{
		int							winner;
		int							i;

		i = -1;
		winner = -1;
		// print_debug(here);
		save_this_path(here, ptr);
		while (here->connexions[++i] && winner < 0)
			if (!((t_lemin*)here->connexions[i])->gone)
				winner = i;
		if (winner == -1)
			return ;
		if (here->place == END)
			return ;
		i = winner;
		while (here->connexions[++i])
			if (!((t_lemin*)here->connexions[i])->gone)
				if (compare_rooms(here->connexions[winner], here->connexions[i]))
					winner = i;
		here->gone = 1;
		find_a_path(here->connexions[winner], ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:48 by root              #+#    #+#             */
/*   Updated: 2019/06/08 15:04:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			order_my_little_connexions(t_god *god)
{
		int i;
		int j;
		t_tab *now;
		t_lemin *here;

		time_exe(__func__);
		i = 0;
		now = god->lem_in;
		while (now)
		{
			here = now->content;
			i = -1;
			while (++i < god->size)
				if (!here->connexions[i])
				{
					j = -1;
					while (++j + i < god->size)
						if (here->connexions[i + j])
							ft_swap(&here->connexions[i], &here->connexions[i + j], sizeof(void*));
				}
			i = 0;
			while (here->connexions[i])
				i++;
			here->nb_of_connexions = i;
			now = now->dir[0];
		}
		return (0);
}

void		get_rooms_in_tab(t_god *god)
{
	t_tab		*now;
	int 		i;

	time_exe(__func__);
	now = god->lem_in;
	god->rooms = ft_memalloc(sizeof(t_lemin**) * (god->size + 1));
	i = -1;
	while (++i < god->size)
	{
		// god->rooms = ft_memalloc(sizeof(t_lemin*));
		god->rooms[i] = now->content;
		god->rooms[i]->id = i;
		now = now->dir[0];
	}
}

t_god		**ft_remember_god(void)
{
	static t_god		*god;

	return (&god);
}
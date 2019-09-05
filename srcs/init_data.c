/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:48 by root              #+#    #+#             */
/*   Updated: 2019/06/24 19:42:59 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			order_my_little_connexions(t_god *god)
{
		int i;
		int j;
		t_tab *now;
		t_lemin *here;

		i = 0;
		now = god->lem_in;
		while (now)
		{
			here = now->content;
			i = 0;
			while (here->connexions[i])
				i++;
			here->nb_of_connexions = i;
			now = now->dir[0];
		}
		return (0);
		j = -1;
}

void		get_rooms_in_tab(t_god *god)
{
	t_tab		*now;
	int 		i;

	now = god->lem_in;
	god->rooms = ft_memalloc(sizeof(t_lemin**) * (god->size + 1));
	i = -1;
	while (++i < god->size)
	{
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

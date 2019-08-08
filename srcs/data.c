/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:35:56 by root              #+#    #+#             */
/*   Updated: 2019/06/24 19:43:10 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void 		clear_data(t_god *god)
{
		int i;

		i = -1;
		while (++i < god->size)
		{
			god->rooms[i]->from[1] = 0;
			god->rooms[i]->from[0] = 0;
		}
		god->start->gone = 0;
		god->end->gone = 0;
}

void clear_links(t_god *god)
{
	int i;
	int j;

	i = 0;
	while (god->rooms[i])
	{
		j = 0;
		while (j < god->rooms[i]->nb_of_connexions)
		{
			god->rooms[i]->used[j] = 0;
			j++;
		}
		i++;
	}
}
void 		clear_tmp_links(t_god *god)
{
	int i;
	int j;

	i = 0;
	while (god->rooms[i])
	{
		j = 0;
		while (j < god->rooms[i]->nb_of_connexions)
		{
			god->rooms[i]->tmp_used[j] = 0;
			j++;
		}
		i++;
	}
}

void		set_link(t_god *god, int r1, int r2)
{
	int i;

	i = 0;
	while (i < god->rooms[r1]->nb_of_connexions)
	{
		if (god->rooms[r1]->connexions[i]->id == r2)
			god->rooms[r1]->tmp_used[i] = 1;
		i++;
	}
}

void		add_surcharged_link(t_god *god)
{
	int i;
	int nb;

	i = 1;
	nb = god->surcharged_link[0];
	while (i <= nb)
	{
		set_link(god, god->surcharged_link[i], god->surcharged_link[i + 1]);
		set_link(god, god->surcharged_link[i + 1], god->surcharged_link[i]);
		i = i + 2;
	}
}

void		clean_surcharged_tab(t_ints tab)
{
	int nb;
	int i;

	i = 1;
	nb = tab[0];
	while (i <= nb)
	{
		tab[i] = 0;
		i++;
	}
	tab[0] = 0;
}

void 		refresh_tmp_links(t_god *god)
{
	int i;
	int j;

	i = 0;
	while (god->rooms[i])
	{
		j = 0;
		while (j < god->rooms[i]->nb_of_connexions)
		{
			god->rooms[i]->tmp_used[j] = god->rooms[i]->used[j];
			j++;
		}
		i++;
	}
	if (god->trigger != 0)
		add_surcharged_link(god);
}

void 		clear_gone(t_god *god)
{
		int i;

		i = -1;
		while (++i < god->size)
		{
			god->rooms[i]->gone = 0;
			god->rooms[i]->weight = 0;
			god->rooms[i]->last_room = NULL;
			god->rooms[i]->surcharged = 0;
			god->rooms[i]->blocked = 0;
		}
}

void 		full_clear(t_god *god)
{
		clear_data(god);
		clear_gone(god);
}

void 		add_gone_from_paths(t_god *god)
{
	// t_ints		path;
	// int 		i;
	// int			j;

	// i = -1;
	// while (++i < god->goulots)
	// {
	// 	path = god->paths[i];
	// 	if (path && path[0])
	// 	{
	// 		j = 0;
	// 		while (++j <= path[0])
	// 			god->rooms[path[j]]->gone = 1;
	// 	}
	// }
	(void)god;
}

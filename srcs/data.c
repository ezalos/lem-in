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

void 		clear_gone(t_god *god)
{
		int i;

		i = -1;
		while (++i < god->size)
			god->rooms[i]->gone = 0;
}

void 		full_clear(t_god *god)
{
		clear_data(god);
		clear_gone(god);
}

void 		add_gone_from_paths(t_god *god)
{
	t_ints		path;
	int 		i;
	int			j;

	i = -1;
	while (++i < god->goulots)
	{
		path = god->paths[i];
		if (path && path[0])
		{
			j = 0;
			while (++j <= path[0])
				god->rooms[path[j]]->gone = 1;
		}
	}
}

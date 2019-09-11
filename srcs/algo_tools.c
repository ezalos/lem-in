/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:08:45 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/11 16:08:14 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				find_link(t_lemin *tmp)
{
	int i;

	i = 0;
	while (i < tmp->last_room->nb_of_connexions)
	{
		if (tmp->last_room->connexions[i]->id == tmp->id)
			return (i);
		i++;
	}
	return (-1);
}

int				find_pv_link(t_god *god, t_lemin *tmp, t_piles *stack)
{
	int i;

	i = 0;
	while (i < god->rooms[stack->actual_room]->nb_of_connexions)
	{
		if (god->rooms[stack->actual_room]->connexions[i]->id == tmp->id)
			return (i);
		i++;
	}
	return (-1);
}

int				is_it_connected(t_god *god, int room1, int room2)
{
	int i;

	i = 0;
	while (i < god->rooms[room2]->nb_of_connexions)
	{
		if (god->rooms[room2]->connexions[i]->id == god->rooms[room1]->id
			&& god->rooms[room2]->tmp_used[i] == 1)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void			creat_surcharged_link(t_god *god, int room1, int room2)
{
	int pos;

	pos = god->surcharged_link[0] + 1;
	god->surcharged_link[pos] = room1;
	god->surcharged_link[pos + 1] = room2;
	god->surcharged_link[0] = god->surcharged_link[0] + 2;
}

int				which_link_is_surcharged(t_god *god, t_ints path)
{
	int i;
	int len;
	int result;

	i = 1;
	len = path[0];
	result = 0;
	while (i < len)
	{
		if (is_it_connected(god, god->rooms[path[i]]->id,
			god->rooms[path[i + 1]]->id) == 1)
		{
			creat_surcharged_link(god, god->rooms[path[i]]->id,
				god->rooms[path[i + 1]]->id);
			result = 1;
		}
		i++;
	}
	return (result);
}

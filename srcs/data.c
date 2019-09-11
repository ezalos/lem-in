/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:35:56 by root              #+#    #+#             */
/*   Updated: 2019/09/11 16:14:41 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		clear_data(t_god *god)
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

void		clear_gone(t_god *god)
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
		god->rooms[i]->gen = -1;
	}
}

void		full_clear(t_god *god)
{
	clear_data(god);
	clear_gone(god);
}

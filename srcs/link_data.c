/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 18:06:03 by ythomas           #+#    #+#             */
/*   Updated: 2019/08/27 18:06:06 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

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

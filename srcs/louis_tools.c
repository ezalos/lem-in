/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:13:37 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/19 15:19:07 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		clean_search(t_god *god)
{
	int i;

	i = -1;
	while (++i < god->size)
		god->rooms[i]->search = 0;
}

void 		clean_gone(t_god *god)
{
	int i;
	// int j;

	i = -1;
	while (++i < god->size)
	{
		god->rooms[i]->gone = 0;
		god->rooms[i]->depth = -1;
		ft_bzero(god->rooms[i]->used, god->rooms[i]->nb_of_connexions * sizeof(int));
		// j = -1;
		// while (++j < god->rooms[i]->nb_of_connexions)
		// 	ft_printf("%d ", god->rooms[i]->used[0]);
	}
}

void 		clean_dist(t_god *god)
{
	int i;
	// int j;

	i = -1;
	while (++i < god->size)
	{
		// if (!god->rooms[i]->gone)
		// god->rooms[i]->dist_to_end = INT_MAX;
		ft_bzero(god->rooms[i]->tmp_used, god->rooms[i]->nb_of_connexions * sizeof(int));
		// j = -1;
		// while (++j < god->rooms[i]->nb_of_connexions)
		// 	ft_printf("%d", god->rooms[i]->tmp_used[0])
	}
}

void 		mean_connec(t_god *god)
{
	int i;
	int tt;
	int nb;
	int one = 0;
	int two = 0;
	int three = 0;
	int four = 0;
	int five = 0;
	int six = 0;
	int more = 0;

	i = -1;
	tt = 0;
	nb = 0;
	while (++i < god->size)
		if (god->rooms[i]->nb_of_connexions > 2)
		{
			tt += god->rooms[i]->nb_of_connexions;
			nb++;
			if (god->rooms[i]->nb_of_connexions == 3)
				three++;
			else if (god->rooms[i]->nb_of_connexions == 4)
				four++;
			else if (god->rooms[i]->nb_of_connexions == 5)
				five++;
			else if (god->rooms[i]->nb_of_connexions == 6)
				six++;
			else
				more++;
		}
		else if (god->rooms[i]->nb_of_connexions == 2)
			two++;
		else
			one++;
	ft_printf("TT = %d/%d\n", tt, nb);
	tt /= nb;
	ft_printf("TT = %d\n", tt);
	ft_printf("1 = %d\n", one);
	ft_printf("2 = %d\n", two);
	ft_printf("3 = %d\n", three);
	ft_printf("4 = %d\n", four);
	ft_printf("5 = %d\n", five);
	ft_printf("6 = %d\n", six);
	ft_printf("more = %d\n", more);
}

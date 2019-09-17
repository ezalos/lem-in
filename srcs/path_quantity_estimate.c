/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_quantity_estimate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:16:14 by root              #+#    #+#             */
/*   Updated: 2019/09/17 13:56:02 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		block_all_rooms_connected(t_lemin *here)
{
	int i;

	i = -1;
	while (here->connexions[++i])
		((t_lemin*)here->connexions[i])->gone = 1;
}

int				how_many_extremities(t_god *god, int side)
{
	int 		i;

	i = -1;
	god->extremities_list[side] = ft_memalloc(sizeof(int*)
		* (god->extremities[side]->nb_of_connexions + 1));
	while (god->extremities[side]->connexions[++i])
	{
		full_clear(god);
		block_all_rooms_connected(god->extremities[side]);
		((t_lemin*)god->extremities[side]->connexions[i])->gone = 0;
		god->extremities[side]->gone = 1;
		if (alternate_piles(god,
		((t_lemin*)god->extremities[side]->connexions[i])->id,
		god->extremities[!side]->id, 0))
		{
			god->extremities_list[side][++(*god->extremities_list[side])]
			= ((t_lemin*)god->extremities[side]->connexions[i])->id;
		}
	}
	return (1);
}

int				how_many_entries_exits(t_god *god)
{
		how_many_extremities(god, 0);
		how_many_extremities(god, 1);
		full_clear(god);
		if (god->extremities_list[1][0] < god->extremities_list[0][0])
		{
			god->goulots = god->extremities_list[1][0];
			god->side = 1;
		}
		else
		{
			god->goulots = god->extremities_list[0][0];
			god->side = 0;
		}
		clear_gone(god);
		return (god->goulots);
}

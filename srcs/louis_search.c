/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:16:40 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/24 18:16:58 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			search_unused_rooms(t_god *god, t_data *possibility_tree)
{
	t_lemin					*here;
	int						i;

	here = possibility_tree->room;
	i = -1;
	while (here->connexions[++i])
		if (is_unused_room_valid(god, here->connexions[i], possibility_tree))
			save_to_tree(possibility_tree, here->connexions[i], NORMAL);
	return (FAILURE);
}

int			search_used_rooms(t_god *god, t_data *possibility_tree)
{
	t_lemin					*here;
	int						i;

	here = possibility_tree->room;
	i = -1;
	while (here->connexions[++i])
		if (is_used_room_valid(god, here->connexions[i], possibility_tree))
		{
			save_to_tree(possibility_tree, here->connexions[i], SURCHARGE);
		}
	return (FAILURE);
}

int			special_cases(t_god *god, t_data *possibility_tree)
{
	t_lemin					*here;

	here = possibility_tree->room;
	if (possibility_tree->surcharge)
	{
		save_to_tree(possibility_tree, here->last_room, NORMAL);
		return (SUCCESS);
	}
	if (possibility_tree->room->id == god->extremities[1]->id)
	{
		if (here->depth < god->turn)
			save_solution(god, possibility_tree);
		return (SUCCESS);
	}
	if (here->id == god->extremities[0]->id)
		here->depth = 0;
	else if (here->depth == -1)
		here->depth = possibility_tree->daddy->room->depth + 1;
	else if (here->depth < possibility_tree->daddy->room->depth + 1)
		here->depth = possibility_tree->daddy->room->depth + 1;
	else
		return (FAILURE);
	return (NEUTRAL);
}

int			search_a_path(t_god *god, t_data *possibility_tree)
{
	t_lemin					*here;
	int						r_v;

	here = possibility_tree->room;
	if ((r_v = special_cases(god, possibility_tree)) != NEUTRAL)
		return (r_v);
	room_connexions_sort(here);
	if ((r_v = search_unused_rooms(god, possibility_tree)) == SUCCESS)
		return (r_v);
	if ((r_v = search_used_rooms(god, possibility_tree)) == SUCCESS)
		return (r_v);
	return (FAILURE);
}

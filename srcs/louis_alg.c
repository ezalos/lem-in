/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_alg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:45:56 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/24 18:21:25 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			traversal_tree_search(t_god *god, t_data *daddy, int depth)
{
	int						i;
	int						tt;

	tt = 0;
	if (god->reach_end_room)
		return (1);
	if (daddy->depth == depth)
	{
		search_a_path(god, daddy);
		return (1);
	}
	i = -1;
	while (!god->reach_end_room && daddy->baby[NORMAL][++i])
		tt += traversal_tree_search(god, daddy->baby[NORMAL][i], depth);
	i = -1;
	while (!god->reach_end_room && daddy->baby[SURCHARGE][++i])
		tt += traversal_tree_search(god, daddy->baby[SURCHARGE][i], depth);
	return (tt);
}

int			update_last_room(t_god *god, t_data *here)
{
	int						r_v;

	r_v = FAILURE;
	if (here)
	{
		if (here->id == god->extremities[0]->id)
			r_v = SUCCESS;
		if (here->daddy)
		{
			if (!here->daddy->surcharge)
				here->room->last_room = here->daddy->room;
			r_v = update_last_room(god, here->daddy);
		}
	}
	return (r_v);
}

int			ultimate_dispatch_room(t_god *god)
{
	int						depth;
	int						is_working;

	depth = 0;
	god->reach_end_room = NULL;
	god->possibility_tree = create_branch(god->extremities[0]);
	is_working = 1;
	while (!god->reach_end_room && is_working)
		is_working = traversal_tree_search(god, god->possibility_tree, depth++);
	if (is_working)
		update_last_room(god, god->reach_end_room);
	return (is_working);
}

void		choose_best_solution(t_god *god)
{
	if (god->save_turn < god->turn)
	{
		god->final_path = god->save_path;
		god->nb_final_paths = god->save_path_nb;
		god->yohan = god->turn;
		god->turn = god->save_turn;
		god->save_turn = god->yohan;
		god->yohan = 1;
	}
}

void		loulou(t_god *god)
{
	int						ite;
	int						save;
	int						retry;

	save_yoyo(god);
	reset_all(god);
	init_paths(god);
	ite = 1;
	retry = 3;
	while (retry && ite && god->goulots > god->nb_final_paths)
	{
		save = god->turn;
		clean_search(god);
		ite = ultimate_dispatch_room(god);
		if (!ite)
			continue;
		clean_gone(god);
		extract_paths(god);
		if (save <= god->turn)
			retry--;
		else
			retry = 3;
	}
	choose_best_solution(god);
}

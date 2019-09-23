/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_alg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:45:56 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/23 21:19:17 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			is_room_searched(t_data *baby, int id)
{
	// DEBUG_FUNC;
	int		r_v;

	r_v = 0;
	if (baby->id == id)
		r_v = 1;
	else if (baby->daddy)
		r_v += is_room_searched(baby->daddy, id);
	// ft_printf("%d\n", r_v);
	return (r_v);
}

int			is_room_valid_base(t_god *god, t_lemin *room, t_data *baby)
{
	int		r_v;

	r_v = FAILURE;
	// if (room->dist_to_end != -1)
		if (room->id != god->extremities[0]->id)
			if (!is_room_searched(baby, room->id))
				r_v = SUCCESS;
	// DEBUG_FUNC;
	// ft_printf("%d\n", r_v);
	return (r_v);
}

int			is_used_room_valid(t_god *god, t_lemin *room, t_data *baby)
{
	int		r_v;

	r_v = FAILURE;
	if (is_room_valid_base(god, room, baby))
		if (room->gone)
			if (room->last_room)
				if (room->last_room->id != god->extremities[0]->id)
					r_v = SUCCESS;
	// DEBUG_FUNC;
	// ft_printf("%d\n", r_v);
	return (r_v);
}

int			is_unused_room_valid(t_god *god, t_lemin *room, t_data *baby)
{
	int		r_v;

	r_v = FAILURE;
	if (is_room_valid_base(god, room, baby))
		if (!room->gone)
			r_v = SUCCESS;
	// DEBUG_FUNC;
	// ft_printf("%d\n", r_v);
	return (r_v);
}

int		is_connec_available(t_lemin *room, int connec)
{
	// DEBUG_FUNC;
	if (room->used[connec] || room->tmp_used[connec])
		return (FAILURE);
	room->tmp_used[connec] = 1;
	return (SUCCESS);
}

void	search_init_room(t_lemin *here, t_lemin *daddy, t_lemin **save)
{
	*save = here->last_room;
	here->last_room = daddy;
	here->search = 1;//tmp
}

void	search_uninit_room(t_lemin *here, t_lemin *save)
{
	here->last_room = save;
	here->search = 0;
}

int		search_unused_rooms(t_god *god, t_data *possibility_tree)
{
	// DEBUG_FUNC;
	t_lemin					*here;
	// int						r_v;
	int						i;

	here = possibility_tree->room;
	i = -1;
	while (here->connexions[++i])// && DEBUG_FUNC)
		if (is_unused_room_valid(god, here->connexions[i], possibility_tree))// && is_connec_available(here,i))
			save_to_tree(possibility_tree, here->connexions[i], NORMAL);
			// if ((r_v = search_a_path(god, here->connexions[i], here)))
			// {
			// 	return (r_v);
			// }
	return (FAILURE);
}

int		search_used_rooms(t_god *god, t_data *possibility_tree)
{
	// DEBUG_FUNC;
	t_lemin					*here;
	// int						r_v;
	int						i;

	here = possibility_tree->room;
	i = -1;
	while (here->connexions[++i])// && DEBUG_FUNC)
		if (is_used_room_valid(god, here->connexions[i], possibility_tree))// && is_connec_available(here,i)
	 	//&& is_connec_available(here->connexions[i], find_connec_ptr(god, here->connexions[i], here->connexions[i]->last_room)))
		{
			save_to_tree(possibility_tree, here->connexions[i], SURCHARGE);

			// search_init_room(here->connexions[i], here, &surcharge_save);
			// // surcharge_save = here->connexions[i]->last_room;
			// if ((r_v = search_a_path(god, surcharge_save, surcharge_save->last_room)))
			// {
			// 	return (r_v);
			// }
			// search_uninit_room(here->connexions[i], surcharge_save);
		}
	return (FAILURE);
}

int		search_a_path(t_god *god, t_data *possibility_tree)
{
	// DEBUG_FUNC;
	t_lemin					*here;
	int						r_v;

	here = possibility_tree->room;
	// search_init_room(here, daddy, &save);
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
	room_connexions_sort(here);
	if ((r_v = search_unused_rooms(god, possibility_tree)) == SUCCESS)
		return (r_v);
	if ((r_v = search_used_rooms(god, possibility_tree)) == SUCCESS)
		return (r_v);
	// search_uninit_room(here, save);
	return (FAILURE);
}


int			traversal_tree_search(t_god *god, t_data *daddy, int depth)
{
	// DEBUG_FUNC;
	// ft_printf("Depth: %d/%d\n", daddy->depth, depth);
	int i;
	int tt;

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
	int		r_v;

	r_v = FAILURE;
	// DEBUG_FUNC;
	if (here)
	{
		if (here->id == god->extremities[0]->id)
			r_v = SUCCESS;
		if (here->daddy)
		{
			if (!here->daddy->surcharge)
				here->room->last_room = here->daddy->room;
			// else
			// 	ft_printf("%~{255;0;0}SURCHARGE%~{}\n");
			// ft_printf("%s <-- ", here->room->name);
			r_v = update_last_room(god, here->daddy);
		}
		// else
		// 	ft_printf("%s\n", here->room->name);
	}
	return (r_v);
}

int 		ultimate_dispatch_room(t_god *god)
{
	// DEBUG_FUNC;
	int		depth;
	int		is_working;

	depth = 0;
	god->reach_end_room = NULL;
	god->possibility_tree = create_branch(god->extremities[0]);
	is_working = 1;
	while (!god->reach_end_room && is_working)
	{
		is_working = traversal_tree_search(god, god->possibility_tree, depth++);
		// ft_printf("%d TREE BRANCH FOUND AT DEEPNESS %d\n", is_working, depth);
		// ft_press_any_key();
	}
	if (!update_last_room(god, god->reach_end_room))
		ft_printf("%~{}LAST ROOM ISNT END\n");
	// else
		// ft_printf("\n%~{255;0;0}LAST ROOM ISNT END\n\n");
	// ft_printf("%~{}END\n");
	return (is_working);
	//update paths
}


void	loulou(t_god *god)
{
	int ite;
	int save;
	int retry = 3;

	ite = 1;
	// get_dist_from_end(god);
	while (retry && ite)
	{
		// ft_printf("\n%d\t%d/%d\n", retry, god->used_goulots[0], god->goulots);
		save = god->turn;
		// DEBUG_COLOR;
		// time_exe("Setup search");
		clean_search(god);


		// ite = search_a_path(god, god->extremities[0], NULL);
		// time_exe("Algo");
		ite = ultimate_dispatch_room(god);
		if (!ite)
			continue;
		// ft_printf("ITE = %d\n", ite);
		// time_exe("Setup gone");
		clean_gone(god);
		// time_exe("Extract");
		extract_paths(god);
		// time_exe("Setup dist");
		// clean_dist(god);
		// get_dist_from_end_oriented_graph(god);
		// DEBUG_FUNC;
		// ft_printf("turn%d/%d/%d\n", save, god->turn, god->expected_solution);
		if (save <= god->turn)
			retry--;
		else
			retry = 3;
		// time_exe("Free");
		// free_tree(god->possibility_tree);
		// ft_press_any_key();
	}
		// int 		i;
		//
		// i = 0;
		// while (i < god->nb_final_paths)
		// {
		// 	print_this_path(god, god->final_path[i]);
		// 	i++;
		// }
	// time_exe("End");
	// DEBUG_FUNC;
	// mean_connec(god);
	// ft_printf("%d\t%d/%d\n%d\n", retry, god->used_goulots[0], god->goulots, INT_MAX);
}

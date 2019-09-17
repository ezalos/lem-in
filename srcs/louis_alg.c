/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_alg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:45:56 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/14 19:56:08 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			is_room_valid_base(t_god *god, t_lemin *room)
{
	int		r_v;

	r_v = FAILURE;
	if (!room->search)
		if (room->dist_to_end != -1)
			if (room->id != god->extremities[0]->id)
				r_v = SUCCESS;
	return (r_v);
}

int			is_used_room_valid(t_god *god, t_lemin *room)
{
	int		r_v;

	r_v = FAILURE;
	if (is_room_valid_base(god, room))
		if (room->gone)
			if (room->last_room)
				if (room->last_room->id != god->extremities[0]->id)
					r_v = SUCCESS;
	return (r_v);
}

int			is_unused_room_valid(t_god *god, t_lemin *room)
{
	int		r_v;

	r_v = FAILURE;
	if (is_room_valid_base(god, room))
		if (!room->gone)
			r_v = SUCCESS;
	return (r_v);
}

int		is_connec_available(t_lemin *room, int connec)
{
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

int		search_unused_rooms(t_god *god, t_lemin *here)
{
	// DEBUG_FUNC;
	int						r_v;
	int						i;

	i = -1;
	while (here->connexions[++i])
		if (is_unused_room_valid(god, here->connexions[i]) && is_connec_available(here,i))
			if ((r_v = search_a_path(god, here->connexions[i], here)))
			{
				return (r_v);
			}
	return (FAILURE);
}

int		search_used_rooms(t_god *god, t_lemin *here)
{
	// DEBUG_FUNC;
	t_lemin					*surcharge_save;
	int						r_v;
	int						i;

	i = -1;
	while (here->connexions[++i])
		if (is_used_room_valid(god, here->connexions[i]) && is_connec_available(here,i)
	 	&& is_connec_available(here->connexions[i], find_connec_ptr(god, here->connexions[i], here->connexions[i]->last_room)))
		{
			search_init_room(here->connexions[i], here, &surcharge_save);
			// surcharge_save = here->connexions[i]->last_room;
			if ((r_v = search_a_path(god, surcharge_save, surcharge_save->last_room)))
			{
				return (r_v);
			}
			search_uninit_room(here->connexions[i], surcharge_save);
		}
	return (FAILURE);
}

int		search_a_path(t_god *god, t_lemin *here, t_lemin *daddy)
{
	// DEBUG_FUNC;
	t_lemin					*save;
	int						r_v;

	search_init_room(here, daddy, &save);
	if (here->id == god->extremities[1]->id)
	{
		save_solution(god, daddy);
		return (SUCCESS);
	}
	room_connexions_sort(here);
	if ((r_v = search_unused_rooms(god, here)) == SUCCESS)
		return (r_v);
	if ((r_v = search_used_rooms(god, here)) == SUCCESS)
		return (r_v);
	search_uninit_room(here, save);
	return (FAILURE);
}

/*
** int		ultimate_dispatch_room(t_god *god, t_lemin *here, t_lemin *daddy)
** {
** 	//init memory
**
** 	//while (FAILURE || DATA IN STACK)
** 		//fill memory (unused only if no use) & save it
**
** //	pbm: 	!= depth for surcharge
** //
** }
*/

void	loulou(t_god *god)
{
	int ite;
	int save;
	int retry = 3;

	ite = 1;
	// DEBUG_COLOR;
	get_dist_from_end(god);
	while (ite && retry)
	{
		ft_printf("\n%d\t%d/%d\n", retry, god->used_goulots[0], god->goulots);
		// DEBUG_FUNC;
		save = god->turn;
		DEBUG_COLOR;
		clean_search(god);
		ite = search_a_path(god, god->extremities[0], NULL);
		ft_printf("ITE = %d\n", ite);
		clean_gone(god);
		extract_paths(god);
		clean_dist(god);
		get_dist_from_end_oriented_graph(god);
		// DEBUG_FUNC;
		ft_printf("turn%d/%d/%d\n", save, god->turn, god->expected_solution);
		if (save <= god->turn)
			retry--;
		else
			retry = 3;
		// print_paths(god);
	}
	// DEBUG_FUNC;
	mean_connec(god);
	ft_printf("%d\t%d/%d\n%d\n", retry, god->used_goulots[0], god->goulots, INT_MAX);
}

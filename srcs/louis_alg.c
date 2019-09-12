/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_alg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:45:56 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/12 18:40:10 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			is_room_valid_base(t_god *god, t_lemin *room)
{
	if (room->search)
		return(FAILURE);
	if (room->dist_to_end == -1)
		return(FAILURE);
	if (room->id == god->extremities[0]->id)
		return(FAILURE);
	return (SUCCESS);
}

int			is_used_room_valid(t_god *god, t_lemin *room)
{
	if (!is_room_valid_base(god, room))
		return(FAILURE);
	if (!room->gone)
		return (FAILURE);
	if (!room->last_room)
		return (FAILURE);
	if (room->last_room->id == god->extremities[0]->id)
		return (FAILURE);
	return (SUCCESS);
}

int			is_unused_room_valid(t_god *god, t_lemin *room)
{
	if (!is_room_valid_base(god, room))
		return(FAILURE);
	if (room->gone)
		return (FAILURE);
   	return (SUCCESS);
}

int		is_connec_available(t_lemin *room, int connec)
{
	if (room->used[connec] || room->tmp_used[connec])
		return (FAILURE);
	room->tmp_used[connec] = 1;
	return (SUCCESS);
}

int		search_unused_rooms(t_god *god, t_lemin *here)
{
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
	t_lemin					*surcharge_save;
	int						r_v;
	int						i;

	i = -1;
	while (here->connexions[++i])
		if (is_used_room_valid(god, here->connexions[i]) && is_connec_available(here,i)
	 	&& is_connec_available(here->connexions[i], find_connec_ptr(god, here->connexions[i], here->connexions[i]->last_room)))
		{
			surcharge_save = here->connexions[i]->last_room;
			here->connexions[i]->last_room = here;
			here->connexions[i]->search = 1;
			if ((r_v = search_a_path(god, surcharge_save, surcharge_save->last_room)))
			{
				return (r_v);
			}
			here->connexions[i]->last_room = surcharge_save;
			here->connexions[i]->search = 0;
		}
	return (FAILURE);
}

int		search_a_path(t_god *god, t_lemin *here, t_lemin *daddy)
{
	t_lemin					*save;
	int						r_v;

	save = here->last_room;
	here->last_room = daddy;
	here->search = 1;//tmp
	if (here->id == god->extremities[1]->id)
	{
		save_solution(god, daddy);
		return (SUCCESS);
	}
	room_connexions_sort(here);
	if ((r_v = search_unused_rooms(god, here)))
		return (r_v);
	if ((r_v = search_used_rooms(god, here)))
		return (r_v);
	here->last_room = save;
	here->search = 0;
	return (FAILURE);
}

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
		// DEBUG_COLOR;
		clean_search(god);
		ite = search_a_path(god, god->extremities[0], NULL);
		ft_printf("ITE = %d\n", ite);
		clean_gone(god);
		extract_paths(god);
		clean_dist(god);
		get_dist_from_end_oriented_graph(god);
		// DEBUG_FUNC;
		ft_printf("turn%d/%d\n", save, god->turn);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_alg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:45:56 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/10 12:34:29 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void			ft_execute_pile_end_to_start(t_god *god, int depth,
	t_ints pile_a, t_ints pile_b)
{
	t_lemin		*lem_in;
	int				*a;
	int				*b;
	int				i;

	a = (void*)pile_a;
	b = (void*)pile_b;
	while (*a > 0)
	{
		lem_in = god->rooms[pile_a[*a]];
		if (!lem_in || lem_in->gone)
			pile_a[(*a)--] = 0;
		else if (lem_in->id == god->extremities[0]->id)//is it start
		{
			if (!lem_in->dist_to_end || lem_in->dist_to_end > depth)
				lem_in->dist_to_end = depth;
		}
		else if (!lem_in->dist_to_end)
		{
			lem_in->dist_to_end = depth;
			i = -1;
			while (lem_in->connexions[++i])
					pile_b[++(*b)] = ((t_lemin*)lem_in->connexions[i])->id;
		}
		pile_a[(*a)--] = 0;
	}
}

void			get_dist_from_end(t_god *god)
{
	t_ints	pile_a;
	t_ints	pile_b;
	int 	depth;

	depth = 0;
	pile_a = ft_memalloc(sizeof(t_ints) * god->size * 2);
	pile_b = ft_memalloc(sizeof(t_ints) * god->size * 2);
	pile_a[++pile_a[0]] = god->extremities[1]->id;
	while (pile_a[0] || pile_b[0])
	{
		if (depth % 2)
			ft_execute_pile_end_to_start(god, depth, pile_a, pile_b);
		else
			ft_execute_pile_end_to_start(god, depth, pile_b, pile_a);
		depth++;
	}
	ft_memdel((void**)&pile_a);
	ft_memdel((void**)&pile_b);
}

int			room_compare(t_lemin *one, t_lemin *two)
{
//IS ONE BETTER THAN TWO ?
	if (one->dist_to_end == two->dist_to_end)
		return (FAILURE);
	if (one->dist_to_end == -1)
		return (SUCCESS);
	if (two->dist_to_end == -1)
		return (FAILURE);
	if (one->dist_to_end < two->dist_to_end)
		return (FAILURE);
	else
		return (SUCCESS);
}

void		room_connexions_sort(t_lemin *here)
{
	int i;
	int j;

	j = 0;
	while (++j < here->nb_of_connexions)
	{
		if (room_compare(here->connexions[j - 1], here->connexions[j]) == SUCCESS)
		{
			i = 0;
			while (++i < here->nb_of_connexions)
				if (room_compare(here->connexions[i - 1], here->connexions[i]) == SUCCESS)
					ft_swap(&here->connexions[i - 1], &here->connexions[i], sizeof(void*));
			j = 0;
		}
	}
}

int			is_room_valid(t_god *god, t_lemin *room, int surcharge_mode)
{
	if (room->search)
		return(FAILURE);
	if (room->dist_to_end == -1)
		return(FAILURE);
	if (room->id == god->extremities[0]->id)
		return(FAILURE);

	if (!surcharge_mode)
   	{
   		if (room->gone)
   			return (FAILURE);



   		return (SUCCESS);
	}
	else
	{
		if (!room->gone)
			return (FAILURE);
		if (room->surcharged)
			return (FAILURE);


		return (SUCCESS);
	}
}

int			search_a_path(t_god *god, t_lemin *here, t_lemin *daddy)
{
	int							r_v;
	int							i;

	// time_exe(__func__);
	// save_this_path(here, path);

	//init
	here->last_room = daddy;
	here->search = 1;	//need to mark passage differently during search
	if (here->id == god->extremities[1]->id)
		return (SUCCESS);//GET A SAVE OF
	room_connexions_sort(here);
	i = -1;
	while (here->connexions[++i])
		if (is_room_valid(god, here->connexions[i], 0))
			if ((r_v = search_a_path(god, here->connexions[i], here)))
				return (r_v);
	here->surcharged = 1;
	i = -1;
	while (here->connexions[++i])
		if (is_room_valid(god, here->connexions[i], 1))
			if ((r_v = search_a_path(god, here->connexions[i], here)))
				return (r_v);
	here->surcharged = 0;
	here->search = 0;
	here->last_room = NULL;
	return (FAILURE);//NOTHING
}

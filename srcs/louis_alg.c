/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_alg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:45:56 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/09 18:36:51 by ldevelle         ###   ########.fr       */
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

int			search_a_path(t_god *god, t_lemin *here, t_lemin *daddy)
{
	int							r_v;
	int							winner;
	int							i;

	time_exe(__func__);
	// save_this_path(here, path);

	//init
	here->last_room = daddy;
	here->search = 1;	//need to mark passage differently during search
	if (here->id == god->extremities[1]->id)
		return (1);
	//NEED TO HAVE TOOL TO ORDER CONNEXIONS
	

	i = -1;
	winner = -1;
	while (here->connexions[++i] && winner < 0)
		if (!((t_lemin*)here->connexions[i])->gone && !((t_lemin*)here->connexions[i])->search)
			winner = i;
	if (winner != -1)//normally go through
	{
		i = winner;
		while (here->connexions[++i])
			if (!((t_lemin*)here->connexions[i])->gone && !((t_lemin*)here->connexions[i])->search)
				if (here->connexions[winner]->dist_to_end >
					here->connexions[i]->dist_to_end)//need to check more than best
					winner = i;
		if ((r_v = search_a_path(god, here->connexions[winner], here)))
			return (r_v);
	}


	//if nothing: search already passed point
	i = -1;
	winner = -1;
	while (here->connexions[++i] && winner < 0)
		if (((t_lemin*)here->connexions[i])->gone && !((t_lemin*)here->connexions[i])->search
		&& !here->connexions[i]->surcharged //cant surcharge twice
		&& ((t_lemin*)here->connexions[i])->id != god->extremities[0]->id)//cant pass by start
			winner = i;
	here->surcharged = 1;
	if ((r_v = search_a_path(god, here->connexions[winner], here)))
		return (r_v);

	here->search = 0;	//need to mark passage differently during search
	here->last_room = NULL;
	return (0);//NOTHING
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <ythomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:52:16 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/11 14:25:33 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int 			get_next_rooms(t_god *god, t_piles *stack,
	t_ints last_p, t_ints new_p)
{
	int i;
	int j;
	int nb;

	i = 0;
	stack->deep++;
	if (last_p[0] == 0)
		return (stack->finish = 2);
	while (i < last_p[0])
	{
		j = 0;
		while (j < god->rooms[last_p[i + 1]]->nb_of_connexions)
		{
			stack->actual_room = god->rooms[last_p[i + 1]]->id; //last_p list of room to explore, new_p rooms to explore next
			if (god->rooms[last_p[i + 1]]->tmp_used[j] == 0 && god->rooms[last_p[i + 1]]->connexions[j]->gone == 1 //tmp_used is connexion already used ? (1/0)
				&& god->rooms[last_p[i + 1]]->id != god->extremities[0]->id //NE PAS ETRE AU DEBUT
				&& ((god->rooms[last_p[i + 1]]->last_room->surcharged != 1) || ((god->rooms[last_p[i + 1]]->last_room->surcharged == 1)
				&& (god->rooms[last_p[i + 1]]->nb_of_connexions == 2)))//surcharge = remonter un chemin deja utilise. Pour l'instant surcharge unique
				&& is_it_connected(god, god->rooms[last_p[i + 1]]->id, god->rooms[last_p[i + 1]]->connexions[j]->id) == 1 //is room directly connected to other room, and path has been used (int *used;).
				&& god->rooms[last_p[i + 1]]->connexions[j]->id != god->extremities[0]->id //is room inderectly (len 1) connected to START.
				&& god->rooms[last_p[i + 1]]->connexions[j]->id != god->rooms[last_p[i + 1]]->last_room->id //dont go back directly where you are from
				&& god->rooms[last_p[i + 1]]->blocked == 1)//everything set at block, needed to explore
			{
				last_p[0] = last_p[0] + 1;
				nb = last_p[0];
				last_p[nb] = god->rooms[last_p[i + 1]]->connexions[j]->id;
				god->rooms[last_p[i + 1]]->connexions[j]->weight = god->rooms[last_p[i + 1]]->weight - 1;
				god->rooms[last_p[i + 1]]->connexions[j]->last_room = god->rooms[last_p[i + 1]];
				(god->trigger)++;
				god->rooms[last_p[i + 1]]->surcharged = 1;
			}
			j++;
		}
		i++;
	}

	i = 0;
	while (i < last_p[0])
	{
		j = 0;
		while (j < god->rooms[last_p[i + 1]]->nb_of_connexions)
		{
			stack->actual_room = god->rooms[last_p[i + 1]]->id;
			if (god->rooms[last_p[i + 1]]->connexions[j]->gone == 1 && god->rooms[last_p[i + 1]]->tmp_used[j] == 0
				&& god->rooms[last_p[i + 1]]->connexions[j]->id != god->extremities[0]->id
				&& god->rooms[last_p[i + 1]]->last_room != NULL
				&& god->rooms[last_p[i + 1]]->connexions[j]->id != god->rooms[last_p[i + 1]]->last_room->id
				&& (god->rooms[last_p[i + 1]]->nb_of_connexions == 2 || god->rooms[last_p[i + 1]]->last_room->surcharged == 1)
				&& is_it_connected(god, god->rooms[last_p[i + 1]]->id, god->rooms[last_p[i + 1]]->connexions[j]->id) == 0 // A VOIR ET A VERIFIER
				&& ((god->rooms[last_p[i + 1]]->weight + 1 <= god->rooms[last_p[i + 1]]->connexions[j]->weight)
				|| god->rooms[last_p[i + 1]]->connexions[j]->weight == 0))
			{
				gone_is_one(god, stack, new_p, god->rooms[last_p[i + 1]]->connexions[j]->id);
			}
			else if (god->rooms[last_p[i + 1]]->connexions[j]->gone == 0 && god->rooms[last_p[i + 1]]->tmp_used[j] == 0
				&& god->rooms[last_p[i + 1]]->connexions[j]->id != god->extremities[0]->id
				&& god->rooms[last_p[i + 1]]->surcharged == 0)
			{
				gone_is_zero(god, stack, new_p, god->rooms[last_p[i + 1]]->connexions[j]->id);
				if (stack->finish == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (stack->finish);
}

int 			get_faster_path(t_god *god)
{
	t_piles stack;

	init_stack(god->size * 2, &stack, god->extremities[0]->id);
	while (stack.finish == 0)
	{
		if (stack.deep % 2 == 0)
		{
			get_next_rooms(god, &stack, stack.pile_a, stack.pile_b);
			stack.pile_a[0] = 0;
		}
		else if (stack.deep % 2 != 0)
		{
			get_next_rooms(god, &stack, stack.pile_b, stack.pile_a);
			stack.pile_b[0] = 0;
		}
	}
	return (stack.finish);
}

int 			breadth_first_search(t_god *god, int *stat)
{
	int 		nb_finish;
	int 		nb;

	nb_finish = 0;
	while (nb_finish < god->goulots && *stat != 2)
	{
		if ((*stat = get_faster_path(god)) == 1)
		{
			add_path_to_set(god, nb_finish);
			nb_finish++;
			if (which_link_is_surcharged(god, god->paths[nb_finish - 1]) == 1)
				nb_finish = reset_this_set(god, nb_finish);
			else
			{
				if (nb_finish == god->variation &&
				(nb = ft_evaluate_set_of_path(god, nb_finish)) < god->turn)
					save_actual_set(god, nb_finish, nb);
			}
		}
		clear_gone(god);
		refresh_tmp_links(god);
		add_gone(god, nb_finish);
	}
	return (nb_finish);
}

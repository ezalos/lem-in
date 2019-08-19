/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 14:52:16 by ythomas           #+#    #+#             */
/*   Updated: 2019/07/24 14:52:47 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int 			find_link(t_lemin *tmp)
{
	int i;

	i = 0;
	while (i < tmp->last_room->nb_of_connexions)
	{
		if (tmp->last_room->connexions[i]->id == tmp->id)
		{
			//ft_printf("[[[[[%s]]i = %d] nb co = %d]]\n", tmp->last_room->connexions[i]->name, i, tmp->last_room->nb_of_connexions);
			return (i);
		}
		i++;
	}
	return (-1);
}

int  			find_pv_link(t_god *god, t_lemin *tmp, t_piles *stack)
{
	int i;

	i = 0;
	while (i < god->rooms[stack->actual_room]->nb_of_connexions)
	{
		if (god->rooms[stack->actual_room]->connexions[i]->id == tmp->id)
			return (i);
		i++;
	}
	return (-1);
}

void 			add_gone(t_god *god, int nb_paths)
{
	int i;
	int j;
	int size;

	i = 0;
	while (i < nb_paths)
	{
		j = 1;
		size = god->paths[i][0];
		if (size != 0)
			while (j <= size)
			{
				god->rooms[god->paths[i][j]]->gone = 1;
				god->rooms[god->paths[i][j]]->blocked = 1;
				if (god->rooms[god->paths[i][j]]->last_room != NULL)
					god->rooms[god->paths[i][j]]->tmp_used[find_link(god->rooms[god->paths[i][j]])] = 1;
				j++;
			}
		i++;	
	}
}

int 			get_len_path(t_god *god)
{
	int 	i;
	t_lemin 	*tmp;

	i = 0;
	tmp = god->extremities[1];
	while (tmp->last_room != NULL)
	{
		tmp = tmp->last_room;
		i++;
	}
	return (i);
}

void			add_path_to_set(t_god *god, int path)
{
	int i;
	t_lemin *tmp;

	i = get_len_path(god);
	tmp = god->extremities[1];
	god->paths[path][0] = i;
	while (tmp->last_room != NULL)
	{
		god->paths[path][i + 1] = tmp->id;
		tmp->last_room->used[find_link(tmp)] = 1;
		tmp = tmp->last_room;
		i--;
	}
}

void			init_stack(int size, t_piles *stack, int id)
{
	stack->pile_a = ft_memalloc(sizeof(t_ints) * size * 2);
	stack->pile_b = ft_memalloc(sizeof(t_ints) * size * 2);
	stack->pile_a[0] = 1;
	stack->pile_a[1] = id;
	stack->finish = 0;
	stack->deep = 0;
	stack->actual_room = 0;
}

void			gone_is_zero(t_god *god, t_piles *stack, t_ints new_p, int id)
{
	int nb;

	god->rooms[id]->weight = god->rooms[stack->actual_room]->weight + 1;
	god->rooms[id]->last_room = god->rooms[stack->actual_room];
	if (id == god->extremities[1]->id)
	{
		stack->finish = 1;
		return ;
	}
	god->rooms[stack->actual_room]->tmp_used[find_pv_link(god, god->rooms[id], stack)] = 1;
	god->rooms[id]->gone = 1;
	new_p[0] = new_p[0] + 1;
	nb = new_p[0];
	new_p[nb] = id;
}

void			gone_is_one(t_god *god, t_piles *stack, t_ints new_p, int id)
{
	int nb;

	if (god->rooms[id]->weight >= god->rooms[stack->actual_room]->weight + 1 || god->rooms[id]->weight == 0)
	{
		god->rooms[id]->last_room = god->rooms[stack->actual_room];
		god->rooms[id]->weight = god->rooms[id]->last_room->weight + 1;
	}
	god->rooms[stack->actual_room]->tmp_used[find_pv_link(god, god->rooms[id], stack)] = 1;
	new_p[0] = new_p[0] + 1; // probleme a regler ici
	nb = new_p[0];
	new_p[nb] = id;
}

int 			is_it_connected(t_god *god, int room1, int room2)
{
	int i;

	i = 0;
	while (i < god->rooms[room2]->nb_of_connexions)
	{
		if (god->rooms[room2]->connexions[i]->id == god->rooms[room1]->id
			&& god->rooms[room2]->tmp_used[i] == 1)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void			creat_surcharged_link(t_god *god, int room1, int room2)
{
	int pos;

	pos = god->surcharged_link[0] + 1;
	god->surcharged_link[pos] = room1;
	god->surcharged_link[pos + 1] = room2;
	god->surcharged_link[0] = god->surcharged_link[0] + 2;
}

int 			get_next_rooms(t_god *god, t_piles *stack, t_ints last_p, t_ints new_p)
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
			// ft_printf("%d\n", god->rooms[last_p[i + 1]]->tmp_used[j]);
			stack->actual_room = god->rooms[last_p[i + 1]]->id;
			if (god->rooms[last_p[i + 1]]->tmp_used[j] == 0 && god->rooms[last_p[i + 1]]->connexions[j]->gone == 1
				&& god->rooms[last_p[i + 1]]->id != god->extremities[0]->id
				&& ((god->rooms[last_p[i + 1]]->last_room->surcharged != 1) || ((god->rooms[last_p[i + 1]]->last_room->surcharged == 1)
					&& (god->rooms[last_p[i + 1]]->nb_of_connexions == 2)))
				&& is_it_connected(god, god->rooms[last_p[i + 1]]->id, god->rooms[last_p[i + 1]]->connexions[j]->id) == 1
				&& god->rooms[last_p[i + 1]]->connexions[j]->id != god->extremities[0]->id
				&& god->rooms[last_p[i + 1]]->connexions[j]->id != god->rooms[last_p[i + 1]]->last_room->id
				&& god->rooms[last_p[i + 1]]->blocked == 1)
			{
				// ft_printf("%sIIIIIIIIIIIIIIIIIIIIInSIDE\n", god->rooms[last_p[i + 1]]->name); /// GONE IS 3rd CASE
				last_p[0] = last_p[0] + 1;
				nb = last_p[0];
				last_p[nb] = god->rooms[last_p[i + 1]]->connexions[j]->id;
				god->rooms[last_p[i + 1]]->connexions[j]->weight = god->rooms[last_p[i + 1]]->weight - 1;
				god->rooms[last_p[i + 1]]->connexions[j]->last_room = god->rooms[last_p[i + 1]];
				(god->trigger)++;
				god->rooms[last_p[i + 1]]->surcharged = 1;
				// print_surcharged_tab(god);
			}
			// ft_printf("%s connected to %s ? => %d\n", god->rooms[last_p[i + 1]]->name, god->rooms[last_p[i + 1]]->connexions[j]->name, is_it_connected(god, god->rooms[last_p[i + 1]]->id, god->rooms[last_p[i + 1]]->connexions[j]->id));
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
			// ft_printf("room = %s et sa connection j = %s, used = %d gone = %d usrcharged = %d, weight actu %d, weight next %d\n", god->rooms[last_p[i + 1]]->name, god->rooms[last_p[i + 1]]->connexions[j]->name, god->rooms[last_p[i + 1]]->tmp_used[j], god->rooms[last_p[i + 1]]->gone, god->rooms[last_p[i + 1]]->surcharged, god->rooms[last_p[i + 1]]->weight, god->rooms[last_p[i + 1]]->connexions[j]->weight);
			if (god->rooms[last_p[i + 1]]->connexions[j]->gone == 1 && god->rooms[last_p[i + 1]]->tmp_used[j] == 0
				&& god->rooms[last_p[i + 1]]->connexions[j]->id != god->extremities[0]->id
				&& god->rooms[last_p[i + 1]]->last_room != NULL
				&& god->rooms[last_p[i + 1]]->connexions[j]->id != god->rooms[last_p[i + 1]]->last_room->id
				&& (god->rooms[last_p[i + 1]]->nb_of_connexions == 2 || god->rooms[last_p[i + 1]]->last_room->surcharged == 1)
				&& is_it_connected(god, god->rooms[last_p[i + 1]]->id, god->rooms[last_p[i + 1]]->connexions[j]->id) == 0 // A VOIR ET A VERIFIER
				&& ((god->rooms[last_p[i + 1]]->weight + 1 <= god->rooms[last_p[i + 1]]->connexions[j]->weight)
				|| god->rooms[last_p[i + 1]]->connexions[j]->weight == 0))
			{
				// ft_printf("%~{250;100;100}CAS ONE%~{}\n");
					// ft_printf("salle qui pqrt dqns lq fonction %s\n", god->rooms[last_p[i + 1]]->connexions[j]->name);
				gone_is_one(god, stack, new_p, god->rooms[last_p[i + 1]]->connexions[j]->id);
			}
			else if (god->rooms[last_p[i + 1]]->connexions[j]->gone == 0 && god->rooms[last_p[i + 1]]->tmp_used[j] == 0
				&& god->rooms[last_p[i + 1]]->connexions[j]->id != god->extremities[0]->id
				&& god->rooms[last_p[i + 1]]->surcharged == 0)
			{
				// ft_printf("%~{100;100;250}CAS ZERO%~{}\n");
				// ft_printf("salle qui pqrt dqns lq fonction %s\n", god->rooms[last_p[i + 1]]->connexions[j]->name);
				gone_is_zero(god, stack, new_p, god->rooms[last_p[i + 1]]->connexions[j]->id);
				if (stack->finish == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	// int g = 1;
	// 	ft_printf("%d\n", last_p[0]);
	// while (g <= last_p[0])
	// {
	// 	ft_printf("/%s/", god->rooms[last_p[g++]]->name);
	// }
	// ft_printf("\n");
	return (stack->finish);
}

int 			get_faster_path(t_god *god)
{
	t_piles stack;

	init_stack(god->size * 2, &stack, god->extremities[0]->id);
	while (stack.finish == 0)
	{
		//print_tmp_used_link_state(god);
		// ft_printf("DEEP IS ==== %d\n", stack.deep);
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

void			reset_this_set(t_god *god, int nb_finish)
{
	int i;
	int len;
	int j;

	i = 0;
	// ft_printf("==============================RESETTTTTTTTTT======================\n");
	while (i < nb_finish)
	{
		len = god->paths[i][0];
		j = 0;
		while (j <= len)
		{
			god->paths[i][j] = 0;
			j++;
		}
		i++;
	}
	clear_links(god);
}

int 				which_link_is_surcharged(t_god *god, t_ints path)
{
	int i;
	int len;
	int result;

	i = 1;
	len = path[0];
	result = 0;
	while (i < len)
	{
		if (is_it_connected(god, god->rooms[path[i]]->id, god->rooms[path[i + 1]]->id) == 1)
		{
			creat_surcharged_link(god, god->rooms[path[i]]->id, god->rooms[path[i + 1]]->id);
			result = 1;
		}
		i++;
	}
	return (result);
}

void 			save_actual_set(t_god *god, int nb_paths, int nb_of_turn)
{
	int i;
	int j;

	(god->variation)++;
	god->nb_final_paths = nb_paths;
	if (god->final_path != NULL)
	{
		i = -1;
		while (god->final_path[++i] != NULL)
			ft_memdel((void **)&(god->final_path[i]));
		ft_memdel((void *)god->final_path);
	}
	god->turn = nb_of_turn;
	god->final_path = ft_memalloc(sizeof(t_ints *) * (nb_paths + 1));
	i = 0;
	while (i < nb_paths)
	{
		j = 0;
		god->final_path[i] = ft_memalloc(sizeof(t_ints) * (god->size * 2));
		god->final_path[i][0] = god->paths[i][0];
		while (j <= god->paths[i][0])
		{
			god->final_path[i][j + 1] = god->paths[i][j + 1]; 
			j++;
		}
		i++;
	}
	god->final_path[i] = NULL;
}

int 			breadth_first_search(t_god *god)
{
	int 		nb_finish;
	int 		stat;
	int 		nb;

	nb_finish = 0;
	stat = 0;
	god->trigger = 0;
	god->variation = 1;
	while (nb_finish < god->goulots && stat != 2)
	{
		//print_used_link_state(god);
		if ((stat = get_faster_path(god)) == 1)
		{
			add_path_to_set(god, nb_finish); // LINK FAIT ICI
			// print_this_path(god, god->paths[nb_max - 1][nb_finish]);
			nb_finish++;
			if (which_link_is_surcharged(god, god->paths[nb_finish - 1]) == 1)
			{
				reset_this_set(god, nb_finish);
				nb_finish = 0;
			}
			else
			{
				if (nb_finish == god->variation && (nb = ft_evaluate_set_of_path(god, nb_finish)) < god->turn)
					save_actual_set(god, nb_finish, nb);
			}
		}
		//print_paths(god);
		//ft_printf("========== SET FOR %d PATHS ============\n", nb_finish);
		clear_gone(god); // clear gone basic
		//print_surcharged_tab(god);
		refresh_tmp_links(god);
		add_gone(god, nb_finish); // ajout du gone de tout leschemin deja trouve
		//print_used_link_state(god);
	}
	return (nb_finish);
}

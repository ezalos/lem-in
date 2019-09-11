/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_alg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:45:56 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/11 17:25:41 by ldevelle         ###   ########.fr       */
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
			{
				lem_in->dist_to_end = depth;
				lem_in->orientation = depth;
			}
		}
		else if (!lem_in->dist_to_end)
		{
			lem_in->dist_to_end = depth;
			lem_in->orientation = depth;
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

//+1 to depth if normal
//dont allow norml if daddy
//daddy use is -1 depth

// int 			update_dist

int				are_these_room_correctly_oriented(t_lemin *from, t_lemin *to)
{
	if ((from->orientation < to->orientation))
		return (1);
	return (0);
}

int				is_this_extremities(t_god *god, t_lemin *here)
{
	if (here->id == god->extremities[0]->id
	|| here->id == god->extremities[1]->id)
		return (1);
	return (0);

}

void			get_dist_from_end_oriented_graph(t_god *god)
{
	t_lemin 	*here;
	int			action;
	int			i;
	int			j;

	i = -1;
	action = 1;
	god->extremities[1]->dist_to_end = 0;
	while (action)
	{
		action = 0;
		while (++i < god->size)
		{
			here = god->rooms[i];
			if (is_this_extremities(god, here))
				continue;
			if (here->dist_to_end != INT_MAX)
			{
				if (here->last_room)
				{
					if (here->last_room->dist_to_end > here->dist_to_end - 1 && ++action)
						here->last_room->dist_to_end = here->dist_to_end - 1;
				}
				else
				{
					j = -1;
					while (here->connexions[++j])
						if (are_these_room_correctly_oriented(here, here->connexions[j]))
							if (here->connexions[j]->dist_to_end > here->dist_to_end + 1 && ++action)
								here->connexions[j]->dist_to_end = here->dist_to_end + 1;
				}
			}
			else
				action++;
		}
	}
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
	// DEBUG_FUNC;
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

void	save_solution(t_god *god, t_lemin *daddy)
{
	int						r_v;
	int						i;

	r_v = 0;
	if (god->used_goulots[0])
	{
		i = 0;
		while (++i <= god->used_goulots[0])
			if (god->used_goulots[i] == daddy->id)
				r_v++;
		if (!r_v)
			god->used_goulots[++god->used_goulots[0]] = daddy->id;
	}
	else
		god->used_goulots[++god->used_goulots[0]] = daddy->id;
}

int		search_unused_rooms(t_god *god, t_lemin *here)
{
	int						r_v;
	int						i;

	i = -1;
	while (here->connexions[++i])
		if (is_unused_room_valid(god, here->connexions[i]))
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
		if (is_used_room_valid(god, here->connexions[i]))
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

t_ints 			*malloc_paths(t_god *god)
{
	t_ints			*malloc_paths;
	int				i;

	malloc_paths = ft_memalloc(sizeof(t_ints) * (god->goulots + 1));
	i = -1;
	while (++i <= god->goulots)
		malloc_paths[i] = ft_memalloc(sizeof(int) * god->size * 2);
	return (malloc_paths);
}

void		write_path(t_god *god, t_lemin *here, t_ints path)
{
	if (!here)
	{
		// ft_printf("pbm\n");
		return ;
	}
	// ft_printf("%~{?}Room %s\n", here->name);
	if (here->id != god->extremities[0]->id)
		write_path(god, here->last_room, path);
	// ft_printf("%~{}Room %s", here->name);
	here->gone = 1;
	path[++path[0]] = here->id;
	// ft_printf("--\n");
}

void	extract_paths(t_god *god)
{
	t_ints			*path;
	int 			i;
	int 			turn;

	i = 0;
	path = malloc_paths(god);
	while (++i <= god->used_goulots[0])
	{
		write_path(god, god->rooms[god->used_goulots[i]], path[i - 1]);
		path[i - 1][++path[i - 1][0]] = god->extremities[1]->id;
		// ft_printf("PATH LEN : %d\n", path[i - 1][0]);
		// ft_printf("%~{}Room %s\n", god->extremities[1]->name);
		// print_this_path(god, path[i - 1]);
	}
	god->paths = path;
	god->nb_of_paths = god->used_goulots[0];
	if (!god->final_path)
	{
		god->final_path = path;
		god->nb_final_paths = god->used_goulots[0];
		turn = evaluate_set_of_path(god, god->final_path, god->nb_final_paths);
		ft_printf("Anthill solved in %d turns!\n", turn);
		god->turn = turn;
		return ;
	}
	if ((turn = evaluate_set_of_path(god, god->paths, god->nb_of_paths))
	 < evaluate_set_of_path(god, god->final_path, god->nb_final_paths))
	 {
 		god->final_path = god->paths;
 		god->nb_final_paths = god->nb_of_paths;
		god->turn = turn;
	 }
	 ft_printf("\tAnthill solved in %d turns!\n", turn);
}

void	clean_search(t_god *god)
{
	int i;

	i = -1;
	while (++i < god->size)
		god->rooms[i]->search = 0;
}

void 		clean_gone(t_god *god)
{
	int i;

	i = -1;
	while (++i < god->size)
		god->rooms[i]->gone = 0;
}

void 		clean_dist(t_god *god)
{
	int i;

	i = -1;
	while (++i < god->size)
		// if (!god->rooms[i]->gone)
		god->rooms[i]->dist_to_end = INT_MAX;
}

void 		mean_connec(t_god *god)
{
	int i;
	int tt;

	i = -1;
	tt = 0;
	while (++i < god->size)
		tt += god->rooms[i]->nb_of_connexions;
	ft_printf("TT = %d\n", tt);
	tt /= god->size;
	ft_printf("TT = %d\n", tt);
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
		ft_printf("%d\t%d/%d\n", retry, god->used_goulots[0], god->goulots);
		// DEBUG_FUNC;
		save = god->turn;
		// DEBUG_COLOR;
		clean_search(god);
		ite = search_a_path(god, god->extremities[0], NULL);
		// ft_printf("\n\nITE = %d\n\n\n", ite);
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
	// mean_connec(god);
	ft_printf("%d\t%d/%d\n%d\n", retry, god->used_goulots[0], god->goulots, INT_MAX);
}

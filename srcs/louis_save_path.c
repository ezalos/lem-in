/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_save_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:41:34 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/12 18:40:35 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

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

int		find_connec_id(t_god *god, int from, int to)
{
	int i;

	i = -1;
	while (++i < god->rooms[from]->nb_of_connexions)
		if (god->rooms[from]->connexions[i]->id == god->rooms[to]->id)
			return (i);
	return (-1);
}

int		find_connec_ptr(t_god *god, t_lemin *from, t_lemin *to)
{
	int i;

	i = 0;
	while (god->rooms[from->id]->connexions[i] != to
	&& i < god->rooms[from->id]->nb_of_connexions)
		i++;
	if (god->rooms[from->id]->connexions[i] == to)
		return (i);
	return (-1);
}

void	block_path_connections(t_god *god, t_ints path)
{
	int check;
	int i;

	i = 0;
	while (++i <= path[0] - 1)
		if ((check = find_connec_id(god, path[i], path[i + 1])) >= 0)
			god->rooms[path[i]]->used[check] = 1;
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
		block_path_connections(god, path[i - 1]);
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
		// ft_printf("Anthill solved in %d turns!\n", turn);
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
	 // ft_printf("\tAnthill solved in %d turns!\n", turn);
}

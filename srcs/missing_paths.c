/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:16:43 by root              #+#    #+#             */
/*   Updated: 2019/06/01 21:22:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				entries_unused(t_god *god)
{
		int	i;
		int	j;
		int exist;
		int r_v;

		ft_printf("This red entries were not used: ");
		j = -1;
		while (++j < god->entry_points)
		{
			exist = 0;
			i = -1;
			while (god->paths[++i].path)
				if (god->paths[i].path[2] == god->entry_list[j])
					exist = 1;
			if (!exist)
				ft_printf("%~{255;155;155}");
			else
				ft_printf("%~{155;255;155}");
			ft_printf("%d ", god->entry_list[j]);
			if (!exist)
			r_v = god->entry_list[j];
		}
		ft_printf("%~{}\n");
		return (r_v);
}

int				exits_unused(t_god *god)
{
		int	i;
		int	j;
		int exist;
		int r_v;

		ft_printf("This red exits were not used: ");
		j = -1;
		while (++j < god->exit_points)
		{
			exist = 0;
			i = -1;
			while (god->paths[++i].path)
				if (god->paths[i].path[god->paths[i].path[0] - 1] == god->exit_list[j])
					exist = 1;
			if (!exist)
				ft_printf("%~{255;155;155}");
			else
				ft_printf("%~{155;255;155}");
			ft_printf("%d ", god->exit_list[j]);
			if (!exist)
			r_v = god->exit_list[j];
		}
		ft_printf("%~{}\n");
		return (r_v);
}

int				find_the_smallest_path(t_god *god, int missing_paths)
{
	int	i;
	int smallest;

	i = -1;
	smallest = god->size;
	while (++i < god->goulots - missing_paths)
		if (god->paths[i].path[0] < smallest)
			smallest = i;
	ft_printf("Smallest path is the n*%d with a size of %d\n", smallest, god->paths[smallest].path[0]);
	print_this_path(god, &god->paths[smallest]);
	return (smallest);
}

int				block_room_by_room_this_path(t_god *god, int smallest)
{
		int	i;
		int	j;
		t_path *the_choosen_two;

		ft_printf("\n\nLets try to block room by room this path\n");
		i = 1;
		while (++i < god->paths[smallest].path[0])
		{
			the_choosen_two = ft_memalloc(sizeof(t_path));
			clear_gone(god);
			god->rooms[god->paths[smallest].path[i]]->gone = 1;
			if (god->size > 15)
			{
				j = 0;
				while (++j < god->exit_points)
				{
					god->rooms[god->exit_list[j]]->gone = 1;
					ft_printf("We just block room n* %d\n", god->exit_list[j]);
				}
			}
			ft_printf("We just block room n* %d\n", god->paths[smallest].path[i]);
			full_process(god, the_choosen_two);
			print_this_path(god, the_choosen_two);
			ft_memdel((void**)&the_choosen_two);
		}
		ft_printf("\n\nI hope there was a solution here...\n\n\n\n");
		return (1);
}

void				block_this_path(t_god *god, t_path *block)
{
	int i;

	i = 1;
	while (++i < block->path[0])
		god->rooms[block->path[i]]->gone = 1;
}

int				complete_missing_paths(t_god *god, int missing_paths)
{
		// int smallest;
		int unblock;
		t_path *the_choosen_two;
		t_path **new_combi;
		int i;

		ft_printf("Missing paths : %d/%d\n", missing_paths, god->goulots);
		i = -1;
		clear_gone(god);
		clear_data(god);
		if (!god->side)
		{
			unblock = entries_unused(god);
			// ft_printf("EnCan we %d\n", unblock);
			while (++i < god->entry_points)
				if (god->entry_list[i] != unblock)
					god->rooms[god->entry_list[i]]->gone = 1;
		}
		else
		{
			unblock = exits_unused(god);
			// ft_printf("ExCan we %d\n", unblock);
			while (++i < god->exit_points)
				if (god->exit_list[i] != unblock)
					god->rooms[god->exit_list[i]]->gone = 1;
		}
		the_choosen_two = ft_memalloc(sizeof(t_path));
		// ft_printf("*****************************\n");
		if (full_process(god, the_choosen_two))
		{
			new_combi = ft_memalloc(sizeof(void*) * god->goulots);
			new_combi[0] = the_choosen_two;
			print_this_path(god, new_combi[0]);
			clear_gone(god);
			block_this_path(god, the_choosen_two);
			i = 0;
			while (++i < god->goulots)
			{
				new_combi[i] = ft_memalloc(sizeof(t_path));
				if (full_process(god, new_combi[i]))
					print_this_path(god, new_combi[i]);
			}
		}
		ft_memdel((void**)&the_choosen_two);

		// ft_printf("*****************************\n");
		// smallest = find_the_smallest_path(god, missing_paths);
		// block_room_by_room_this_path(god, smallest);
		return (0);
}

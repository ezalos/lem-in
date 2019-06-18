/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:16:43 by root              #+#    #+#             */
/*   Updated: 2019/06/18 20:39:14 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				*entries_unused_tab(t_god *god)
{
		int *unused_tab;
		int	i;
		int	j;
		int exist;
		int r_v;

		ft_printf("This red entries were not used: ");
		j = -1;
		r_v = 0;
		unused_tab = ft_memalloc((god->entry_points + 1) * sizeof(int));
		while (++j < god->entry_points)
		{
			exist = 0;
			i = -1;
			while (god->paths[++i].path)
				if (god->paths[i].path[2] == god->entry_list[j])
					exist = 1;
			if (!exist)
			{
				unused_tab[++(*unused_tab)] = god->entry_list[j];
				ft_printf("%~{255;155;155}");//red
			}
			else
				ft_printf("%~{155;255;155}");//green
			ft_printf("%d ", god->entry_list[j]);
			if (!exist && !r_v)
				r_v = god->entry_list[j];
		}
		ft_printf("%~{}\n");
		ft_printf("Lets force their use by blocking the green ones\n\n");
		return (unused_tab);
}

int				*exits_unused_tab(t_god *god)
{
		int *unused_tab;
		int	i;
		int	j;
		int exist;
		int r_v;

		ft_printf("This red exits were not used: ");
		unused_tab = ft_memalloc((god->exit_points + 1) * sizeof(int));
		j = -1;
		r_v = 0;
		while (++j < god->exit_points)
		{
			exist = 0;
			i = -1;
			while (god->paths[++i].path)
				if (god->paths[i].path[god->paths[i].path[0] - 1] == god->exit_list[j])
					exist = 1;
			if (!exist)
			{
				unused_tab[++(*unused_tab)] = god->exit_list[j];
				ft_printf("%~{255;155;155}");
			}
			else
				ft_printf("%~{155;255;155}");
			ft_printf("%d ", god->exit_list[j]);
			if (!exist && !r_v)
				r_v = god->exit_list[j];
		}
		ft_printf("%~{}\n");
		ft_printf("Lets force their use by blocking the green ones\n\n");
		return (unused_tab);
}

void				block_this_path(t_god *god, t_path *block)
{
	int i;

	i = 1;
	while (++i < block->path[0])
		god->rooms[block->path[i]]->gone = 1;
}

void				unblock_this_path(t_god *god, int *block)
{
	int i;

	i = 0;
	while (++i <= block[0])
		god->rooms[block[i]]->gone = 0;
}

int			*block_room_list(t_god *god, int *entry_list, int *unused_entries)
{
	int	*blocked_rooms;
	int i;
	int j;
	int exist;

	blocked_rooms = ft_memalloc(entry_list[0] * sizeof(int));
	i = 0;
	while (++i <= entry_list[0])
	{
		exist = 0;
		j = 0;
		while (++j <= unused_entries[0])
		{
			if (entry_list[i] == unused_entries[j])
				exist++;
		}
		if (!exist)
		{
			blocked_rooms[++(*blocked_rooms)] = god->rooms[entry_list[i]]->id;
			god->rooms[entry_list[i]]->gone = 1;
		}
	}
	return(blocked_rooms);
}

int				complete_missing_paths(t_god *god, int missing_paths)
{
		int *unblock;
		t_path **new_combi;
		int	*blocked_rooms;
		int i;


		ft_printf("%~{255;155;155}Missing paths estimation : %d/%d%~{}\n", missing_paths, god->goulots);
		clear_gone(god);
		clear_data(god);
		if (!god->side)
		{
			unblock = entries_unused_tab(god);
			blocked_rooms = block_room_list(god, god->entry_t_list, unblock);
		}
		else
		{
			unblock = exits_unused_tab(god);
			blocked_rooms = block_room_list(god, god->exit_t_list, unblock);
		}
		new_combi = ft_memalloc(sizeof(void*) * (god->goulots + 1));
		i = -1;
		while (++i <= god->goulots)
			new_combi[i] = ft_memalloc(sizeof(t_path));
		i = 0;
		while (full_process(god, new_combi[i]))
			i++;
		if (i)
		{
			unblock_this_path(god, blocked_rooms);
			ft_printf("%~{200;200;255}Let's unblock the rooms and complete our search%~{}\n\n");
			while (++i <= god->goulots)
				if (!full_process(god, new_combi[i]))
					break ;
			ft_printf("We found a total of %~{155;155;255}%d%~{} paths :", i - 1);
			if (i >= god->goulots)
				ft_printf("%~{155;255;155}\tThis is a complete set!%~{}\n\n");
			else
				ft_printf("%~{255;155;155}\t%d paths are still missing%~{}\n", god->goulots - (i - 1));
		}
		return (0);
}

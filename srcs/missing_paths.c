/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   missing_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 18:16:43 by root              #+#    #+#             */
/*   Updated: 2019/06/19 00:34:58 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

t_ints			extremities_list_unused(t_god *god)
{
		t_ints	unused_tab;
		int		i;
		int		j;
		int		exist;

		if (god->side)
			ft_printf("This red exits were not used: ");
		else
			ft_printf("This red entries were not used: ");
		j = 0;
		unused_tab = ft_memalloc((god->extremities_list[god->side][0] + 1) * sizeof(int));
		while (++j <= god->extremities_list[god->side][0])
		{
			exist = 0;
			i = -1;
			while (god->paths[++i])
			{
				if (!god->side)
				{
					if (god->paths[i][2] == god->extremities_list[god->side][j]) //path[2] means it looks at the second room of the path, so the one directly connected to start
						exist = 1;
				}
				else
				 	if (god->paths[i][god->paths[i][0] - 1] == god->extremities_list[god->side][j]) //path[god->paths[i].path[0] - 1] means it looks at the before last room of the path, so the one directly connected to end
						exist = 1;
			}
			if (!exist)
			{
				unused_tab[++(*unused_tab)] = god->extremities_list[god->side][j];
				ft_printf("%~{255;155;155}");
			}
			else
				ft_printf("%~{155;255;155}");
			ft_printf("%d ", god->extremities_list[god->side][j]);
		}
		ft_printf("%~{}\n");
		ft_printf("Lets force their use by blocking the green ones\n\n");
		return (unused_tab);
}

void				unblock_this_path(t_god *god, t_ints list_to_unblock)
{
	int i;

	i = 0;
	while (++i <= list_to_unblock[0])
		god->rooms[list_to_unblock[i]]->gone = 0;
}

int			*block_room_list(t_god *god, t_ints room_list, t_ints open_list)
{
	t_ints blocked_rooms;
	int i;
	int j;
	int exist;

	blocked_rooms = ft_memalloc(room_list[0] * sizeof(int));
	i = 0;
	while (++i <= room_list[0])
	{
		exist = 0;
		j = 0;
		while (++j <= open_list[0])
		{
			if (room_list[i] == open_list[j])
				exist++;
		}
		if (!exist)
		{
			blocked_rooms[++(*blocked_rooms)] = god->rooms[room_list[i]]->id;
			god->rooms[room_list[i]]->gone = 1;
		}
	}
	return(blocked_rooms);
}

int				complete_missing_paths(t_god *god, int missing_paths)
{
		t_ints	unblock;
		t_ints	*new_combi;
		t_ints	blocked_rooms;
		int		i;

		ft_printf("%~{255;155;155}Missing paths estimation : %d/%d%~{}\n", missing_paths, god->goulots);
		full_clear(god);
		unblock = extremities_list_unused(god);
		blocked_rooms = block_room_list(god, god->extremities_list[god->side], unblock);
		new_combi = ft_memalloc(sizeof(void*) * (god->goulots + 1));
		i = -1;
		while (++i <= god->goulots)
			new_combi[i] = ft_memalloc(sizeof(int) * god->size);
		i = 0;
		while (full_process(god, new_combi[i]))
			i++;
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
		return (0);
}

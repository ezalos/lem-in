/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:34:40 by root              #+#    #+#             */
/*   Updated: 2019/09/23 20:14:02 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		set_room_in_tab(int place, t_tab *new, t_tab **lem_in)
{
	if (place < 0 || !(*lem_in))
		ft_tabadd_start(lem_in, new, 0);
	else if (place > 0)
		ft_tabadd_end(*lem_in, new, 0);
	else
		ft_tabadd(lem_in, new, 0, 1);
}

int			add_rooms(t_god *god, int place, char *line)
{
	t_tab		**lem_in;
	t_tab		*new;
	t_lemin		*room;
	char		**split;

	lem_in = &god->lem_in;
	if (!(split = ft_strsplit(line, ' ')))
		return (ERROR);
	if (!(room = ft_memalloc(sizeof(t_lemin))))
		return (ERROR);
	if (!(room->name = ft_strdup(split[0])))
		return (ERROR);
	hashtable_append(god->hashtable, room, room->name, ft_strlen(room->name));
	if ((int)ft_strlen(room->name) > god->name_len)
		god->name_len = ft_strlen(room->name);
	room->place = place;
	room->y_coord = ft_atoi(split[1]);
	room->x_coord = ft_atoi(split[2]);
	ft_strdel_multi(4, &split[0], &split[1], &split[2], &split);
	if (!(new = ft_tabnew_ptr(room, sizeof(void*))))
		return (ERROR);
	if (place < 0 || !(*lem_in))
		god->extremities[0] = room;
	set_room_in_tab(place, new, lem_in);
	return (VALID);
}

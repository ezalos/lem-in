/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_room_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 18:12:42 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/24 18:17:17 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			is_room_searched(t_data *baby, int id)
{
	int						r_v;

	r_v = 0;
	if (baby->id == id)
		r_v = 1;
	else if (baby->daddy)
		r_v += is_room_searched(baby->daddy, id);
	return (r_v);
}

int			is_room_valid_base(t_god *god, t_lemin *room, t_data *baby)
{
	int						r_v;

	r_v = FAILURE;
	if (room->id != god->extremities[0]->id)
		if (!is_room_searched(baby, room->id))
			r_v = SUCCESS;
	return (r_v);
}

int			is_used_room_valid(t_god *god, t_lemin *room, t_data *baby)
{
	int						r_v;

	r_v = FAILURE;
	if (is_room_valid_base(god, room, baby))
		if (room->gone)
			if (room->last_room)
				if (room->last_room->id != god->extremities[0]->id)
					r_v = SUCCESS;
	return (r_v);
}

int			is_unused_room_valid(t_god *god, t_lemin *room, t_data *baby)
{
	int						r_v;

	r_v = FAILURE;
	if (is_room_valid_base(god, room, baby))
		if (!room->gone)
			r_v = SUCCESS;
	return (r_v);
}

int			is_connec_available(t_lemin *room, int connec)
{
	if (room->used[connec] || room->tmp_used[connec])
		return (FAILURE);
	room->tmp_used[connec] = 1;
	return (SUCCESS);
}

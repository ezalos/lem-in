/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rooms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 18:34:40 by root              #+#    #+#             */
/*   Updated: 2019/06/19 00:17:07 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int machin(int nb)
{
	static int bg[100000];

	if (bg[nb] == 0)
		bg[nb] = 1;
	else
		return (0);
	return (1);
}

int		add_rooms(t_god *god, int place, int ants_nb, char *line)
{
	t_tab		**lem_in;
	t_tab		*new;
	t_lemin		*room;
	char		**split;
	int			len;
	int			nb;
	static int	err;

	nb = ft_rand(100000, ft_seed_string(line));
	// if (!machin(nb) && ++err)
	// 	ft_printf("%dERROR: %d\t%s\n", err, nb, line);
	time_exe(__func__);
	lem_in = &god->lem_in;
	if (!(split = ft_strsplit(line, ' ')))
		return (ERROR);
	if (!(room = ft_memalloc(sizeof(t_lemin))))
		return (ERROR);
	if (!(room->name = ft_strdup(split[0])))
		return (ERROR);
	if ((int)ft_strlen(room->name) > god->name_len)
		god->name_len = ft_strlen(room->name);
	room->place = place;
	room->y_coord = ft_atoi(split[1]);
	room->x_coord = ft_atoi(split[2]);
	ft_strdel_multi(4, &split[0], &split[1], &split[2], &split);//need to be protected against more than 3 str
	if (!(new = ft_tabnew_ptr(room, sizeof(void*))))
		return (ERROR);
	if (place < 0 || !(*lem_in))
	{
		god->start = room;
		god->extremities[0] = room;
		room->ants = ants_nb;
		ft_tabadd_start(lem_in, new, 0);
	}
	else if (place > 0)
		ft_tabadd_end(*lem_in, new, 0);
	else
	{
		len = ft_tab_lendir(*lem_in, 0);
		if (((t_lemin*)ft_tab_dirth(*lem_in, 0, len - 1)->content)->place == 1)
		{
			ft_tabadd(lem_in, new, 0, len - 1);
		}
		else
		{
			god->end = room;
			god->extremities[1] = room;
			ft_tabadd(lem_in, new, 0, len);
		}
	}
	return (VALID);
	err++;
}

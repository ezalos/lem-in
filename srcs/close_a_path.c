/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_a_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:11:44 by root              #+#    #+#             */
/*   Updated: 2019/05/27 15:00:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

t_tab 	**rooms_saved(void)
{
	// ft_printf("%s\n", __func__);
	static t_tab		*rooms_saved;

	return (&rooms_saved);
}

int			compare_room_access(t_room_access *zero, t_room_access *one)
{
	// ft_printf("%s\n", __func__);
	if (zero->room->gone && one->room->gone)
		return (-1);
	else if (zero->room->gone)
		return (1);
	else if (one->room->gone)
		return (0);
	// ft_printf("Hey\n");
	if (zero->first < one->first)
		return (0);
	else if (zero->first == one->first && zero->second < one->second)
		return (0);
	return (1);
}

void		order_room_access(t_room_access **room_access)
{
	ft_printf("%s\n", __func__);
	int							i;
	int							r_v;

	i = 0;
	while (room_access[++i])
	{
		ft_printf("i = %d\n", i);
		ft_printf("%s[%d;%d]\n", room_access[i - 1]->room->name, room_access[i - 1]->first, room_access[i - 1]->second);
		if ((r_v = compare_room_access(room_access[i - 1], room_access[i])) == 1)
		{
			ft_swap(&room_access[i - 1], &room_access[i], sizeof(t_room_access*));
			i = 0;
		}
		ft_printf("r_v = %d\n\n", r_v);
	}
}

t_room_access		**look_at_adjacent_rooms(t_lemin *here)
{
	ft_printf("%s\n", __func__);
	t_room_access		**room_access;
	int							i;
	int							j;

	room_access = ft_memalloc(sizeof(t_room_access*) * (here->nb_of_connexions + 1));
	i = -1;
	while (++i < here->nb_of_connexions)
		room_access[i] = ft_memalloc(sizeof(t_room_access));
	i = -1;
	j = 0;
	while (here->connexions[++i + j])
		if (!((t_lemin*)here->connexions[i + j])->gone)
		{
			room_access[i]->room = here->connexions[i + j];
			room_access[i]->first = ((t_lemin*)here->connexions[i + j])->from_end;
			room_access[i]->second = ((t_lemin*)here->connexions[i + j])->from_start + ((t_lemin*)here->connexions[i + j])->from_end;
			ft_printf("%s\t%d\t%d\n",room_access[i]->room->name, room_access[i]->first, room_access[i]->second);
		}
		else
			j++;
	ft_printf("i : %d && j : %d\n", i, j);
	if (i - j > 1)
		order_room_access(room_access);
	return (room_access);
}

int		save_this_room(t_room_access **room_access)
{
	ft_printf("%s\n", __func__);
	t_tab		*new;

		if (!(new = ft_tabnew_ptr(room_access, sizeof(t_room_access**))))
			return (ERROR);
		ft_tabadd_start(rooms_saved(), new, 0);
		return (VALID);
}

t_lemin		*choose_best_room(void)
{
	ft_printf("%s\n", __func__);
	t_tab						*now;
	int							r_v;
	int							actual;
	int							winner;
	int							nb_w;
	int							nb_a;

	actual = 0;
	winner = 0;
	nb_w = 0;
	nb_a = 0;
	now = (*rooms_saved());
	while (now)
	{
		r_v = compare_room_access(((t_room_access**)ft_tab_dirth((*rooms_saved()), 0, winner)->content)[nb_w], ((t_room_access**)now->content)[nb_a]);
		if (r_v == 1)
		{
			winner = actual;
			nb_w = 0;
		}
		else if (r_v == -1)
		{
			nb_w++;
		}
		actual++;
		now = now->dir[0];
		ft_printf("r_v : %d\n", r_v);
	}
	now = ft_tab_dirth((*rooms_saved()), 0, winner);
	r_v = nb_w;
	while (((t_room_access**)now->content)[r_v + 1])
	{
		ft_swap(((t_room_access**)now->content)[r_v], ((t_room_access**)now->content)[r_v + 1], sizeof(void*));
		r_v++;
	}
	return(((t_room_access**)now->content)[r_v]->room);
}

int				close_a_path(t_lemin *here)
{
	if (here->gone)
		return (0);
	else
		here->gone = 1;
	if (here->place == 1)
	{
		ft_printf("%~{155;255;155}");
		ft_printf("\n\n%s\n", here->name);
		return (0);
	}
	else if (here->place == -1)
		ft_printf("%~{255;155;155}");
	else
		ft_printf("%~{}");
	ft_printf("\n\n%s\n", here->name);
	save_this_room(look_at_adjacent_rooms(here));
	close_a_path(choose_best_room());
	return (0);
}

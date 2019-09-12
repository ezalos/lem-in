/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:48 by root              #+#    #+#             */
/*   Updated: 2019/09/11 16:19:26 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void			init_used_tab(t_god *god)
{
	int i;

	i = 0;
	while (god->rooms[i])
	{
		god->rooms[i]->used = ft_memalloc(sizeof(int)
		* god->rooms[i]->nb_of_connexions);
		god->rooms[i]->tmp_used = ft_memalloc(sizeof(int)
		* god->rooms[i]->nb_of_connexions);
		god->surcharged_link = ft_memalloc(sizeof(int) * god->size * 2);
		i++;
	}
}

int				init_suit(t_god *god, t_print *print)
{
	god->end = ft_tab_reach_end(god->lem_in, 0)->content;
	god->extremities[1] = ft_tab_reach_end(god->lem_in, 0)->content;
	order_my_little_connexions(god);
	get_rooms_in_tab(god);
	how_many_entries_exits(god);
	if (!god->goulots)
		return (-1);
	*ft_remember_god() = god;
	init_used_tab(god);
	print_whole_buffer(print);
	write(1, "\n", 1);
	return (0);
}

int				init(t_god *god)
{
	t_print		*print;
	char		*line;
	int			ret;

	print = init_print();
	if (parse_ants(god, print) == -1)
		return (-1);
	god->hashtable = hashtable_init();
	while ((ret = ft_gnl(god->fd, &line)) > 0 && is_it_link_part(line) == 0)
	{
		if (parse_rooms(god, print, line) == -1)
			return (-1);
		ft_memdel((void **)&line);
	}
	if (god->dbt != 1 || god->fin != 1)
		return (-1);
	if (ret <= 0)
		return (-1);
	if (parse_links(god, print, line) == -1)
		return (-1);
	if (god->fd != 1)
		close(god->fd);
	if (init_suit(god, print) == -1)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:48 by root              #+#    #+#             */
/*   Updated: 2019/06/24 19:53:32 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		init_used_tab(t_god *god)
{
	int i;

	i = 0;
	while (god->rooms[i])
	{
		god->rooms[i]->used = ft_memalloc(sizeof(int *)
		* god->rooms[i]->nb_of_connexions);
		god->rooms[i]->tmp_used = ft_memalloc(sizeof(int *)
		* god->rooms[i]->nb_of_connexions);
		god->surcharged_link = ft_memalloc(sizeof(t_ints) * god->size * 2);
		i++;
	}
}

t_print 	*init_print(void)
{
	t_print *print;

	print = ft_memalloc(sizeof(t_print));
	print->next = NULL;
	print->index = 0;
	return (print);
}

void 		add_to_buffer(t_print *print, char *str)
{
	int i;
	t_print *tmp;

	tmp = print;
	while (print->next != NULL)
		print = print->next;
	if (ft_strlen(str) + print->index > P_BUFF - 5)
	{
		print->next = init_print();
		print = print->next;
	}
	i = 0;
	while (str[i] != '\0')
		print->buff[print->index++] = str[i++];
	print->buff[print->index++] = '\n';
	print = tmp;
}

int 		init_suit(t_god *god, t_print *print)
{
	time_exe(__func__);
	god->end = ft_tab_reach_end(god->lem_in, 0)->content;
	god->extremities[1] = ft_tab_reach_end(god->lem_in, 0)->content;
	//print_matrix(god->lem_in);
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

int 		init(t_god *god, int fd)
{
	t_print *print;
	char *line;
	int ret;

	time_exe(__func__);
	print = init_print();
	if (parse_ants(god, fd, print) == -1)
		return (-1);
	god->hashtable = hashtable_init();
	while ((ret = ft_gnl(fd, &line)) > 0 && is_it_link_part(line) == 0)
	{
		if (parse_rooms(god, fd, print, line) == -1)
			return (-1);
		ft_memdel((void **)&line);
	}
	if (god->dbt != 1 || god->fin != 1)
		return (-1);
	if (ret <= 0)
		return (-1);
	if (parse_links(god, fd, print, line) == -1)
		return (-1);
	if (fd != 1)
		close(fd);
	if (init_suit(god, print) == -1)
		return (-1);
	return (0);
}

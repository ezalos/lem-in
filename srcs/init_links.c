/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:48 by root              #+#    #+#             */
/*   Updated: 2019/06/14 00:29:20 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			find_room_name(t_tab *lem_in, char *line, size_t dir)
{
	int		i;
	t_tab	*tmp;

	tmp = lem_in;
	i = 0;
	while (tmp)
	{
		if (!ft_strcmp(((t_lemin*)tmp->content)->name, line))
			return (i);
		i++;
		tmp = tmp->dir[dir];
	}
	return (-1);
}


void		***first_call(t_tab *lem_in, t_god *god)
{
	void		***adjacent_matrix;
	int			i;
	int			len;

	len = ft_tab_lendir(lem_in, 0);
	god->size = len;
	adjacent_matrix = ft_memalloc((len + 1) * sizeof(void**));
	i = -1;
	while (++i < len)
	{
		adjacent_matrix[i] = ft_memalloc(len * sizeof(void*));
		((t_lemin*)ft_tab_dirth(lem_in, 0, i)->content)->connexions = adjacent_matrix[i];
	}
	return (adjacent_matrix);
}

int			link_rooms(t_tab *lem_in, char *line, void ****adjacent_matrix, t_god *god)
{
	char		**split;
	int			first;
	int			second;
	int			i;

	time_exe(__func__);
	if (!*adjacent_matrix)
		*adjacent_matrix = first_call(lem_in, god);
	if (!(split = ft_strsplit(line, '-')))
		return (ERROR);
	first = find_room_name(lem_in, split[0], 0);
	second = find_room_name(lem_in, split[1], 0);
	i = 0;
	while ((*adjacent_matrix)[first][i])
		i++;
	(*adjacent_matrix)[first][i] = ft_tab_dirth(lem_in, 0, second)->content;
	i = 0;
	while ((*adjacent_matrix)[second][i])
		i++;
	(*adjacent_matrix)[second][i] = ft_tab_dirth(lem_in, 0, first)->content;
	first = -1;
	while (split[++first])
		ft_memdel((void**)&split[first]);
	ft_memdel((void**)&split);
	return (SUCCESS);
}

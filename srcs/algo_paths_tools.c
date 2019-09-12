/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_paths_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:18:48 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/11 16:06:44 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void				refresh_package(t_god *god, int nb_finish)
{
	clear_gone(god);
	refresh_tmp_links(god);
	add_gone(god, nb_finish);
}

int					get_len_path(t_god *god)
{
	int			i;
	t_lemin		*tmp;

	i = 0;
	tmp = god->extremities[1];
	while (tmp->last_room != NULL)
	{
		tmp = tmp->last_room;
		i++;
	}
	return (i);
}

void				add_path_to_set(t_god *god, int path)
{
	int				i;
	t_lemin			*tmp;

	i = get_len_path(god);
	tmp = god->extremities[1];
	god->paths[path][0] = i;
	while (tmp->last_room != NULL)
	{
		god->paths[path][i + 1] = tmp->id;
		tmp->last_room->used[find_link(tmp)] = 1;
		tmp = tmp->last_room;
		i--;
	}
}

void				save_actual_set(t_god *god, int nb_paths, int nb_of_turn)
{
	int			i;
	int			j;

	(god->variation)++;
	god->nb_final_paths = nb_paths;
	if (god->final_path != NULL)
	{
		i = -1;
		while (god->final_path[++i] != NULL)
			ft_memdel((void **)&(god->final_path[i]));
		ft_memdel((void *)god->final_path);
	}
	god->turn = nb_of_turn;
	god->final_path = ft_memalloc(sizeof(t_ints *) * (nb_paths + 1));
	i = -1;
	while (++i < nb_paths)
	{
		god->final_path[i] = ft_memalloc(sizeof(t_ints) * (god->size * 2));
		god->final_path[i][0] = god->paths[i][0];
		j = -1;
		while (++j <= god->paths[i][0])
			god->final_path[i][j + 1] = god->paths[i][j + 1];
	}
	god->final_path[i] = NULL;
}

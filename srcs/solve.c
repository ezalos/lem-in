/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:35:56 by root              #+#    #+#             */
/*   Updated: 2019/09/19 13:57:12 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				full_process(t_god *god)
{
	int tmp;
	int stat;

	clear_gone(god);
	stat = 0;
	god->trigger = 0;
	god->variation = 1;
	tmp = breadth_first_search(god, &stat);
	return (tmp);
}

void			does_path_exist(t_god *god, int a, int b)
{
	if (is_there_a_path(god, NULL, a, b))
		ft_printf("%~{155;255;155}");
	else
		ft_printf("%~{255;155;155}");
	ft_printf("%d-%d%~{}\n", a, b);
}

void 			init_paths(t_god *god)
{
	int i;

	i = 0;
	god->turn = 1000000000;
	god->final_path = NULL;
	god->nb_final_paths = 0;
	god->paths = ft_memalloc(sizeof(t_ints *) * (god->goulots + 1));
	god->used_goulots = ft_memalloc(sizeof(int) * (god->goulots + 10));
	while (i <= god->goulots)
	{
		god->paths[i] = ft_memalloc(sizeof(t_ints) * god->size * 2);
		i++;
	}
}

int				lets_calcul(t_god *god)
{
	// print_room_infos(god);
	init_paths(god);
	// full_process(god);
	// ft_printf("%s-%s\n", god->extremities[0]->name, god->extremities[1]->name);
	loulou(god);
	// DEBUG_FUNC;
	//ft_printf("[%d]\n", god->turn);
	//print_paths(god);
	//print_final_paths(god);
	return (0);
}

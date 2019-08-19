/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:35:56 by root              #+#    #+#             */
/*   Updated: 2019/06/24 19:48:19 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				full_process(t_god *god, int nb_max)
{
	int tmp;

	clear_gone(god);
	if (nb_max != 1)
	{
		clear_links(god);
		clear_tmp_links(god);
		clean_surcharged_tab(god->surcharged_link);
	}
	// ft_printf("%s\n", __func__);
	// print_name_and_from_dist(god);
	tmp = breadth_first_search(god);
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
	while (i <= god->goulots)
	{
		god->paths[i] = ft_memalloc(sizeof(t_ints) * god->size * 2); // probleme ave clean garbage voir avec LOUIS
		// En fait le probleme vient de l'allocation du 2 eme malloc de god->paths[i] essayer de comprendre pk pour utiliser moins de memoire.
		i++;
	}
}

int				lets_calcul(t_god *god)
{
	time_exe("SOLVE");
	print_room_infos(god);
	how_many_entries_exits(god);
	if (!god->goulots && ft_printf("%~{255;155;155}There is no solution%~{}\n"))
		return (0);
	init_paths(god);
	full_process(god, god->goulots);
	// print_paths(god);
	ft_printf("%~{255;155;155}Nombre de tour trouves [%d]%~{}\n", god->turn);
	//print_final_paths(god);
	return (0);
}

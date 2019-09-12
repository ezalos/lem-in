/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:35:56 by root              #+#    #+#             */
/*   Updated: 2019/09/11 17:26:24 by ythomas          ###   ########.fr       */
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

void			init_paths(t_god *god)
{
	int i;

	i = 0;
	god->turn = 1000000000;
	god->final_path = NULL;
	god->nb_final_paths = 0;
	god->paths = ft_memalloc(sizeof(t_ints *) * (god->goulots + 1));
	while (i <= god->goulots)
	{
		god->paths[i] = ft_memalloc(sizeof(t_ints) * god->size * 2);
		i++;
	}
}

int				lets_calcul(t_god *god)
{
	init_paths(god);
	full_process(god);
	return (0);
}

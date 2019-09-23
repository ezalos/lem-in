/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:35:56 by root              #+#    #+#             */
/*   Updated: 2019/09/23 21:14:56 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				check_start_to_end(t_god *god)
{
	int i;

	i = 0;
	while (i < god->extremities[0]->nb_of_connexions)
	{
		if (god->extremities[0]->connexions[i]->id == god->extremities[1]->id)
		{
			god->all_in_one = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

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
	god->used_goulots = ft_memalloc(sizeof(int) * (god->goulots + 10));
	while (i <= god->goulots)
	{
		god->paths[i] = ft_memalloc(sizeof(t_ints) * god->size * 2);
		i++;
	}
}

int				lets_calcul(t_god *god)
{
	init_paths(god);
	god->all_in_one = 0;
	if (check_start_to_end(god) == 1)
		return (0);
	full_process(god);
	return (0);
}

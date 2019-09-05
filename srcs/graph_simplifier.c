/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_simplifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:45:32 by root              #+#    #+#             */
/*   Updated: 2019/06/02 19:45:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				get_rid_of_dead_ends(t_god *god)
{
	int i;
	int nb;
	int total;

	i = -1;
	nb = 1;
	total = 0;
	while (nb)
	{
		nb = 0;
		while (++i < god->size)
			if (god->rooms[i]->nb_of_connexions == 1 &&
				!god->rooms[i]->place && ++nb)
				god->rooms[i]->connexions[0] = NULL;
		total += nb;
	}
	god->size -= total;
	ft_printf("Dead_ends_remover deleted %~{255;155;155}%d%~{} rooms\n",
		total);
	return (total);
}

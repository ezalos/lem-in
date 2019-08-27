/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_quantity_estimate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:16:14 by root              #+#    #+#             */
/*   Updated: 2019/06/24 19:55:29 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		block_all_rooms_connected(t_lemin *here)
{
	int i;

	i = -1;
	while (here->connexions[++i])
		((t_lemin*)here->connexions[i])->gone = 1;
}

int				how_many_extremities(t_god *god, int side)
{
	int 		i;
	int			name_size;

	name_size = ft_nb_len(god->extremities[side]->id, 10);
	// if (!side)
		// ft_printf("\nStart goulot: ");
	// else
		// ft_printf("  End goulot: ");
	i = -1;
	god->extremities_list[side] = ft_memalloc(sizeof(int*) * (god->extremities[side]->nb_of_connexions + 1));
	while (god->extremities[side]->connexions[++i])
	{
		full_clear(god);
		block_all_rooms_connected(god->extremities[side]);
		((t_lemin*)god->extremities[side]->connexions[i])->gone = 0;
		god->extremities[side]->gone = 1;
		if (alternate_piles(god, ((t_lemin*)god->extremities[side]->connexions[i])->id, god->extremities[!side]->id, 0))
		{
			// ft_printf("%~{155;255;155}");
			god->extremities_list[side][++(*god->extremities_list[side])] = ((t_lemin*)god->extremities[side]->connexions[i])->id;
		}
		// else
			// ft_printf("%~{255;155;155}");
		// ft_printf("%*d%~{} ", name_size, ((t_lemin*)god->extremities[side]->connexions[i])->id);
	}
	return (1);
}

int				how_many_entries_exits(t_god *god)
{
		how_many_extremities(god, 0);
		how_many_extremities(god, 1);
		full_clear(god);
		if (god->extremities_list[1][0] < god->extremities_list[0][0])
		{
			god->goulots = god->extremities_list[1][0];
			god->side = 1;
		}
		else
		{
			god->goulots = god->extremities_list[0][0];
			god->side = 0;
		}
		clear_gone(god);
		//ft_printf("Goulots %d\tEntry %d\tExit %d\n\n", god->goulots, god->extremities_list[0][0], god->extremities_list[1][0]);
		return (god->goulots);
}

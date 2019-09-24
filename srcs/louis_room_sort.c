/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_room_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:58:37 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/24 17:40:44 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			room_compare(t_lemin *one, t_lemin *two)
{
	if (one->dist_to_end == two->dist_to_end)
		return (FAILURE);
	if (one->dist_to_end == -1)
		return (SUCCESS);
	if (two->dist_to_end == -1)
		return (FAILURE);
	if (one->dist_to_end < two->dist_to_end)
		return (FAILURE);
	else
		return (SUCCESS);
}

void		room_connexions_sort(t_lemin *here)
{
	int i;
	int j;

	j = 0;
	while (++j < here->nb_of_connexions)
	{
		if (room_compare(here->connexions[j - 1],
			here->connexions[j]) == SUCCESS)
		{
			i = 0;
			while (++i < here->nb_of_connexions)
				if (room_compare(here->connexions[i - 1],
					here->connexions[i]) == SUCCESS)
					ft_swap(&here->connexions[i - 1],
						&here->connexions[i], sizeof(void*));
			j = 0;
		}
	}
}

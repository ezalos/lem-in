/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:16:14 by root              #+#    #+#             */
/*   Updated: 2019/05/27 12:16:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				how_many_entries_exits(t_god *god)
{
	int i;

		i = 0;
		while (god->start->connexions[i])
			i++;
		god->entry_points = i;
		i = 0;
		while (god->end->connexions[i])
			i++;
		god->exit_points = i;
		if (god->exit_points < god->entry_points)
			god->goulots = god->exit_points;
		else
			god->goulots = god->entry_points;
		ft_printf("Goulots %d\tEntry %d\tExit %d\n", god->goulots, god->entry_points, god->exit_points);
		return (god->goulots);
}

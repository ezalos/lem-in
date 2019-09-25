/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:30:29 by root              #+#    #+#             */
/*   Updated: 2019/09/25 16:55:00 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void			print_room_infos(t_god *god)
{
	int			one_connexion;
	int			two_connexion;
	int			i;

	one_connexion = 0;
	two_connexion = 0;
	i = -1;
	while (++i < god->size)
		if (god->rooms[i]->nb_of_connexions == 1)
			one_connexion++;
		else if (god->rooms[i]->nb_of_connexions == 2)
			two_connexion++;
	ft_printf("\nThis anthill has %~{155;155;255}%d%~{} rooms.\n\
	\t%~{255;155;155}%d%~{} with 1 connexion and %~{255;155;155}%d%~{} \
	with 2 connexions\n\tUseful nb of rooms is %~{155;255;155}%d%~{}\
	/%~{155;155;255}%d%~{}-->%~{255;255;155}%d%%%~{}\n", god->size,
	one_connexion, two_connexion, god->size - (one_connexion + two_connexion),
	god->size, (god->size - (one_connexion + two_connexion)) * 100 / god->size);
	ft_printf("There is %~{155;155;255}%d%~{} ants\n", god->ants);
}

void			print_this_path(t_god *god, t_ints path)
{
	int			j;

	if (path && path[0])
	{
		ft_printf("%~{155;155;255}Path of length %d\n", path[0] - 1);
		j = 0;
		while (++j <= path[0])
		{
			if (god->rooms[path[j]]->id == god->extremities[0]->id)
				ft_printf("%~{255;155;155}");
			else if (god->rooms[path[j]]->id == god->extremities[1]->id)
				ft_printf("%~{155;255;155}");
			else
				ft_printf("%~{?*}", god->rooms[path[j]]);
			ft_printf("%*s%~{}", god->name_len, god->rooms[path[j]]->name);
			if (god->rooms[path[j]]->id != god->extremities[1]->id)
			{
				if (god->rooms[path[j]]->nb_of_connexions < 3)
					ft_printf("%~{50;50;50}");
				ft_printf(" --> %~{}");
			}
		}
		if (path[0])
			ft_printf("\n\n");
	}
}

void			print_final_paths(t_god *god)
{
	int			i;

	i = 0;
	while (i < god->nb_final_paths)
	{
		print_this_path(god, god->final_path[i]);
		i++;
	}
}

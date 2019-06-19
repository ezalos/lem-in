/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:30:29 by root              #+#    #+#             */
/*   Updated: 2019/06/19 14:17:07 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int		print_matrix(t_tab *lem_in)
{
	int				fd;
	t_tab			*tmp;
	t_lemin		*here;
	int				i;
	int				len;

	len = ft_tab_lendir(lem_in, 0);
	fd = ft_strlen(((t_lemin*)lem_in->content)->name);
	// tmp = lem_in;
	// while (tmp)
	// {
	// 	if (fd < (int)ft_strlen(((t_lemin*)lem_in->content)->name))
	// 		fd = ft_strlen(((t_lemin*)lem_in->content)->name);
	// 	tmp = tmp->dir[0];
	// }
	if (fd < 3)
		fd = 3;
	ft_printf("%*s", fd, " ");
	tmp = lem_in;
	while (tmp)
	{
		here = (t_lemin*)(tmp->content);
		ft_printf("%~{?*}%*s%s%*s%~{}", here, fd - (ft_strlen(here->name) / 2), " ", here->name, 1 + fd % 2 + (fd - (fd % 2)) - ((ft_strlen(here->name) / 2) + (ft_strlen(here->name) % 2)), " ");
		tmp = tmp->dir[0];
	}
	tmp = lem_in;
	ft_printf("\n");
	while (tmp)
	{
		here = (t_lemin*)(tmp->content);
		ft_printf("%~{?*}%*s%~{}", here, fd, here->name);
		i = -1;
		while (++i < len)
		{
			if (!here->connexions[i])
			{
				// ft_printf("%~{?*}%-*s%~{}", here->connexions[i], fd, "void");
				ft_printf("%*s%~{80;0;100}x%~{}%*s", fd, " ", fd, " ");
				// break ;
			}
			else
			{
				ft_printf("%~{?*}%*s%~{} ", here, fd, here->name);
				ft_printf("%~{?*}%-*s%~{}", here->connexions[i], fd, ((t_lemin*)here->connexions[i])->name);
			}
		}
		ft_printf("\n");
		tmp = tmp->dir[0];
	}
	return (0);
}

void			print_room_infos(t_god *god)
{
	int	i;
	int one_connexion;
	int two_connexion;

	time_exe("SOLVE");
	one_connexion = 0;
	two_connexion = 0;
	i = -1;
	while (++i < god->size)
		if (god->rooms[i]->nb_of_connexions == 1)
			one_connexion++;
		else if (god->rooms[i]->nb_of_connexions == 2)
			two_connexion++;
	ft_printf("\nThis anthill has %~{155;155;255}%d%~{} rooms.\n\t%~{255;155;155}%d%~{} with 1 connexion and %~{255;155;155}%d%~{} with 2 connexions\n\tUseful nb of rooms is %~{155;255;155}%d%~{}/%~{155;155;255}%d%~{}-->%~{255;255;155}%d%%%~{}\n", god->size, one_connexion, two_connexion, god->size - (one_connexion + two_connexion), god->size, (god->size - (one_connexion + two_connexion)) * 100 / god->size);
	ft_printf("There is %~{155;155;255}%d%~{} ants\n", god->ants);
}

void 			print_this_path(t_god *god, t_ints path)
{
	int			j;
	int			name_size;

	// ft_printf("HEY\n");
	name_size = ft_nb_len(god->end->id, 10);
	if (path && path[0])
	{
		ft_printf("%~{155;155;255}Path of length %d\n", path[0]);
		j = 0;
		while (++j <= path[0])
		{
			if (god->rooms[path[j]]->place == -1)
				ft_printf("%~{255;155;155}");
			else if (god->rooms[path[j]]->place == 1)
				ft_printf("%~{155;255;155}");
			else
				ft_printf("%~{?*}", god->rooms[path[j]]);
			ft_printf("%*d%~{}", name_size, god->rooms[path[j]]->id);
			if (god->rooms[path[j]]->place != 1)
			{
				if (god->rooms[path[j]]->nb_of_connexions < 3)
					ft_printf("%~{50;50;50}");
				ft_printf(" --> ");
			}
		}
		if (path[0])
			ft_printf("\n\n");
	}
}

void 			print_paths(t_god *god)
{
	int 		i;

	i = -1;
	while (++i < god->goulots)
		print_this_path(god, god->paths[i]);
}

void 		print_name_and_from_dist(t_god *god)
{
	t_tab		*tmp;
	t_lemin	*here;
	int len;

	tmp = god->lem_in;
	len = ft_nb_len(god->end->id, 10);
	while (tmp)
	{
		here = tmp->content;
		ft_printf("%~{255;155;255}%*d%~{}(%d)\t", len, here->id, here->gone);
		ft_printf("start: %d\t", here->from[0]);
		ft_printf("end: %d\n", here->from[1]);
		tmp = tmp->dir[0];
	}
	ft_printf("\n");
}

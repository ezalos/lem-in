/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:30:29 by root              #+#    #+#             */
/*   Updated: 2019/06/01 21:17:00 by root             ###   ########.fr       */
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

	tmp = lem_in;
	len = ft_tab_lendir(lem_in, 0);
	fd = ft_strlen(((t_lemin*)lem_in->content)->name);
	if (fd < 3)
		fd = 3;
	ft_printf("%*s", fd, " ");
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

void 			print_this_path(t_god *god, t_path *path)
{
	int			j;
	int			name_size;

	// ft_printf("HEY\n");
	name_size = ft_nb_len(god->end->id, 10);
	if (path && path->path && path->path[0])
	{
		ft_printf("%~{155;155;255}Path of length %d\n", path->path[0]);
		j = 0;
		while (++j <= path->path[0])
		{
			if (god->rooms[path->path[j]]->place == -1)
				ft_printf("%~{255;155;155}");
			else if (god->rooms[path->path[j]]->place == 1)
				ft_printf("%~{155;255;155}");
			else
				ft_printf("%~{?*}", god->rooms[path->path[j]]);
			ft_printf("%*d%~{}", name_size, god->rooms[path->path[j]]->id);
			if (god->rooms[path->path[j]]->place != 1)
				ft_printf(" --> ");
		}
		if (path->path[0])
			ft_printf("\n\n");
	}
}

void 			print_paths(t_god *god)
{
	int 		i;

	i = -1;
	while (++i < god->goulots)
		print_this_path(god, &god->paths[i]);
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

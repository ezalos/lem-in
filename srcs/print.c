/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 00:30:29 by root              #+#    #+#             */
/*   Updated: 2019/06/24 19:48:57 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void	print_used_link_state(t_god *god)
{
	int i;
	int j;

	i = 0;
	while (god->rooms[i])
	{
		j = -1;
		ft_printf("Room %~{255;255;155}%s%~{} a pour connexions : ", god->rooms[i]->name);
		while (++j < god->rooms[i]->nb_of_connexions)
			ft_printf("[%~{255;255;155}%s%~{} = %~{155;155;255}%d%~{}]", god->rooms[i]->connexions[j]->name, god->rooms[i]->used[j]);
		ft_printf("\n");
		i++;
	}
}

void	print_tmp_used_link_state(t_god *god)
{
	int i;
	int j;

	i = 0;
	while (god->rooms[i])
	{
		j = -1;
		ft_printf("Room %~{255;255;155}%s%~{} a pour connexions : ", god->rooms[i]->name);
		while (++j < god->rooms[i]->nb_of_connexions)
			ft_printf("[%~{255;255;155}%s%~{} = %~{155;155;255}%d%~{}]", god->rooms[i]->connexions[j]->name, god->rooms[i]->tmp_used[j]);
		ft_printf("\n");
		i++;
	}
}

void		print_surcharged_tab(t_god *god)
{
	int nb;
	int i;

	nb = god->surcharged_link[0];
	i = 1;
	ft_printf("\n");
	while (i <= nb)
	{
		ft_printf("%~{100;100;200}[%s] %~{}", god->rooms[god->surcharged_link[i]]->name);
		i++;
	}
	ft_printf("\n");
}

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

	name_size = ft_nb_len(god->end->id, 10);
	if (path && path[0])
	{
		ft_printf("%~{155;155;255}Path of length %d\n", path[0] - 1);
		j = 0;
		while (++j <= path[0] + 1)
		{
			if (god->rooms[path[j]]->place == -1)
				ft_printf("%~{255;155;155}");
			else if (god->rooms[path[j]]->place == 1)
				ft_printf("%~{155;255;155}");
			else
				ft_printf("%~{?*}", god->rooms[path[j]]);
			if (!(ft_strcmp(god->rooms[path[j]]->name, "Ioy9")))
					ft_rgb_bcolor(255,255,255);
			ft_printf("%*s%~{}", god->name_len, god->rooms[path[j]]->name);
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

	i = 0;
	while (i < god->goulots)
	{
		print_this_path(god, god->paths[i]);
		i++;
	}
}

void 			print_final_paths(t_god *god)
{
	int 		i;

	i = 0;
	while (i < god->nb_final_paths)
	{
		print_this_path(god, god->final_path[i]);
		i++;
	}
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

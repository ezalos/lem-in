/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:15:14 by ythomas           #+#    #+#             */
/*   Updated: 2019/08/16 13:15:42 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				moove_one_turn(t_god *god, t_print *print)
{
	int i;
	int j;
	int tmp;

	i = -1;
	tmp = 0;
	while (++i < god->nb_final_paths)
	{
		j = god->final_path[i][0];
		while (j > 1)
		{
			if (god->rooms[god->final_path[i][j]]->gen != -1)
			{
				fill_line_buffer(print,
				ft_itoa(god->rooms[god->final_path[i][j]]->gen),
				god->rooms[god->final_path[i][j + 1]]->name);
				god->rooms[god->final_path[i][j + 1]]->gen
				= god->rooms[god->final_path[i][j]]->gen;
				god->rooms[god->final_path[i][j]]->gen = -1;
				tmp++;
			}
			j--;
		}
	}
	return (tmp);
}

int 			push_ants(t_god *god, int *genome,
	int *waiting_ant, t_print *print)
{
	int i;
	int pushed;

	i = 0;
	pushed = 0;
	while (i < god->nb_final_paths)
	{
		if (waiting_ant[i] > 0)
		{
			fill_line_buffer(print, ft_itoa(*genome),
				god->rooms[god->final_path[i][2]]->name);
			god->rooms[god->final_path[i][2]]->gen = *genome;
			(*genome)++;
			(waiting_ant[i])--;
			pushed++; 
		}
		i++;
	}
	return (pushed);
}

int 			*init_waiting_tab(t_god *god)
{
	int *tab;
	int i;
	int len;
	int mod;

	tab = ft_memalloc(sizeof(int *) * god->nb_final_paths);
	i = 0;
	len = 0;
	while (i < god->nb_final_paths)
		len = len + god->final_path[i++][0];
	i = -1;
	if ((mod = ((god->ants + len) % god->nb_final_paths)) == 0)
	{
		while (++i < god->nb_final_paths)
			tab[i] = god->turn - god->final_path[i][0] + 1;
	}
	else
	{
		while (++i < god->nb_final_paths)
			tab[i] = god->turn - god->final_path[i][0];
	}
	if ((mod = ((god->ants + len) % god->nb_final_paths)) != 0)
	{
		i = -1;
		while (++i < mod)
			(tab[i])++;
	}
	return (tab);
}

int				display_result_suit(t_god *god, int *tmp, int *t_ants)
{
	int genome;
	int *waiting_ant;
	t_print print;

	genome = 1;
	print.index = 0;
	waiting_ant = init_waiting_tab(god);
	while (*t_ants > 0 || *tmp > 0)
	{
		*tmp = moove_one_turn(god, &print);
		if (*t_ants != 0)
		{
			*t_ants = *t_ants - push_ants(god, &genome, waiting_ant, &print);
			*tmp = 1;
		}
		else if (*tmp == 0)
			break ;
		print_buffer_with_refresh(&print);
	}
	return (0);
}

int				display_result(t_god *god)
{
	int tmp;
	int t_ants;

	tmp = 0;
	t_ants = god->ants;
	display_result_suit(god, &tmp, &t_ants);
	return (0);
}

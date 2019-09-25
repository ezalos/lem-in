/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:58:43 by ldevelle          #+#    #+#             */
/*   Updated: 2019/09/25 17:14:40 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		sort_t_ints(t_ints *set_of_paths, int nb_of_paths)
{
	int i;
	int j;

	j = 0;
	while (++j < nb_of_paths)
	{
		if (set_of_paths[j][0] < set_of_paths[j - 1][0])
		{
			i = 0;
			while (++i < nb_of_paths)
				if (set_of_paths[i][0] < set_of_paths[i - 1][0])
					ft_swap(&set_of_paths[i],
					&set_of_paths[i - 1], sizeof(void*));
			j = 0;
		}
	}
}

int			send_using_n_path(t_god *god, t_ints *set_of_paths, int quant)
{
	int turn;
	int len_paths;
	int i;

	len_paths = 0;
	i = 0;
	while (i < quant)
	{
		len_paths = len_paths + set_of_paths[i++][0];
	}
	turn = ((god->ants + len_paths) / quant) - 1;
	if (((god->ants + len_paths) % quant) != 0)
		turn++;
	return (turn);
}

int			ft_evaluate_set_of_path(t_god *god, int nb_paths)
{
	int		turn;

	sort_t_ints(god->paths, nb_paths);
	turn = send_using_n_path(god, god->paths, nb_paths);
	return (turn);
}

int			evaluate_set_of_path(t_god *god, t_ints *set_of_paths, int nb_paths)
{
	int		turn;

	sort_t_ints(set_of_paths, nb_paths);
	turn = send_using_n_path(god, set_of_paths, nb_paths);
	return (turn);
}

void		clean_final_path(t_god *god)
{
	int		save;
	int		i;

	save = 10000000;
	i = 0;
	while (save > god->turn && ++i <= god->nb_final_paths)
		save = evaluate_set_of_path(god, god->final_path, i);
	god->nb_final_paths = i;
	god->turn = save;
}

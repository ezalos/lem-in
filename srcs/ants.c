/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:58:43 by ldevelle          #+#    #+#             */
/*   Updated: 2019/06/22 16:10:37 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

// func : donne le nb de ligne pour un set
//
// func : qui imprime la reponse au bon format

/*
** int			cumulative_length_of_n_paths(t_ints *set, int path_quant)
** {
** 	int sum;
** 	int i;
**
** 	sum = 0;
** 	i = -1;
** 	while (++i < path_quant)
** 	{
** 		(void)set;
** 	}
** 	return (sum);
** }
*/

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
					ft_swap(&set_of_paths[i], &set_of_paths[i - 1], sizeof(void*));
			j = 0;
		}
	}
}

int			send_using_n_path(t_god *god, t_ints *set_of_paths, int quant)
{
	int *time_before_arrival;
	int	ants;
	int	i;
	int biggest;
	int	turns;

	time_before_arrival = ft_memalloc(sizeof(int) * (quant + 1));
	i = -1;
	while (++i <= quant)
		time_before_arrival[i] = set_of_paths[i][0] - 1;
	ants = god->ants;
	turns = 0;
	biggest = -1;
	while (ants > 0)
	{
		turns++;
		// ft_printf("Ants: %d\tTurn: %d\n", ants, turns);
		i = -1;
		while (++i <= quant)
			if (!ants)
				break;
			else if (!time_before_arrival[i])
			{
				if (biggest < i)
					biggest = i;
				ants--;
			}
			else
			{
				time_before_arrival[i]--;
				if (!time_before_arrival[i])
					ants--;
			}
	}
	ft_printf("\t%~{155;155;255}Longest path%~{} used is %~{155;155;255}%d%~{}\t with len %~{255;255;155}%d%~{}\n", biggest + 1, set_of_paths[biggest][0] - 1);
	print_this_path(god, set_of_paths[biggest]);
	ft_printf("\t\t%~{155;255;155}It took %~{255;155;255}%d%~{155;255;155} turns\t%~{}%d%~{155;255;155} is excpected%~{}\n\n", turns, god->expected_solution);
	return (turns);
}

int			ft_evaluate_set_of_path(t_god *god, t_ints *set_of_paths)
{
	int		nb_of_paths;
	int		turn;

	nb_of_paths = 0;
	turn = 0;
	while (set_of_paths[nb_of_paths])
		nb_of_paths++;
	ft_printf("%~{255;255;155}Nb of paths: %~{255;155;155}%d%~{}\n", nb_of_paths);
	sort_t_ints(set_of_paths, nb_of_paths);
	nb_of_paths--;
	turn = send_using_n_path(god, set_of_paths, nb_of_paths);
	return (turn);
}

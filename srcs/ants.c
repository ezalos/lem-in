/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:58:43 by ldevelle          #+#    #+#             */
/*   Updated: 2019/06/19 19:32:12 by ldevelle         ###   ########.fr       */
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
	while (++j <= nb_of_paths && set_of_paths[j][0])
	{
		if (set_of_paths[j][0] < set_of_paths[j - 1][0])
		{
			i = 0;
			while (++i <= nb_of_paths && set_of_paths[i][0])
				if (set_of_paths[i][0] < set_of_paths[i - 1][0])
					ft_swap(&set_of_paths[i], &set_of_paths[i - 1], sizeof(void*));
			j = 0;
		}
	}
}

int			ft_evaluate_set_of_path(t_god *god, t_ints *set_of_paths)
{
	int		nb_of_paths;
	int		nb_of_ants;
	int		turn;
	int		i;
	int		index;

	nb_of_paths = 0;
	turn = 0;
	while (set_of_paths[nb_of_paths][0])
	{
		// if (!set_of_paths[nb_of_paths][0])
		// 	set_of_paths[nb_of_paths] = NULL;
		nb_of_paths++;
	}
	ft_printf("Nb of paths : %d\n", nb_of_paths);
	nb_of_paths--;
	sort_t_ints(set_of_paths, nb_of_paths);
	i = -1;
	// while (set_of_paths[++i])
	// 	print_this_path(god, set_of_paths[i]);
	nb_of_ants = god->ants;
	index = -1;
	while (nb_of_ants > 0 && nb_of_paths >= 1)
	{
		if (nb_of_ants > set_of_paths[nb_of_paths][0] - 1 && ++turn)
		{
			ft_printf("%d\tWe currently have %d ants, and are considering path %d of len %d\n", turn, nb_of_ants, nb_of_paths, set_of_paths[nb_of_paths][0]);
			if (index < set_of_paths[nb_of_paths][0])
				index = set_of_paths[nb_of_paths][0];
			else
				index--;
			ft_printf("\t\tWe pushed %d ants\n", nb_of_paths);
			nb_of_ants -= nb_of_paths;
		}
		else
		{
			nb_of_paths--;
		}
	}
	// while (index)
	// {
	// 	turn++;
	// 	index--;
	// }
	ft_printf("Ants: %d : %d\n", nb_of_ants, god->ants);
	ft_printf("Paths: %d\n", nb_of_paths);
	ft_printf("Turns: %d\n", turn);
	ft_printf("Index: %d\n", index);
	return (turn);
}

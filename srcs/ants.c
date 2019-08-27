/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:58:43 by ldevelle          #+#    #+#             */
/*   Updated: 2019/06/24 19:44:03 by ldevelle         ###   ########.fr       */
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
					ft_swap(&set_of_paths[i], &set_of_paths[i - 1], sizeof(void*));
			j = 0;
		}
	}
}

// int			send_using_n_path(t_god *god, t_ints *set_of_paths, int quant)
// {
// 	int *time_before_arrival;
// 	int *sent_ants;
// 	int	ants;
// 	int	i;
// 	int	turns;

// 	time_before_arrival = ft_memalloc(sizeof(int) * (quant + 1));
// 	sent_ants = ft_memalloc(sizeof(int) * (quant + 1));
// 	i = 0;
// 	while (i < quant)
// 	{
// 		time_before_arrival[i] = set_of_paths[i][0];
// 		i++;
// 	}
// 	ants = god->ants;
// 	turns = 0;
// 	while (ants > 0)
// 	{
// 		turns++;
// 		i = 0;
// 		while (i < quant)
// 		{
// 			if (!ants)
// 				break;
// 			else if (!time_before_arrival[i] || !(--time_before_arrival[i]))
// 			{
// 				ants--;
// 				sent_ants[i]++;
// 			}
// 			i++;
// 		}
// 	}
// 	i = -1;
// 	// ft_printf("Ants = [%d]\n", god->ants);
// 	// while (++i < quant && sent_ants[i])
// 	// 	ft_printf("\t%~{255;155;155}%*d ants%~{} has been sent through %~{255;255;155}path %*d%~{} of %~{155;255;255}len %d%~{}\n", ft_nb_len(god->ants, 10), sent_ants[i], ft_nb_len(god->goulots, 10), i, set_of_paths[i][0]);
// 	// ft_printf("\t%~{155;155;255}Longest path%~{} used is %~{155;155;255}%d%~{}\t with len %~{255;255;155}%d%~{}\n", i - 1, set_of_paths[i - 1][0]);
// 	// print_this_path(god, set_of_paths[i - 1]);
// 	// ft_printf("\t%~{155;255;155}It took %~{255;155;255}%d%~{155;255;155} turns.%~{}", turns);
// 	// if (god->expected_solution)
// 	// 	ft_printf("   %~{255;155;255}%d%~{155;255;155} is excpected%~{}", god->expected_solution);
// 	// ft_printf("\n");
// 	ft_printf("[%d]\n", turns);
// 	return (turns);
//}

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
	//ft_printf("new = [%d]\n", turn);
	return (turn);
}

int			ft_evaluate_set_of_path(t_god *god, int nb_paths)
{
	int		turn;

	sort_t_ints(god->paths, nb_paths);
	turn = send_using_n_path(god, god->paths, nb_paths);
	//ft_printf("%d\n", turn);
	//ft_printf("%~{255;255;155}Nb of paths: %~{255;155;155}%d%~{}\n", set);
	return (turn);
}

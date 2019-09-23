/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:27:19 by root              #+#    #+#             */
/*   Updated: 2019/09/23 21:18:47 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			clean_error(void)
{
	ft_clean_garbage();
	write(2, "ERROR\n", 6);
	return (-1);
}

void		reset_all(t_god *god)
{
	int		i;

	i = -1;
	while (++i < god->size)
	{
		god->rooms[i]->weight = 0;
		god->rooms[i]->depth = 0;
		god->rooms[i]->dist_to_end = 0;
		god->rooms[i]->last_room = 0;
		god->rooms[i]->gone = 0;
		god->rooms[i]->search = 0;
	}
	god->used_goulots = 0;
}

int			main(int ac, char **av)
{
	t_god			*god;

	(void)ac;
	god = ft_memalloc(sizeof(t_god));
	god->fd = 0;
	god->visu = 0;
	if (lem_in(god, av) == -1)
		return (clean_error());
	if (lets_calcul(god) == -1)
		return (clean_error());
	if (god->turn - god->expected_solution > 2)
	{
		reset_all(god);
		init_paths(god);
		loulou(god);
	}
	if (!god->visu || god->all_in_one == 1)
		display_result(god);
	// else
	// 	ft_setup_visu(god);
	// print_time();
	ft_printf("turn = %d\t MISSING : %d\n", god->turn, god->turn - god->expected_solution);
	// ft_add_to_file("./data/missing_turns_louis", ft_strjoin_multi(3, av[1], " :\t", ft_nb_to_a(god->turn - god->expected_solution, 10)));
	ft_clean_garbage();
	return (0);
}

//in 42 lemin tools: ./checker.sh ../lem-in maps/valid/map_33

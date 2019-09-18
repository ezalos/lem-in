/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:27:19 by root              #+#    #+#             */
/*   Updated: 2019/09/18 18:24:40 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int 	clean_error(void)
{
	ft_clean_garbage();
	write(2, "ERROR\n", 6);
	return (-1);
}

int		main(int ac, char **av)
{
	t_god			*god;
	int				fd;

	(void)ac;
	fd = 0;
	god = ft_memalloc(sizeof(t_god));
	god->visu = 0;
	if (lem_in(god, av, fd) == -1)
		return (clean_error());
	if (lets_calcul(god) == -1)
		return (clean_error());
	// if (!god->visu)
	// 	display_result(god);
	// else
	// 	ft_setup_visu(god);
	// print_time();
	// ft_printf("turn = %d\t MISSING : %d\n", god->turn, god->turn - god->expected_solution);
	// ft_add_to_file("./data/missing_turns", ft_strjoin_multi(3, av[1], " :\t", ft_nb_to_a(god->turn - god->expected_solution, 10)));
	ft_clean_garbage();
	return (0);
}

//in 42 lemin tools: ./checker.sh ../lem-in maps/valid/map_33

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:27:19 by root              #+#    #+#             */
/*   Updated: 2019/09/30 16:06:35 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			clean_error(void)
{
	ft_clean_garbage();
	write(2, "ERROR\n", 6);
	return (-1);
}

double		total_time_prog(void)
{
	static double	init;
	double			m;

	if (!init)
		init = ((double)(clock()));
	m = ((double)(((double)(clock())) - init)) / (CLOCKS_PER_SEC);
	return (m);
}

void		print_infos(t_god *god, char **av)
{
	ft_printf("ANT: %d\n", god->ants);
	ft_printf("%~{}turn = %4d \tMISSING : %2d\n%f\tY? : %d/(%d)\n",\
	god->turn, god->turn - god->expected_solution, total_time_prog(),\
	god->yohan, god->save_turn);
	print_final_paths(god);
	if (0)
	{
		ft_add_to_file("./data/missing_turns_louis",\
		ft_strjoin_multi(3, av[1], " :\t",\
			ft_nb_to_a(god->turn - god->expected_solution, 10)));
	}
}

void		create_data(t_god *god)
{
	char	*str;
	int		fd_in;
	int		fd_out;

	if (god->expected_solution != ERROR_EX_SOLUTION)
	{
		ft_add_to_file("./data/data.lem-in",\
		ft_strjoin_multi(3,\
			ft_nb_to_a(god->turn - god->expected_solution, 10),\
			"\t:\t", ft_nb_to_a((int)(total_time_prog() * (double)1000), 10)));
		if (god->turn - god->expected_solution > 10)
		{
			fd_out = ft_create_new_file("./too_much");
			fd_in = open(god->file, O_RDONLY);
			while (ft_gnl(fd_in, &str))
				ft_printf("%~.*%s\n", fd_out, str);
		}
	}
}

int			main(int ac, char **av)
{
	t_god			*god;

	(void)ac;
	total_time_prog();
	god = ft_memalloc(sizeof(t_god));
	if (lem_in(god, av) == -1)
		return (clean_error());
	if (lets_calcul(god) == -1)
		return (clean_error());
	if (god->expected_solution != ERROR_EX_SOLUTION
	&& god->turn - god->expected_solution > 2)
		loulou(god);
	if (0)
		print_infos(god, av);
	if (!god->visu || god->all_in_one == 1)
	{
		display_result(god);
		create_data(god);
	}
	else
		ft_setup_visu(god);
	ft_clean_garbage();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:27:19 by root              #+#    #+#             */
/*   Updated: 2019/09/24 14:07:43 by ldevelle         ###   ########.fr       */
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
		// god->rooms[i]->weight = 0;
		// god->rooms[i]->depth = 0;
		// god->rooms[i]->dist_to_end = 0;
		god->rooms[i]->last_room = 0;
		god->rooms[i]->gone = 0;
		// god->rooms[i]->search = 0;
	}
	god->used_goulots = 0;
}

void			loulou_init_paths(t_god *god)
{
	int i;

	i = 0;
	god->paths = ft_memalloc(sizeof(t_ints *) * (god->goulots + 1));
	god->used_goulots = ft_memalloc(sizeof(int) * (god->goulots + 10));
	while (i <= god->goulots)
	{
		god->paths[i] = ft_memalloc(sizeof(t_ints) * god->size * 2);
		i++;
	}
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

int			main(int ac, char **av)
{
	t_god			*god;

	(void)ac;
	total_time_prog();
	god = ft_memalloc(sizeof(t_god));
	god->fd = 0;
	god->visu = 0;
	if (lem_in(god, av) == -1)
		return (clean_error());
	if (lets_calcul(god) == -1)
		return (clean_error());

	// int i;
	// i = 0;
	// while (i < god->nb_final_paths)
	// {
	// 	print_this_path(god, god->final_path[i]);
	// 	i++;
	// }
	ft_printf("%~{}turn = %d\t MISSING : %d\n%f\n", god->turn, god->turn - god->expected_solution, total_time_prog());
	if (god->expected_solution != ERROR_EX_SOLUTION && god->turn - god->expected_solution > 2)
	{
		reset_all(god);
		loulou_init_paths(god);
		ft_printf("%p & %d\n", god->final_path, god->nb_final_paths);
		loulou(god);
	}
	if (!god->visu || god->all_in_one == 1)
		display_result(god);
	else
		ft_setup_visu(god);
	// print_time();
	ft_printf("%~{}turn = %d\t MISSING : %d\n%f\n", god->turn, god->turn - god->expected_solution, total_time_prog());
	// ft_add_to_file("./data/missing_turns_louis", ft_strjoin_multi(3, av[1], " :\t", ft_nb_to_a(god->turn - god->expected_solution, 10)));
	ft_clean_garbage();
	return (0);
}

//in 42 lemin tools: ./checker.sh ../lem-in maps/valid/map_33

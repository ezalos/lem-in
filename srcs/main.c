/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:27:19 by root              #+#    #+#             */
/*   Updated: 2019/06/24 19:53:11 by ldevelle         ###   ########.fr       */
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
	if (!god->visu)
		display_result(god);
	else
		ft_setup_visu(god);
	//print_time();
	ft_printf("turn = %d\n", god->turn);
	ft_clean_garbage();
	return (0);
}

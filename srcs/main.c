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

	fd = 0;
	god = ft_memalloc(sizeof(t_god));
	if (ac < 2)
	{
		if (init(god, fd) == -1)
			return (clean_error());
	}
	else if (ac == 2)
	{
		if ((fd = open(av[1], O_RDONLY)) <= 0 || init(god, fd) == -1)
			return (clean_error());
	}
	else
		return (0);
	if (lets_calcul(god) == -1)
		return (clean_error());
	display_result(god, av);
	print_time();
	ft_clean_garbage();
	return (0);
}

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

int		main(int ac, char **av)
{
	t_god			*god;
	int				fd;

	if (ac != 2)
		return (0);
	time_exe("INIT");
	if ((fd = open(av[1], O_RDONLY)) > 0)
	{
		god = init(fd);
		lets_calcul(god);
	}
	print_time();
	ft_clean_garbage();
	return (0);
}

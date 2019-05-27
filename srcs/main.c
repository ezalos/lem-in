/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:27:19 by root              #+#    #+#             */
/*   Updated: 2019/05/25 15:58:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int		main(int ac, char **av)
{
	t_god			*god;
	int				fd;

	if (ac != 2)
		return (0);
	if ((fd = open(av[1], O_RDONLY)) > 0)
	{
		god = init(fd);
		lets_calcul(god);
	}
	return (0);
}

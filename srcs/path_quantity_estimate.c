/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_quantity_estimate.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:16:14 by root              #+#    #+#             */
/*   Updated: 2019/09/12 14:24:27 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				how_many_entries_exits(t_god *god)
{
	if (god->extremities[0]->nb_of_connexions
		< god->extremities[1]->nb_of_connexions)
		god->goulots = god->extremities[0]->nb_of_connexions;
	else
		god->goulots = god->extremities[1]->nb_of_connexions;
	return (god->goulots);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:38:39 by ythomas           #+#    #+#             */
/*   Updated: 2019/08/30 14:38:43 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int 			get_len_actual_path(t_visu *visu, int i)
{
	int j;

	j = 0;
	while (visu->paths[i][j])
		j++;
	return (j);
}

void			calculate_coord_last_room(t_visu *visu)
{
	int len;
	double rate_y;

	rate_y = ((H_SCREEN - 100.0) / (double)visu->nb_h);
	len = get_len_actual_path(visu, 0);
	visu->paths[0][len - 1]->y = ((double)visu->nb_h * (rate_y)) + 50.0;
	visu->paths[0][len - 1]->x = ((W_SCREEN - 100.0) / 2.0) + 50.0;
}

void 			calculate_coord(t_visu *visu, int i, int j)
{
	int len;
	double rate_y;

	len = get_len_actual_path(visu, i);
	rate_y = ((H_SCREEN - 100.0)/ (double)len);
	visu->paths[i][j]->y = ((double)j * (rate_y)) + 50.0;
	if (i == 0)
		visu->paths[i][j]->x = ((W_SCREEN - 100.0) / 2.0) + 50.0;
	else if (i % 2 != 0)
	{
		visu->paths[i][j]->x = (((W_SCREEN - 100.0) / 2.0) + (visu->range * visu->rate_x)) + 50.0;
		//ft_printf("%s :  x = %.1f, y = %.1f\n", visu->paths[i][j]->name, visu->paths[i][j]->x, visu->paths[i][j]->y);
	}
	else
	{
		visu->paths[i][j]->x = (((W_SCREEN - 100.0) / 2.0) - (visu->range * visu->rate_x)) + 50.0;
		//ft_printf("%s :  x = %.1f, y = %.1f\n", visu->paths[i][j]->name, visu->paths[i][j]->x, visu->paths[i][j]->y);
	}
}

void			init_new_coord(t_visu *visu)
{
	int i;
	int j;

	i = 0;
	calculate_coord(visu, 0, 0);
	calculate_coord_last_room(visu);
	visu->range = 1.5;
	while (visu->paths[i])
	{
		j = 1;
		while (visu->paths[i][j + 1] != NULL)
		{
			calculate_coord(visu, i, j);
			j++;
		}
		if (i != 0 && i % 2 == 0)
			visu->range += 1.5;
		i++;
	}
}

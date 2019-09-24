/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <ythomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:38:39 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/24 18:15:57 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"
#include <math.h>

int				get_len_actual_path(t_visu *visu, int i)
{
	int j;

	j = 0;
	while (visu->paths[i][j])
		j++;
	return (j);
}

void			calculate_coord_last_room(t_visu *visu)
{
	double	rate_y;
	int		i;
	int		j;

	rate_y = ((visu->screen_h - 100.0) / (double)visu->nb_h);
	i = 0;
	while (visu->paths[i])
	{
		j = 0;
		while (visu->paths[i][j])
			j++;
		visu->paths[i][j - 1]->y = ((double)visu->nb_h * (rate_y)) + 50.0;
		visu->paths[i][j - 1]->z = visu->centre;
		visu->paths[i][j - 1]->x = visu->centre;
		i++;
	}
}

void			calculate_coord(t_visu *visu, int i, int j)
{
	int len;
	int rate_y;

	len = get_len_actual_path(visu, i);
	rate_y = ((visu->screen_h - 100.0) / (double)len);
	visu->paths[i][j]->y = ((double)j * (rate_y)) + 50.0;
	visu->paths[i][j]->x = visu->tmpx;
	visu->paths[i][j]->z = visu->tmpz;
}

void			calculate_coord_firsts_rooms(t_visu *visu)
{
	int i;

	i = 1;
	visu->paths[0][0]->x = visu->centre;
	visu->paths[0][0]->y = 50;
	visu->paths[0][0]->z = visu->centre;
	while (visu->paths[i])
	{
		visu->paths[i][0]->x = visu->paths[0][0]->x;
		visu->paths[i][0]->y = visu->paths[0][0]->y;
		visu->paths[i][0]->z = visu->paths[0][0]->z;
		i++;
	}
}

void			init_new_coord(t_visu *visu)
{
	int i;
	int j;

	i = 0;
	visu->centre = visu->screen_w / 2.0;
	calculate_coord_firsts_rooms(visu);
	calculate_coord_last_room(visu);
	while (visu->paths[i])
	{
		j = 1;
		visu->tmpx = visu->centre + visu->rayon * cos(
			(double)i * 2.0 * M_PI / (double)visu->nb_paths);
		visu->tmpz = visu->centre + visu->rayon * sin(
			(double)i * 2.0 * M_PI / (double)visu->nb_paths);
		while (visu->paths[i][j + 1] != NULL)
		{
			calculate_coord(visu, i, j);
			j++;
		}
		i++;
	}
}

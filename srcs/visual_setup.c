/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <ythomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 16:59:16 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/30 16:08:58 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				get_max_room_in_path(t_god *god)
{
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	while (i < god->nb_final_paths)
	{
		if (god->final_path[i][0] > tmp)
			tmp = god->final_path[i][0];
		i++;
	}
	return (tmp + 1);
}

int				init_visu_paths(t_god *god, t_visu *visu)
{
	int i;
	int j;

	i = 0;
	while (i < visu->nb_paths)
	{
		visu->paths[i] = ft_memalloc(sizeof(void *)
			* (god->final_path[i][0] + 2));
		j = 0;
		while (j <= god->final_path[i][0])
		{
			visu->paths[i][j] = ft_memalloc(sizeof(t_room));
			visu->paths[i][j]->x = 0.0;
			visu->paths[i][j]->y = 0.0;
			visu->paths[i][j]->z = 0.0;
			visu->paths[i][j]->name = ft_strdup(
				god->rooms[god->final_path[i][j + 1]]->name);
			visu->paths[i][j]->nb_rooms = god->final_path[i][0] + 1;
			j++;
		}
		visu->paths[i][j] = NULL;
		i++;
	}
	visu->paths[i] = NULL;
	return (0);
}

int				ft_setup_visu(t_god *god)
{
	t_visu	*visu;

	if (god->nb_final_paths == 0)
		return (ft_printf("MAP HAS NO SOLUTION\n"));
	clean_final_path(god);
	visu = malloc(sizeof(t_visu));
	visu->nb_paths = god->nb_final_paths;
	visu->flux = init_waiting_tab(god);
	visu->paths = ft_memalloc(sizeof(void *) * (visu->nb_paths + 1));
	visu->ants = god->ants;
	visu->turn = god->turn;
	visu->nb_h = get_max_room_in_path(god);
	visu->screen_h = visu->nb_h * 200.0;
	visu->screen_w = W_SCREEN - 100;
	if (init_visu_paths(god, visu) == -1)
		return (-1);
	visu->rayon = visu->screen_w / 100.0 + (100 * visu->nb_paths);
	init_new_coord(visu);
	launch_visual(visu);
	return (0);
}

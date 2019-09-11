/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_visual.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:13:08 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/09 16:13:09 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int 			ft_get_key(int key, t_visu *visu)
{
	if (key == 53)
		exit(EXIT_SUCCESS);
	return (0);
}

int 			launch_visual(t_visu *visu)
{
	void *ptr;
	void *window;
	int i;
	int j;


	ptr = mlx_init();
	window = mlx_new_window(ptr, (int)W_SCREEN, (int)H_SCREEN, "test");
	i = 0;
	while (visu->paths[i])
	{
		j = 0;
		while (visu->paths[i][j])
		{
			mlx_pixel_put(ptr, window, visu->paths[i][j]->x, visu->paths[i][j]->y, 0xffeeff);
			j++;
		}
		i++;
	}
	mlx_hook(window, 2, (1L << 0), ft_get_key, visu);
	mlx_loop(ptr);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   louis_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:41:35 by ezalos            #+#    #+#             */
/*   Updated: 2019/09/18 09:25:21 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

t_data		*create_branch(t_lemin *room)
{
	t_data	*branch;

	branch = ft_memalloc(sizeof(t_data));
	branch->room = room;
	branch->baby = ft_memalloc(sizeof(t_data*) * 2);
	branch->baby[NORMAL] = ft_memalloc(sizeof(t_data) * (room->nb_of_connexions + 1));
	branch->baby[SURCHARGE] = ft_memalloc(sizeof(t_data) * (room->nb_of_connexions + 1));
	branch->id = room->id;
	return (branch);
}

void		add_to_tree(t_data *daddy, t_data *baby, int mode)
{
	int		i;

	i = 0;
	while (daddy->baby[mode][i])
		i++;
	if (i >= daddy->room->nb_of_connexions)
		ft_printf("%s: %s\n", __func__, "More child than possible");
	daddy->baby[mode][i] = baby;
	baby->depth = daddy->depth + 1;
	baby->daddy = daddy;
	if (mode == SURCHARGE)
	{
		baby->surcharge = SURCHARGE;
		// baby->depth = daddy->depth - 1;
		//NEED TO MAKE SURCHARGE GROW UNITL EQUAL
	}
	else
	{
		baby->surcharge = NORMAL;
		// baby->depth = daddy->depth + 1;
	}
}

void		save_to_tree(t_data *daddy, t_lemin *room, int mode)
{
	// DEBUG_FUNC;
	t_data *baby;

	// ft_printf("SAVE ROOM %s %d\n", room->name, mode);
	baby = create_branch(room);
	add_to_tree(daddy, baby, mode);
}

void		free_elmnt(t_data *branch)
{
	ft_memdel((void**)&branch->baby[SURCHARGE]);
	ft_memdel((void**)&branch->baby[NORMAL]);
	ft_memdel((void**)&branch->baby);
	ft_memdel((void**)&branch);
}

void		free_tree(t_data *daddy)
{
	int i;

	i = -1;
	while (daddy->baby[NORMAL][++i])
		free_tree(daddy->baby[NORMAL][i]);
	i = -1;
	while (daddy->baby[SURCHARGE][++i])
		free_tree(daddy->baby[SURCHARGE][i]);
	free_elmnt(daddy);
}

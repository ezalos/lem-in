/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_spe_cases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <ythomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 12:21:33 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/24 12:17:17 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void			add_buffer(t_print *print, char *str)
{
	int			i;
	t_print		*tmp;

	tmp = print;
	while (print->next != NULL)
		print = print->next;
	if (ft_strlen(str) + print->index > P_BUFF - 5)
	{
		print->next = init_print();
		print = print->next;
	}
	i = 0;
	while (str[i] != '\0')
		print->buff[print->index++] = str[i++];
	print = tmp;
}

void			display_all_in_one(t_god *god, int t_ants)
{
	t_print			*print;
	int				i;

	print = init_print();
	i = 1;
	while (i <= t_ants)
	{
		if (i != 1)
			add_buffer(print, " ");
		add_buffer(print, "L");
		add_buffer(print, ft_itoa(i));
		add_buffer(print, "-");
		add_buffer(print, god->extremities[1]->name);
		i++;
	}
	add_buffer(print, "\n");
	print_whole_buffer(print);
}

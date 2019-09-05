/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:07:27 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/05 12:07:29 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

t_print 	*init_print(void)
{
	t_print *print;

	print = ft_memalloc(sizeof(t_print));
	return (print);
}

void 		print_whole_buffer(t_print *print)
{
	t_print *tmp;

	tmp = print;
	while (tmp != NULL)
	{
		write(1, tmp->buff, tmp->index);
		tmp = tmp->next;
	}
}

void 		add_to_buffer(t_print *print, char *str)
{
	int i;
	t_print *tmp;

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
	print->buff[print->index++] = '\n';
	print = tmp;
}

void			print_buffer_with_refresh(t_print *print)
{
	int i;

	if (print->index != 0)
		(print->index)--;
	print->buff[print->index] = '\n';
		(print->index)++;
	write(1, print->buff, print->index);
	i = 0;
	while (i < print->index)
		print->buff[i++] = '\0';
	print->index = 0;
}

void 			fill_line_buffer(t_print *print, char *nb, char *name)
{
	int i;
	int j;

	print->buff[print->index] = 'L';
	(print->index)++;
	i = 0;
	while (nb[i] != '\0')
	{
		print->buff[print->index] = nb[i++];
		(print->index)++;
	}
	print->buff[print->index] = '-';
	(print->index)++;
	j = 0;
	while (name[j] != '\0')
	{
		print->buff[print->index] = name[j++];
		(print->index)++;
	}
	print->buff[print->index] = ' ';
	(print->index)++;
}

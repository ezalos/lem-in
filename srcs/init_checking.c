/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_checking.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:40:55 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/03 13:40:56 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int 		is_it_link_part(char *str)
{
	int i;

	i = 0;
	if (str[i] == '#' || str[i] == 'L')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

int 		check_room_parsing_suit(char *str, int i, int step)
{
	if (str[i] == ' ' && str[i + 1] == ' ')
		return (-1);
	if ((int)(str[i]) < 32 || (int)(str[i]) >= 127)
		return (-1);
	if (str[i] == '-' && step == 0)
		return (-1);
	return (0);
}

int 		check_room_parsing(t_print *print, char *str)
{
	int i;
	int step;

	i = 0;
	step = 0;
	if (str[i] == 'L')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\0')
			step++;
		else if (check_room_parsing_suit(str, i, step) == -1)
			return (-1);
		if (step > 0 && (str[i] == '-' || str[i] == '+')
		&& (str[i + 1] == '-' || str[i + 1] == '+'))
			return (-1);
		if (step > 0 && !(str[i] == '-' || str[i] == '+'
		|| str[i] == ' ' || (str[i] >= '0' && str[i] <= '9')))
			return (-1);
		i++;
	}
	if (step != 2)
		return (-1);
	add_to_buffer(print, str);
	return (0);
}

int 		check_link_parsing(t_print *print, char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	if (str[i] == 'L')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (-1);
		if (str[i] == '-')
			nb++;
		i++;
	}
	if (nb != 1)
		return (-1);
	add_to_buffer(print, str);
	return (0);
}

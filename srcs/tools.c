/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 13:53:24 by ythomas           #+#    #+#             */
/*   Updated: 2019/08/27 13:53:26 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

long		ft_atol(char *src)
{
	long		i;
	long		sign;
	long		res;

	i = 0;
	sign = 1;
	res = 0;
	if (!src)
		return (0);
	while (((src[i] >= 8 && src[i] <= 13) || src[i] == ' ') && src[i])
		i++;
	if (src[i] == '-' || src[i] == '+')
		if (src[i++] == '-')
			sign = -1;
	while (src[i] >= '0' && src[i] <= '9')
	{
		if ((res * 10 + src[i] - 48) > 2147483647)
			return (-1);
		res = res * 10 + src[i++] - 48;
		if (res < 0)
			return (sign == -1 ? 1 : 0);
	}
	return (res * sign);
}

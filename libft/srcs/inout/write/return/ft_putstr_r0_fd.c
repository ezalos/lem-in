/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_r0_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:17:17 by ldevelle          #+#    #+#             */
/*   Updated: 2019/05/06 19:17:27 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putstr_r0_fd(char const *s, int fd)
{
	if (s == NULL)
		return (0);
	while (*s)
		write(fd, s++, 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <ythomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 16:07:18 by ythomas           #+#    #+#             */
/*   Updated: 2019/09/25 17:29:49 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

static const int	g_flags[256] =
{
	['h'] = F_H,
	['v'] = F_V
};

static const char	*g_usages[] =
{
	"usage: lem-in [-hv] -- [file]\n",
	"-h help display usage\n",
	"-v visual display visual\n",
	"if file is not specified, red from STDIN\n"
};

static void			ft_print_error(const char *const error)
{
	int				index;

	if (error)
		write(STDERR_FILENO, error, ft_strlen(error));
	index = 0;
	while (index < (int)(sizeof(g_usages) / sizeof(g_usages[0])))
	{
		write(STDERR_FILENO, g_usages[index], ft_strlen(g_usages[index]));
		++index;
	}
	exit(EXIT_FAILURE);
}

static int			ft_get_minus(char **av, char **const file,
		int *const flags)
{
	char			*ptr;

	ptr = *av;
	if (*++ptr == '-')
	{
		if (*++ptr)
			ft_print_error("error: bad paramter format\n");
		*file = *++av;
		if (*file && *++av)
			ft_print_error("error: only one file can be specified\n");
		return (1);
	}
	else
	{
		while (*ptr && g_flags[(int)*ptr])
			*flags |= g_flags[(int)*ptr++];
		if (*ptr)
			ft_print_error("error: unknow parameter\n");
	}
	return (0);
}

int					ft_get_flag(char **av, char **const file)
{
	int				flags;

	flags = 0;
	*file = NULL;
	while (*++av)
	{
		if (**av == '-')
		{
			if (ft_get_minus(av, file, &flags))
				break ;
		}
		else
		{
			*file = *av;
			if (*file && *++av)
				ft_print_error("error: only one file can be specified\n");
			break ;
		}
	}
	return (flags);
}

int					lem_in(t_god *god, char **av)
{
	char			*file;
	const int		flags = ft_get_flag(av, &file);

	if (flags & F_H)
		ft_print_error(NULL);
	if (flags & F_V)
		god->visu = flags;
	if (file && ((god->fd = open(file, O_RDONLY)) <= 0 || init(god) == -1))
		return (-1);
	else if (file == NULL && (init(god) == -1))
		return (-1);
	god->file = file;
	return (0);
}

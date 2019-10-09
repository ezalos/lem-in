/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <ythomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:41:02 by ythomas           #+#    #+#             */
/*   Updated: 2019/10/07 18:56:15 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			parse_links(t_god *god, t_print *print, char *line)
{
	char		*str;
	int			ret;

	if (check_link_parsing(print, line) != -1)
		ret = link_rooms(god->lem_in, line, &god->adjacent_matrix, god);
	else
		return (-1);
	while ((ret = ft_gnl(god->fd, &str)) > 0)
	{
		if (str[0] == '#')
			add_to_buffer(print, str);
		else if ((ret = check_link_parsing(print, str)) != -1)
			ret = link_rooms(god->lem_in, str, &god->adjacent_matrix, god);
		if (ret == -1)
			return (-1);
	}
	return (0);
}

int			parse_rooms(t_god *god, t_print *print, char *line)
{
	int ret;

	ret = 0;
	if (line[0] == '#' && (line[1] != '#' || (line[1] == '#'
	&& ft_strcmp(line + 2, "start") && ft_strcmp(line + 2, "end"))))
		add_to_buffer(print, line);
	else if (god->dbt == 0 && line[0] == '#' && line[1] == '#'
	&& !ft_strcmp(line + 2, "start") && (god->dbt = 1) == 1)
		ret = parse_extremity(god, print, START, line);
	else if (god->fin == 0 && line[0] == '#' && line[1] == '#'
	&& !ft_strcmp(line + 2, "end") && (god->fin = 1) == 1)
		ret = parse_extremity(god, print, END, line);
	else if ((ret = check_room_parsing(print, line)) != -1)
		add_rooms(god, 0, line);
	if (!ft_strncmp(line, "#Here is the number of lines required: ", 38))
		god->expected_solution = ft_atoi(line + 38);
	if (ret == -1)
		return (-1);
	return (0);
}

int			parse_extremity(t_god *god, t_print *print, int place, char *line)
{
	char	*str;
	int		ret;

	add_to_buffer(print, line);
	while ((ret = ft_gnl(god->fd, &str)) > 0 && str[0] == '#'
	&& ft_strcmp(str + 1, "#start") && ft_strcmp(str + 1, "#end"))
	{
		add_to_buffer(print, str);
		ft_memdel((void **)&str);
	}
	if (ret > 0)
	{
		if (check_room_parsing(print, str) != -1)
			add_rooms(god, place, str);
		else
			return (-1);
	}
	else
		return (-1);
	ft_memdel((void **)&str);
	return (0);
}

int			parse_ants(t_god *god, t_print *print)
{
	int		i;
	char	*line;
	int		tmp;

	i = -1;
	god->expected_solution = ERROR_EX_SOLUTION;
	while ((tmp = ft_gnl(god->fd, &line)) > 0 && line[0] == '#')
		add_to_buffer(print, line);
	if (tmp > 0 && ft_isdigit(line[0]))
	{
		while (line[++i] != '\0')
			if (line[i] < '0' || line[i] > '9')
				return (-1);
	}
	else
		return (-1);
	if ((tmp = ft_atol(line)) == -1)
		return (-1);
	god->ants = tmp;
	add_to_buffer(print, line);
	ft_memdel((void **)&line);
	god->dbt = 0;
	god->fin = 0;
	return (1);
}

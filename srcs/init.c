/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:48 by root              #+#    #+#             */
/*   Updated: 2019/06/14 00:09:39 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			file_steps(int fd, char **line)
{
	static int				step;
	int						r_v;
	int						i;

	time_exe(__func__);
	i = -1;
	if ((r_v = get_next_line(fd, line)) > 0)
	{
		if ((*line)[0] == '#' || (*line)[0] == 'L')// && (*line)[1] == '#')
			return (INIT_SPEC);
		else if (!step)
		{
			while ((*line)[++i])
				if (!ft_isdigit((*line)[i]))
					return (ERROR);
			return (step = INIT_QANT);
		}
		else if (step && ft_char_srch('-', (*line)))
			return ((step = INIT_LINK));
		else if (step + 1 == INIT_ROOM)
			return (INIT_ROOM);
		else
			return (ERROR);
	}
	return (r_v);
}

t_god		*init(int fd)
{
	t_god		*god;
	char		*line;
	int			r_v;
	int			place;
	int			ants_nb;
	int			ste;

	time_exe(__func__);
	god = ft_memalloc(sizeof(t_god));
	place = 0;
	line = NULL;
	ste = 0;
	while ((r_v = file_steps(fd, &line)) > 0)
	{
		ste++;
		time_exe(__func__);
		if (r_v == INIT_SPEC)
		{
			if (line[0] == 'L')
				(void)place;
			else if (!ft_strcmp(line + 2, "start"))
				place = START;
			else if (!ft_strcmp(line + 2, "end"))
				place = END;
		}
		else if (r_v == INIT_QANT)
			ants_nb = ft_atoi(line);
		else if (r_v == INIT_ROOM)
			add_rooms(god, place, ants_nb, line);
		else if (r_v == INIT_LINK)
			link_rooms(god->lem_in, line, &god->adjacent_matrix, god);
		else
			return (PTR_ERROR);
		ft_strdel(&line);
		if (r_v != INIT_SPEC)
			place = 0;
	}
	close(fd);
	god->end = ft_tab_reach_end(god->lem_in, 0)->content;
	// print_matrix(god->lem_in);
	time_exe(__func__);
	order_my_little_connexions(god);
	time_exe(__func__);
	get_rooms_in_tab(god);
	time_exe(__func__);
	*ft_remember_god() = god;
	return (god);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:48 by root              #+#    #+#             */
/*   Updated: 2019/06/24 19:53:32 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

void		init_used_tab(t_god *god)
{
	int i;

	i = 0;
	while (god->rooms[i])
	{
		god->rooms[i]->used = ft_memalloc(sizeof(int *) * god->rooms[i]->nb_of_connexions);
		god->rooms[i]->tmp_used = ft_memalloc(sizeof(int *) * god->rooms[i]->nb_of_connexions);
		god->surcharged_link = ft_memalloc(sizeof(t_ints) * god->size * 2);
		i++;
	}
}

int			file_steps(int fd, char **line, intmax_t total)
{
	static int				step;
	static intmax_t			where;
	int						r_v;
	int						i;

	i = -1;
	if ((r_v = ft_gnl(fd, line)) > 0)
	{
		ft_progress(__func__, where += r_v + 1, total);
		if ((*line)[0] == '#' || (*line)[0] == 'L')
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
	intmax_t	ste;
	intmax_t	total;
	int			i;

	god = ft_memalloc(sizeof(t_god));
	place = 0;
	line = NULL;
	ste = 0;
	total = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	while ((r_v = file_steps(fd, &line, total)) > 0)
	{
		ste++;
		if (r_v == INIT_SPEC)
		{
			if (line[0] == 'L')
				(void)place;
			else if (!ft_strcmp(line + 2, "start"))
				place = START;
			else if (!ft_strcmp(line + 2, "end"))
				place = END;
			else if (!ft_strncmp(line, "#Here is the number of lines required:", 38))
			{
				i = 0;
				while (!ft_isdigit(line[i]))
					i++;
				god->expected_solution = ft_atoi(line + i);
			}
		}
		else if (r_v == INIT_QANT)
			ants_nb = ft_atoi(line);
		else if (r_v == INIT_ROOM)
			add_rooms(god, place, ants_nb, line);
		else if (r_v == INIT_LINK)
			link_rooms(god->lem_in, line, &god->adjacent_matrix, god);
		else
			return (PTR_ERROR);
		// ft_strdel(&line);
		if (r_v != INIT_SPEC)
			place = 0;
	}
	// ft_progress(__func__, 4, 4);
	close(fd);
	god->end = ft_tab_reach_end(god->lem_in, 0)->content;
	god->extremities[1] = ft_tab_reach_end(god->lem_in, 0)->content;
	//print_matrix(god->lem_in);
	order_my_little_connexions(god);
	get_rooms_in_tab(god);
	*ft_remember_god() = god;
	init_used_tab(god);
	return (god);
}

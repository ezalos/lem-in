/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:48 by root              #+#    #+#             */
/*   Updated: 2019/05/18 14:08:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int			file_steps(int fd, char **line)
{
	static int		step;
	int						r_v;
	int						i;

	i = -1;
	if ((r_v = get_next_line(fd, line)) > 0)
	{
		if ((*line)[0] == '#' && (*line)[1] == '#')
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

int		add_rooms(t_tab **lem_in, int place, int ants_nb, char *line)
{
	t_tab		*new;
	t_lemin	*room;
	char		**split;

		if (!(split = ft_strsplit(line, ' ')))
			return (ERROR);
		ft_printf("%s\n", "SPLIT");
		if (!(room = ft_memalloc(sizeof(t_lemin))))
			return (ERROR);
		if (!(room->name = ft_strdup(split[0])))
			return (ERROR);
		ft_printf("name:%s\n", room->name);
		room->place = place;
		ft_printf("place:%d\n", room->place);
		room->y_coord = ft_atoi(split[1]);
		room->x_coord = ft_atoi(split[2]);
		ft_printf("y_coord:%d\n", room->y_coord);
		ft_printf("x_coord:%d\n", room->x_coord);
		ft_printf("%s\n", "ROOM Created");
		ft_strdel_multi(4, &split[0], &split[1], &split[2], &split);//need to be protected against more than 3 str
		if (!(new = ft_tabnew_ptr(&room, sizeof(void*))))
			return (ERROR);
		ft_printf("%s\n", "NEW");
		if (place < 0 || !(*lem_in))
		{
			room->ants = ants_nb;
			ft_tabadd_start(lem_in, new, 0);
		}
		else if (place > 0)
			ft_tabadd_end(*lem_in, new, 0);
		else
			ft_tabadd(lem_in, new, 0, 1);
		place = 0;
		return (VALID);
}

t_tab		*init(int fd)
{
	t_tab		*lem_in;
	char		*line;
	int			r_v;
	int			place;
	int			ants_nb;

	lem_in = NULL;
	while ((r_v = file_steps(fd, &line)) > 0)
	{
		ft_printf("%d\t%s\n", r_v, line);
		place = 0;
		if (r_v == INIT_SPEC)
		{
			if (!ft_strcmp(line + 2, "start"))
				place = -1;
			else if (!ft_strcmp(line + 2, "end"))
				place = 1;
		}
		else if (r_v == INIT_QANT)
			ants_nb = ft_atoi(line);
		else if (r_v == INIT_ROOM)
			add_rooms(&lem_in, place, ants_nb, line);
		else if (r_v == INIT_LINK)
			break ;
		else
			return (PTR_ERROR);
		ft_strdel(&line);
	}
	ft_printf("%d\t%s\n", r_v, line);
	ft_printf("%s\n", "END");
	close(fd);
	return (lem_in);
}

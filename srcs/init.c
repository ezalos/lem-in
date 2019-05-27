/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:48 by root              #+#    #+#             */
/*   Updated: 2019/05/27 16:16:49 by root             ###   ########.fr       */
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

int		add_rooms(t_god *god, int place, int ants_nb, char *line)
{
	t_tab		**lem_in;
	t_tab		*new;
	t_lemin	*room;
	char		**split;
	int			len;

		lem_in = &god->lem_in;
		if (!(split = ft_strsplit(line, ' ')))
			return (ERROR);
		if (!(room = ft_memalloc(sizeof(t_lemin))))
			return (ERROR);
		if (!(room->name = ft_strdup(split[0])))
			return (ERROR);
		room->place = place;
		room->y_coord = ft_atoi(split[1]);
		room->x_coord = ft_atoi(split[2]);
		ft_strdel_multi(4, &split[0], &split[1], &split[2], &split);//need to be protected against more than 3 str
		if (!(new = ft_tabnew_ptr(room, sizeof(void*))))
			return (ERROR);
		if (place < 0 || !(*lem_in))
		{
			god->start = room;
			room->ants = ants_nb;
			ft_tabadd_start(lem_in, new, 0);
		}
		else if (place > 0)
			ft_tabadd_end(*lem_in, new, 0);
		else
		{
			len = ft_tab_lendir(*lem_in, 0);
			if (((t_lemin*)ft_tab_dirth(*lem_in, 0, len - 1)->content)->place == 1)
			{
				ft_tabadd(lem_in, new, 0, len - 1);
			}
			else
			{
				god->end = room;
				ft_tabadd(lem_in, new, 0, len);
			}
		}
		return (VALID);
}

int			find_room_name(t_tab *lem_in, char *line, size_t dir)
{
	int		i;
	t_tab	*tmp;

	tmp = lem_in;
	i = 0;
	while (tmp)
	{
		if (!ft_strcmp(((t_lemin*)tmp->content)->name, line))
			return (i);
		i++;
		tmp = tmp->dir[dir];
	}
	return (-1);
}


void		***first_call(t_tab *lem_in, t_god *god)
{
	void		***adjacent_matrix;
	int			i;
	int			len;

	len = ft_tab_lendir(lem_in, 0);
	god->size = len;
	adjacent_matrix = ft_memalloc((len + 1) * sizeof(void**));
	i = -1;
	while (++i < len)
	{
		adjacent_matrix[i] = ft_memalloc(len * sizeof(void*));
		((t_lemin*)ft_tab_dirth(lem_in, 0, i)->content)->connexions = adjacent_matrix[i];
	}
	return (adjacent_matrix);
}

int			link_rooms(t_tab *lem_in, char *line, void ****adjacent_matrix, t_god *god)
{
	char		**split;
	int			first;
	int			second;

	if (!*adjacent_matrix)
		*adjacent_matrix = first_call(lem_in, god);
	if (!(split = ft_strsplit(line, '-')))
		return (ERROR);
	first = find_room_name(lem_in, split[0], 0);
	second = find_room_name(lem_in, split[1], 0);
	(*adjacent_matrix)[first][second] = ft_tab_dirth(lem_in, 0, second)->content;
	(*adjacent_matrix)[second][first] = ft_tab_dirth(lem_in, 0, first)->content;
	first = -1;
	while (split[++first])
		ft_memdel((void**)&split[first]);
	ft_memdel((void**)&split);
	return (SUCCESS);
}

int	order_my_little_connexions(t_god *god)
{
	int i;
	int j;
	t_tab *now;
	t_lemin *here;

	i = 0;
	now = god->lem_in;
	while (now)
	{
		here = now->content;
		i = -1;
		while (++i < god->size)
			if (!here->connexions[i])
			{
				j = -1;
				while (++j + i < god->size)
					if (here->connexions[i + j])
						ft_swap(&here->connexions[i], &here->connexions[i + j], sizeof(void*));
			}
		i = 0;
		while (here->connexions[i])
			i++;
		here->nb_of_connexions = i;
		now = now->dir[0];
	}
	return (0);
}

void		get_rooms_in_tab(t_god *god)
{
	t_tab		*now;
	int 		i;

	now = god->lem_in;
	god->rooms = ft_memalloc(sizeof(t_lemin**) * (god->size + 1));
	i = -1;
	while (++i < god->size)
	{
		// god->rooms = ft_memalloc(sizeof(t_lemin*));
		god->rooms[i] = now->content;
		god->rooms[i]->id = i;
		now = now->dir[0];
	}
}

t_god		*init(int fd)
{
	t_god		*god;
	char		*line;
	int			r_v;
	int			place;
	int			ants_nb;

	god = ft_memalloc(sizeof(t_god));
	place = 0;
	while ((r_v = file_steps(fd, &line)) > 0)
	{
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
	order_my_little_connexions(god);
	get_rooms_in_tab(god);
	return (god);
}

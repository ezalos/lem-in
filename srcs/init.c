/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:48 by root              #+#    #+#             */
/*   Updated: 2019/05/19 15:40:40 by root             ###   ########.fr       */
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
	int			len;

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
		if (!(new = ft_tabnew_ptr(room, sizeof(void*))))
			return (ERROR);
		ft_printf("%s\n", "NEW");
		if (place < 0 || !(*lem_in))
		{
			room->ants = ants_nb;
			// ft_tabadd_here(*lem_in, new, 1);
			ft_tabadd_start(lem_in, new, 0);
		}
		else if (place > 0)
			// ft_tabadd_here(*lem_in, new, 3);
			ft_tabadd_end(*lem_in, new, 0);
		else
		{
			len = ft_tab_lendir(*lem_in, 0);
			if (((t_lemin*)ft_tab_dirth(*lem_in, 0, len - 1)->content)->place == 1)
				ft_tabadd(lem_in, new, 0, len - 1);
			else
				ft_tabadd(lem_in, new, 0, len);
		}
		place = 0;
		return (VALID);
}

int			find_room_name(t_tab *lem_in, char *line, size_t dir)
{
	int		i;
	t_tab	*tmp;

	ft_printf("%s-%p\n", __func__, lem_in);
	tmp = lem_in;
	i = 0;
	while (tmp)
	{
		ft_printf("%s-%s\n",((t_lemin*)tmp->content)->name, line);
		if (!ft_strcmp(((t_lemin*)tmp->content)->name, line))
			return (i);
		i++;
		tmp = tmp->dir[dir];
	}
	return (-1);
}


void		***first_call(t_tab *lem_in)
{
	void		***adjacent_matrix;
	// t_tab		*tmp;
	int			i;
	int			len;

	ft_printf("%s\n", __func__);
	// tmp = ft_tab_cutone(lem_in->dir[3]);
	// ft_printf("%s\n", __func__);
	// ft_tabadd_end(lem_in, tmp, 0);
	// ft_printf("%s\n", __func__);
	// tmp = ft_tab_cutone(lem_in->dir[1]);
	// ft_tabadd_start(&lem_in, tmp, 0);
	len = ft_tab_lendir(lem_in, 0);
	adjacent_matrix = ft_memalloc(len * sizeof(void**));
	i = -1;
	while (++i < len)
	{
		ft_printf("%d/%d\n", i, len);
		adjacent_matrix[i] = ft_memalloc(len * sizeof(void*));
		((t_lemin*)ft_tab_dirth(lem_in, 0, i)->content)->connexions = adjacent_matrix[i];
	}
	return (adjacent_matrix);
}

int			link_rooms(t_tab *lem_in, char *line, void ****adjacent_matrix)
{
	char		**split;
	int			first;
	int			second;

	ft_printf("%s\n", __func__);
	if (!*adjacent_matrix)
		*adjacent_matrix = first_call(lem_in);
		ft_printf("%s", __func__);
	if (!(split = ft_strsplit(line, '-')))
		return (ERROR);
	first = find_room_name(lem_in, split[0], 0);
	second = find_room_name(lem_in, split[1], 0);
	ft_printf("%~{?}%s\t1:%d\t2:%d\n%~{}", __func__, first, second);
	(*adjacent_matrix)[first][second] = ft_tab_dirth(lem_in, 0, second)->content;
	(*adjacent_matrix)[second][first] = ft_tab_dirth(lem_in, 0, first)->content;
	first = -1;
	while (split[++first])
		ft_memdel((void**)&split[first]);
	ft_memdel((void**)&split);
	return (SUCCESS);
}

t_tab		*init(int fd)
{
	t_tab		*lem_in;
	char		*line;
	int			r_v;
	int			place;
	int			ants_nb;
	void		***adjacent_matrix;

	lem_in = NULL;
	adjacent_matrix = NULL;
	place = 0;
	while ((r_v = file_steps(fd, &line)) > 0)
	{
		ft_printf("%~{?}%d\t%s\n%~{}", r_v, line);
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
			link_rooms(lem_in, line, &adjacent_matrix);
		else
			return (PTR_ERROR);
		ft_strdel(&line);
		if (r_v != INIT_SPEC)
			place = 0;
	}
	ft_printf("%d\t%s\n", r_v, line);
	ft_printf("%s\n", "END");
	close(fd);
	return (lem_in);
}

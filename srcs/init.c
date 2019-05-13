/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 12:30:48 by root              #+#    #+#             */
/*   Updated: 2019/05/13 13:48:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

t_tab		*init(int fd)
{
	t_tab		*lem_in;
	t_tab		*new;
	t_lemin	*room;
	char		*line;
	char		**split;
	int			r_v;
	int			place;
	int			ants_nb;

	lem_in = NULL;
	if (get_next_line(fd, &line) <= 0)
		return (NULL);
	ants_nb = ft_atoi(line);
	while ((r_v = get_next_line(fd, &line)) > 0)
	{
		ft_printf("%~{255;150;150}%s:%p%~{}\n", __func__, lem_in);
		if (line[0] == '#' && line[1] == '#')
		{
			if (!ft_strcmp(line + 2, "start"))
				place = -1;
			else if (!ft_strcmp(line + 2, "end"))
				place = 1;
		}
		else if(ft_char_srch('-', line))
		{
			break ;
		}
		else
		{
			split = ft_strsplit(line, ' ');
			ft_printf("%s\n", "SPLIT");
			room = ft_memalloc(sizeof(t_lemin));
			room->name = ft_strdup(split[0]);
			ft_printf("name:%s\n", room->name);
			room->place = place;
			ft_printf("place:%d\n", room->place);
			room->y_coord = ft_atoi(split[1]);
			room->x_coord = ft_atoi(split[2]);
			ft_printf("y_coord:%d\n", room->y_coord);
			ft_printf("x_coord:%d\n", room->x_coord);
			ft_printf("%s\n", "ROOM Created");
			ft_strdel_multi(4, &split[0], &split[1], &split[2], &split);//need to be protected against more than 3 str
			new = ft_tabnew_ptr(&room, sizeof(void*));
			ft_printf("%s\n", "NEW");
			if (place < 0 || !lem_in)
			{
				room->ants = ants_nb;
				ft_tabadd_start(&lem_in, new, 0);
			}
			else if (place > 0)
				ft_tabadd_end(lem_in, new, 0);
			else
				ft_tabadd(&lem_in, new, 0, 1);
			place = 0;
		}
		ft_strdel(&line);
	}
	ft_printf("%s\n", "END");
	close(fd);
	return (lem_in);
}

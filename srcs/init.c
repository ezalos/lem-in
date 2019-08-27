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

void 		print_whole_buffer(t_print *print)
{
	t_print *tmp;

	tmp = print;
	while (tmp != NULL)
	{
		write(1, tmp->buff, tmp->index);
		tmp = tmp->next;
	}
}

int 		is_it_link_part(char *str)
{
	int i;

	i = 0;
	if (str[i] == '#' || str[i] == 'L')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

t_print 	*init_print(void)
{
	t_print *print;

	print = ft_memalloc(sizeof(t_print));
	print->next = NULL;
	print->index = 0;
	return (print);
}

void 		add_to_buffer(t_print *print, char *str)
{
	int i;
	t_print *tmp;

	tmp = print;
	while (print->next != NULL)
		print = print->next;
	if (ft_strlen(str) + print->index > P_BUFF - 5)
	{
		print->next = init_print();
		print = print->next;
	}
	i = 0;
	while (str[i] != '\0')
		print->buff[print->index++] = str[i++];
	print->buff[print->index++] = '\n';
	print = tmp;
}

int			parse_ants(t_god *god, int fd, t_print *print)
{
	int i;
	char *line;
	int tmp;

	i = 0;
	if (ft_gnl(fd, &line) > 0)
	{
		while (line[i] != '\0')
		{
			if (line[i] < '0' || line[i] > '9')
				return (-1);
			i++;
		}
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
int 		check_room_parsing_suit(char *str, int i, int step)
{
	if (str[i] == ' ' && str[i] == ' ')
		return (-1);
	if ((int)(str[i]) < 32 || (int)(str[i]) > 127)
		return (-1);
	if (str[i] == '-' && step == 0)
		return (-1);
	return (0);
}
int 		check_room_parsing(t_print *print, char *str)
{
	int i;
	int step;

	i = 0;
	step = 0;
	if (str[i] == 'L')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\0')
			step++;
		else if (check_room_parsing_suit(str, i, step) == -1)
			return (-1);
		if (step > 0 && (str[i] == '-' || str[i] == '+') && (str[i + 1] == '-' || str[i + 1] == '+'))
			return (-1);
		if (step > 0 && !(str[i] == '-' || str[i] == '+' || str[i] == ' ' || (str[i] >= '0' && str[i] <= '9')))
			return (-1);
		i++;
	}
	if (step != 2)
		return (-1);
	add_to_buffer(print, str);
	return (0);
}

int 		check_link_parsing(t_print *print, char *str)
{
	int i;
	int nb;

	i = 0;
	nb = 0;
	if (str[i] == 'L')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (-1);
		if (str[i] == '-')
			nb++;
		i++;
	}
	if (nb == 0)
		return (-1);
	add_to_buffer(print, str);
	return (0);
}

int 		parse_extremity(t_god *god, t_print *print, int fd, int place, char *line)
{
	char *str;
	int ret;

	add_to_buffer(print, line);
	while ((ret = ft_gnl(fd, &str)) > 0 && str[0] == '#' && ft_strcmp(str + 1, "#start") && ft_strcmp(str + 1, "#end"))
	{
		add_to_buffer(print, str);
		ft_memdel((void **)&str);
	}
	if (ret > 0)
	{
		if (check_room_parsing(print, str) != -1)
			add_rooms(god, place, god->ants, str);
		else
			return (-1);
	}
	else
		return (-1);
	ft_memdel((void **)&str);
	return (0);
}

int 		parse_rooms(t_god *god, int fd, t_print *print, char *line)
{
	int ret;

time_exe(__func__);
	ret = 0;
	if (line[0] == '#' && (line[1] != '#' || (line[1] == '#' && !ft_strcmp(line + 2, "start") && !ft_strcmp(line + 2, "end"))))
		add_to_buffer(print, line);
	else if (god->dbt == 0 && line[0] == '#' && line[1] == '#' && !ft_strcmp(line + 2, "start") && (god->dbt = 1) == 1)
		ret = parse_extremity(god, print, fd, START, line);
	else if (god->fin == 0 &&line[0] == '#' && line[1] == '#' && !ft_strcmp(line + 2, "end") && (god->fin = 1) == 1)
		ret = parse_extremity(god, print, fd, END, line);
	else if ((ret = check_room_parsing(print, line)) != -1)
		add_rooms(god, 0, god->ants, line);
	if (ret == -1)
		return (-1);
	return (0);
}

int 		parse_links(t_god *god, int fd, t_print *print, char *line)
{
	char *str;
	int ret;

	time_exe(__func__);

	if (check_link_parsing(print, line) != -1)
		ret = link_rooms(god->lem_in, line, &god->adjacent_matrix, god);
	else
		return (-1);
	while ((ret = ft_gnl(fd, &str)) > 0)
	{
		if (str[0] == '#' && str[1] != '#')
			add_to_buffer(print, str);
		else if ((ret = check_link_parsing(print, str)) != -1)
			ret = link_rooms(god->lem_in, str, &god->adjacent_matrix, god);
		if (ret == -1)
			return (-1);
		ft_memdel((void **)&str);
	}
	return (0);
}

int 		init_suit(t_god *god, t_print *print)
{
	god->end = ft_tab_reach_end(god->lem_in, 0)->content; // NE PAS TOUCHER
	god->extremities[1] = ft_tab_reach_end(god->lem_in, 0)->content; // NE PAS TOUCHER
	//print_matrix(god->lem_in);
	order_my_little_connexions(god);// NE PAS TOUCHER
	get_rooms_in_tab(god);// NE PAS TOUCHER
	how_many_entries_exits(god);
	if (!god->goulots)
		return (-1);
	*ft_remember_god() = god;// NE PAS TOUCHER
	init_used_tab(god);// NE PAS TOUCHER
	print_whole_buffer(print);
	write(1, "\n", 1); // JUSTE POUR CHECKER
	return (0);
}

int 		init(t_god *god, int fd)
{
	t_print *print;
	char *line;
	int ret;

	time_exe(__func__);
	print = init_print();
	if (parse_ants(god, fd, print) == -1)
		return (-1);
	while ((ret = ft_gnl(fd, &line)) > 0 && is_it_link_part(line) == 0)
	{
		if (parse_rooms(god, fd, print, line) == -1)
			return (-1);
		ft_memdel((void **)&line);
	}
	if (god->dbt != 1 || god->fin != 1)
		return (-1);
	if (ret <= 0)
		return (-1);
	if (parse_links(god, fd, print, line) == -1)
		return (-1);
	if (fd != 1)
		close(fd);
	time_exe(__func__);
	if (init_suit(god, print) == -1)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ythomas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 13:15:14 by ythomas           #+#    #+#             */
/*   Updated: 2019/08/16 13:15:42 by ythomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/head.h"

int				display_map(t_god *god, char **av)
{
	int fd;
	char buffer[10000];
	int len;

	(void)god;
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (-1);
	while ((len = read(fd, buffer, 10000)) > 0)
		write(1, buffer, len);
	close(fd);
	write(1, "\n", 1);
	return (0);
}

void 			fill_buffer(t_print *print, char *nb, char *name)
{
	int i;
	int j;

	print->buff[print->index] = 'L';
	(print->index)++;
	i = 0;
	while (nb[i] != '\0')
	{
		print->buff[print->index] = nb[i++];
		(print->index)++;
	}
	print->buff[print->index] = '-';
	(print->index)++;
	j = 0;
	while (name[j] != '\0')
	{
		print->buff[print->index] = name[j++];
		(print->index)++;
	}
	print->buff[print->index] = ' ';
	(print->index)++;

}
int				moove_one_turn(t_god *god, t_print *print)
{
	int i;
	int j;
	int tmp;

	i = 0;
	tmp = 0;
	while (i < god->nb_final_paths)
	{
		j = god->final_path[i][0];
		while (j > 1)
		{
			if (god->rooms[god->final_path[i][j]]->gen != -1)
			{
				fill_buffer(print, ft_itoa(god->rooms[god->final_path[i][j]]->gen), god->rooms[god->final_path[i][j + 1]]->name);
				//ft_printf("L%d-%s ", god->rooms[god->final_path[i][j]]->gen, god->rooms[god->final_path[i][j + 1]]->name);
				god->rooms[god->final_path[i][j + 1]]->gen = god->rooms[god->final_path[i][j]]->gen;
				god->rooms[god->final_path[i][j]]->gen = -1;
				tmp++;
			}
			j--;
		}
		i++;
	}
	return (tmp);
}

int 			push_ants(t_god *god, int *genome, int *waiting_ant, t_print *print)
{
	int i;
	int pushed;

	i = 0;
	pushed = 0;
	while (i < god->nb_final_paths)
	{
		if (waiting_ant[i] > 0)
		{
			fill_buffer(print, ft_itoa(*genome), god->rooms[god->final_path[i][2]]->name);
			//ft_printf("L%d-%s ", *genome, god->rooms[god->final_path[i][2]]->name);
			god->rooms[god->final_path[i][2]]->gen = *genome;
			(*genome)++;
			(waiting_ant[i])--;
			pushed++; 
		}
		i++;
	}
	return (pushed);
}

int 			*init_waiting_tab(t_god *god)
{
	int *tab;
	int i;
	int len;
	int mod;

	tab = ft_memalloc(sizeof(int *) * god->nb_final_paths);
	i = 0;
	while (i < god->nb_final_paths)
		len = len + god->final_path[i++][0];
	i = -1;
	while (++i < god->nb_final_paths)
		tab[i] = god->turn - god->final_path[i][0] + 2;
	if ((mod = ((god->ants + len) % god->nb_final_paths)) != 0)
	{
		i = -1;
		while (++i < mod)
			(tab[i])++;
	}
	return (tab);
}

void			print_buffer(t_print *print)
{
	int i;

	if (print->index != 0)
		(print->index)--;
	print->buff[print->index] = '\n';
		(print->index)++;
	write(1, print->buff, print->index);
	i = 0;
	while (i < print->index)
		print->buff[i++] = '\0';
	print->index = 0;
}

int				display_ants_turn(t_god *god)
{
	int genome = 1;
	int tmp;
	int t_ants;
	int *waiting_ant;
	t_print print;

	print.index = 0;
	waiting_ant = init_waiting_tab(god);
	tmp = 0;
	t_ants = god->ants;
	while (t_ants > 0 || tmp > 0)
	{
		tmp = moove_one_turn(god, &print);
		if (t_ants != 0)
			t_ants = t_ants - push_ants(god, &genome, waiting_ant, &print);
		print_buffer(&print);
	}
	return (0);
}

int 			display_result(t_god *god, char **av)
{
	display_map(god, av);
	(void)av;
	display_ants_turn(god);
	return (0);
}

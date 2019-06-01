/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:21:20 by ldevelle          #+#    #+#             */
/*   Updated: 2019/06/01 13:35:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H


# define FAILURE				0
# define SUCCESS				1

# define START					-1
# define END						1

# define ERROR					-1
# define VALID					0

# define PTR_ERROR			NULL

# define INIT_QANT			1
# define INIT_ROOM			2
# define INIT_LINK			3
# define INIT_SPEC			4

# define RIGHT					0
# define DOWN						1
# define LEFT						2
# define UP							3

# include "../../libft/includes/libft.h"

typedef struct		s_path
{
	int							*path;
}									t_path;

typedef struct		s_lemin
{
	int							id;
	char						*name;
	int							place;

	int							x_coord;
	int							y_coord;

	int							ants;

	void						**connexions;
	int							nb_of_connexions;

	int							from_start;
	int							from_end;
	int							from[2];
	int							gone;
}									t_lemin;

typedef struct		s_god
{
	t_tab						*lem_in;
	t_lemin					**rooms;
	void						***adjacent_matrix;

	t_path					*paths;
	int							nb_of_paths;

	t_lemin					*start;
	t_lemin					*end;

	int							size;

	int							name_len;

	int							entry_points;
	int							*entry_list;
	int							exit_points;
	int							*exit_list;
	int							goulots;
}									t_god;

/*
******************************************************************************
**																			**
**								----------									**
**								PROTOTYPES									**
**								----------									**
**																			**
******************************************************************************
*/

/*
**************
**   INIT	**
**************
*/
t_god			*init(int fd);
int				print_matrix(t_tab *lem_in);
int				lets_calcul(t_god *god);
int				refresh_a_star(t_god *god);
int				how_many_entries_exits(t_god *god);
int				close_a_path(t_lemin *here);
void			find_a_path(t_lemin *here, t_path *ptr);
t_god			**ft_remember_god(void);
int				alternate_piles(t_god *god, int id_start, int id_end, int start_to_end);
void 			clear_data(t_god *god);
void 			print_name_and_from_dist(t_god *god);
void 			print_paths(t_god *god);
void 			print_this_path(t_god *god, t_path *path);
void 		clear_gone(t_god *god);
void 		add_gone_from_paths(t_god *god);

int			is_there_a_path(t_god *god, int *kill_list, int point_a, int point_b);
#endif

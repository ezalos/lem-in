/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:21:20 by ldevelle          #+#    #+#             */
/*   Updated: 2019/06/18 23:08:25 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H


# define FAILURE				0
# define SUCCESS				1

# define START					-1
# define END					1

# define ERROR					-1
# define VALID					0

# define PTR_ERROR				NULL

# define INIT_QANT				1
# define INIT_ROOM				2
# define INIT_LINK				3
# define INIT_SPEC				4

# define RIGHT					0
# define DOWN					1
# define LEFT					2
# define UP						3

# include "../../libft/includes/libft.h"

typedef int* 					t_ints;

typedef struct					s_path
{
	t_ints						path;
}								t_path;

typedef struct					s_lemin
{
	int							id;
	char						*name;
	int							place;

	int							x_coord;
	int							y_coord;

	int							ants;

	void						**connexions;
	int							nb_of_connexions;

	int							from[2];
	int							gone;
}								t_lemin;

typedef struct					s_god
{
	t_tab						*lem_in;
	t_lemin						**rooms;
	void						***adjacent_matrix;

	t_path						*paths;
	int							nb_of_paths;

	t_lemin						*start;
	t_lemin						*end;
	t_lemin						*extremities[2];

	int							size;

	int							name_len;

	int							entry_points;
	int							*entry_list;
	int							*entry_t_list;

	int							exit_points;
	int							*exit_list;
	int							*exit_t_list;

	t_ints						extremities_list[2];

	int							goulots;
	int							side;
}								t_god;

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
**   INIT		**
**************
*/
t_god			*init(int fd);

int				add_rooms(t_god *god, int place, int ants_nb, char *line);

int				find_room_name(t_tab *lem_in, char *line, size_t dir);
void			***first_call(t_tab *lem_in, t_god *god);
int				link_rooms(t_tab *lem_in, char *line, void ****adjacent_matrix, t_god *god);

int				order_my_little_connexions(t_god *god);
void			get_rooms_in_tab(t_god *god);
t_god			**ft_remember_god(void);


/*
**************
**   DATA		**
**************
*/
t_god			**ft_remember_god(void);
void 			clear_data(t_god *god);
void 			clear_gone(t_god *god);
void 			add_gone_from_paths(t_god *god);
void 		full_clear(t_god *god);

/*
**************
**   PRINT	**
**************
*/
int				print_matrix(t_tab *lem_in);
void 			print_name_and_from_dist(t_god *god);
void 			print_paths(t_god *god);
void 			print_this_path(t_god *god, t_path *path);
void			print_room_infos(t_god *god);

/*
**************
** GOULOTS	**
**************
*/
int				how_many_entries_exits(t_god *god);

/*
**************
** 	PATH		**
**************
*/
int				close_a_path(t_lemin *here);
void			find_a_path(t_lemin *here, int id, t_path *ptr);
int				get_rid_of_dead_ends(t_god *god);


/*
**************
**   	A*		**
**************
*/
int				refresh_a_star(t_god *god);
int				alternate_piles(t_god *god, int id_start, int id_end, int start_to_end);

int				lets_calcul(t_god *god);
int				full_process(t_god *god, t_path *ptr);

int				complete_missing_paths(t_god *god, int missing_paths);
int				is_there_a_path(t_god *god, int *kill_list, int point_a, int point_b);
#endif

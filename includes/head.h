/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:21:20 by ldevelle          #+#    #+#             */
/*   Updated: 2019/06/24 17:13:12 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H


# define FAILURE				0
# define SUCCESS				1
# define F_V 					1
# define F_H 					2

# define START					-1
# define END					1

# define ERROR					-1
# define VALID					0

# define PTR_ERROR				NULL

# define INIT_QANT				1
# define INIT_ROOM				2
# define INIT_LINK				3
# define INIT_SPEC				4

# define HTABLE_SIZE			262144

# define RIGHT					0
# define DOWN					1
# define LEFT					2
# define UP						3

# define P_BUFF					5000

/********** VISUAL DEFINE ************/

#define H_SCREEN				1080.0
#define W_SCREEN				1920.0
#define MAX_PIX					2073600

/*************************************/


# include "../../libft/includes/libft.h"
# include <mlx.h>

typedef int* 					t_ints;

typedef struct					s_lemin
{
	int							id;
	char						*name;
	int							place;

	int							x_coord;
	int							y_coord;


	struct s_lemin				**connexions;
	int							nb_of_connexions;
	int 						weight;
	struct s_lemin				*last_room;
	int 						*used; //de la taille du nb_of_xonnexions, used[i] correspondra donc a si la conexion de connexion[i] est utilisé
	int 						*tmp_used;
	int 						blocked;

	int							from[2];
	int							gone;
	int 						gen;
	int 						surcharged;
}								t_lemin;

typedef struct					s_meta
{
	int							turns;
	t_ints						*set_of_path;
	int							*ants_sent;
}								t_meta;





typedef struct 					s_piles
{
	t_ints 						pile_a;
	t_ints 						pile_b;
	int 						finish;
	int 						deep;
	int 						actual_room;
	int 						ste;
	int 						r_v;
}								t_piles;






typedef struct 					s_hashelement
{
	void						*data;
	void						*key;
	size_t						key_length;
	struct s_hashelement		*next;
}								t_hashelement;

# define HASHTABLE_DEFAULT_SIZE 8200

typedef struct 					s_hashtable
{
	struct s_hashelement		**elements;
	size_t						elements_size;
	size_t						elements_count;
}								t_hashtable;

struct s_hashtable				*hashtable_init(void);
void							hashtable_append(t_hashtable *hashtable, void *data, void *key, size_t key_length);
void							*hashtable_value(t_hashtable *hashtable, void *key, size_t key_length);
void							hashtable_deinit(t_hashtable *hashtable);
void                     		print_hashtable(t_hashtable *hashtable);

typedef struct					s_god
{
	t_tab						*lem_in;
	t_lemin						**rooms;
	t_lemin						***adjacent_matrix;
	t_ints						surcharged_link;

	t_ints						*paths;
	t_ints 						*final_path;
	int 						*waiting_ant;
	int 						nb_final_paths;
	int							nb_of_paths;
	int							ants;
	long int 					turn;

	struct s_hashtable			*hashtable;

	t_lemin						*start;
	t_lemin						*end;
	t_lemin						*extremities[2];

	int							size;
	int							expected_solution;

	int 						dbt;
	int 						fin;

	int							name_len;

	t_ints						extremities_list[2];

	int 						trigger;
	int 						variation;
	int 						visu;

	int							goulots;
	int							side;
}								t_god;

typedef struct 					s_print
{
	int 						index;
	char 						buff[P_BUFF];
	struct s_print 				*next;
} 								t_print;





typedef struct 					s_room
{
	double 						x;
	double 						y;
	char 						*name;
	int 						nb_rooms;
}								t_room;

typedef struct 					s_visu
{
	int 						nb_paths;
	t_room 						***paths;
	int 						ants;
	int 						turn;
	int 						nb_h;
	double 						rate_x;
	double 						rate_y;
	double 						range;
}								t_visu;




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
int 			init(t_god *god, int fd);
int 			lem_in(t_god *god, char **av, int fd);

int				add_rooms(t_god *god, int place, int ants_nb, char *line);

int 			parse_links(t_god *god, int fd, t_print *print, char *line);
int 			parse_rooms(t_god *god, int fd, t_print *print, char *line);
int 			parse_extremity(t_god *god, t_print *print,
				int fd, int place, char *line);
int				parse_ants(t_god *god, int fd, t_print *print);
void 			print_whole_buffer(t_print *print);
int 			is_it_link_part(char *str);
int 			check_room_parsing_suit(char *str, int i, int step);
int 			check_room_parsing(t_print *print, char *str);
int 			check_link_parsing(t_print *print, char *str);


int				find_room_name(t_tab *lem_in, char *line, size_t dir);
int				link_rooms(t_tab *lem_in, char *line,
				t_lemin ****adjacent_matrix, t_god *god);
void			init_stack(int size, t_piles *stack, int id);

int				order_my_little_connexions(t_god *god);
void			get_rooms_in_tab(t_god *god);
t_god			**ft_remember_god(void);
t_lemin			***ft_lemin_htable(void);

int 			clean_help(int err);

/*
**************
**   DATA		**
**************
*/
t_god			**ft_remember_god(void);
void 			clear_data(t_god *god);
void 			clear_gone(t_god *god);
void 			add_gone_from_paths(t_god *god);
void 			full_clear(t_god *god);
void 			clear_links(t_god *god);
void 			clear_tmp_links(t_god *god);
void 			refresh_tmp_links(t_god *god);
void			clean_surcharged_tab(t_ints tab);

/*
**************
**   PRINT	**
**************
*/
int				print_matrix(t_tab *lem_in);
void 			print_name_and_from_dist(t_god *god);
void 			print_paths(t_god *god);
void 			print_final_paths(t_god *god);
void 			print_this_path(t_god *god, t_ints path);
void			print_room_infos(t_god *god);
void			print_used_link_state(t_god *god);
void			print_tmp_used_link_state(t_god *god);
void			print_surcharged_tab(t_god *god);

/*
**************
**   DISPLAY	**
**************
*/

int 			display_result(t_god *god);
void 			add_to_buffer(t_print *print, char *str);
t_print 		*init_print(void);
void 			print_whole_buffer(t_print *print);
void 			add_to_buffer(t_print *print, char *str);
void			print_buffer_with_refresh(t_print *print);
void 			fill_line_buffer(t_print *print, char *nb, char *name);

int 			ft_setup_visu(t_god *god);
int 			launch_visual(t_visu *visu);
void			init_new_coord(t_visu *visu);

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
void			find_a_path(t_lemin *here, int id, t_ints *path);
int				get_rid_of_dead_ends(t_god *god);
int				ft_evaluate_set_of_path(t_god *god, int nb_paths);
/*
*******************
** 	TOOLS		**
*******************
*/
long			ft_atol(char *src);
int 			which_link_is_surcharged(t_god *god, t_ints path);
void			creat_surcharged_link(t_god *god, int room1, int room2);
int 			is_it_connected(t_god *god, int room1, int room2);
int  			find_pv_link(t_god *god, t_lemin *tmp, t_piles *stack);
int 			find_link(t_lemin *tmp);

int 			reset_this_set(t_god *god, int nb_finish);
void			init_stack(int size, t_piles *stack, int id);
void			gone_is_one(t_god *god, t_piles *stack, t_ints new_p, int id);
void			gone_is_zero(t_god *god, t_piles *stack, t_ints new_p, int id);
void 			add_gone(t_god *god, int nb_paths);

void 			save_actual_set(t_god *god, int nb_paths, int nb_of_turn);
int 			get_faster_path(t_god *god);
void			add_path_to_set(t_god *god, int path);
int 			get_len_path(t_god *god);
/*
**************
**   	A*		**
**************
*/

int 			breadth_first_search(t_god *god, int *stat);

int				refresh_a_star(t_god *god);
int				alternate_piles(t_god *god, int id_start, int id_end, int start_to_end);

int				lets_calcul(t_god *god);
int				full_process(t_god *god);

t_ints			*get_second_set_of_paths(t_god *god);
int				is_there_a_path(t_god *god, int *kill_list, int point_a, int point_b);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <afeuerst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:26:56 by afeuerst          #+#    #+#             */
/*   Updated: 2019/09/23 21:07:57 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H

/********** VISUAL DEFINE ************/

# define H_SCREEN				1080.0
# define W_SCREEN				1920.0

# define BALL_RADIUS			20.0
# define BALL_MIN_SPACE			BALL_RADIUS * 2.0
# define CONNECT_RADIUS			BALL_RADIUS / 3.0
# define CONNECT_BALL_SPACE_DIFF  0 /*BALL_RADIUS * 2 + BALL_RADIUS / 5.0*/
# define CONNECT_DIFF CON

# define FOURMI_RADIUS BALL_RADIUS / 4.0

# define MAX_PIX					2073600

# define DURATION 1.25

# define DEBUG_H_MIN H_SCREEN
# define DEBUG_W_MIN W_SCREEN

typedef struct 					s_room
{
	float						x;
	float						y;
	float						z;
	char 						*name;
	int 						nb_rooms;
}								t_room;

typedef struct 					s_visu
{
	int 						nb_paths;
	int 						*flux;
	t_room 						***paths;
	int 						ants;
	int 						turn;
	int 						nb_h;
	double						screen_h;
	double						screen_w;
	double						rate_x;
	double						rate_y;
	double						rayon;
	double						centre;
	double						tmpx;
	double						tmpz;
}								t_visu;

void							launch_visual(t_visu *const visu);

# define TEXT_FONT_SIZE 19.0

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:21:20 by ldevelle          #+#    #+#             */
/*   Updated: 2019/05/13 13:30:14 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H


# define MODE					2

# include "../../libft/includes/libft.h"

typedef struct		s_lemin
{
	char						*name;
	int							place;
	int							x_coord;
	int							y_coord;
	int							ants;
}									t_lemin;

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
t_tab		*init(int fd);



#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2018/09/12 16:06:56 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	ROTATE_Z function:
**	Rotation around Oz axis
*/

t_vec	rotate_z(t_vec u, double angle)
{
	t_vec	v;

	angle = angle * M_PI / 180;
	v.x = u.x * cos(angle) - u.y * sin(angle);
	v.y = u.x * sin(angle) + u.y * cos(angle);
	v.z = u.z;
	return (v);
}

/*
**	ROTATE_X function:
**	Rotation around Ox axis
*/

t_vec	rotate_x(t_vec u, double angle)
{
	t_vec	v;

	angle = angle * M_PI / 180;
	v.y = u.y * cos(angle) - u.z * sin(angle);
	v.z = u.y * sin(angle) + u.z * cos(angle);
	v.x = u.x;
	return (v);
}

/*
**	ROTATE_Y function:
**	Rotation around Oy axis
*/

t_vec	rotate_y(t_vec u, double angle)
{
	t_vec	v;

	angle = angle * M_PI / 180;
	v.z = u.z * cos(angle) - u.x * sin(angle);
	v.x = u.z * sin(angle) + u.x * cos(angle);
	v.y = u.y;
	return (v);
}

/*
**	ROTATE function:
**	Rotation in space
*/

t_vec	rotate(t_vec u, double anglex, double angley, double anglez)
{
	t_vec	w;
	t_vec	v;
	t_vec	x;

	v = rotate_x(u, anglex);
	w = rotate_y(v, angley);
	x = rotate_z(w, anglez);
	return (x);
}

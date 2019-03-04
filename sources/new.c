/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 15:19:32 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/04 17:34:18 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	NEWCOLOR function:
**	Create a new color with 3 parameters
*/

t_color	newcolor(double r, double g, double b)
{
	t_color	c;

	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		ft_printerror("Wrong value for color");
	c.red = r;
	c.green = g;
	c.blue = b;
	return (c);
}

/*
**	NEWSH function:
**	Create a new sphere with 3 parameters
*/

t_sph	newsph(t_vec center, double radius, int mat)
{
	t_sph	sph;

	if (radius <= 0 || mat < 0)
		ft_printerror("Wrong value for sphere");
	sph.center = center;
	sph.radius = radius;
	sph.mat = mat;
	return (sph);
}

/*
**	NEWPLANE function:
**	Create a new plane with 3 parameters
*/

t_plane	newplane(t_vec dir, double d, int mat)
{
	t_plane	p;

	if (mat < 0)
		ft_printerror("Wrong value for plane");
	p.dir = dir;
	p.d = d;
	p.mat = mat;
	return (p);
}

/*
**	NEWCYL function:
**	Create a new cylinder with 4 parameters
*/

t_cyl	newcyl(t_vec dir, t_vec center, double radius, int mat)
{
	t_cyl	cy;

	if (radius <= 0 || mat < 0)
		ft_printerror("Wrong value for cylinder");
	cy.dir = dir;
	cy.center = center;
	cy.radius = radius;
	cy.mat = mat;
	return (cy);
}

/*
**	NEWCONE function:
**	Create a new cone with 4 parameters
*/

t_cone	newcone(t_vec dir, t_vec center, double angle, int mat)
{
	t_cone	co;

	if (angle <= 0 || angle >= 70 || mat < 0)
		ft_printerror("Wrong value for cone");
	co.dir = dir;
	co.center = center;
	co.angle = angle;
	co.mat = mat;
	return (co);
}

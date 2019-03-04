/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_items.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2018/09/12 15:46:17 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	HITSPHERE function:
**	Returns 1 if the sphere is hit and change the parameter t, else 0
*/

int		hitsphere(t_ray r, t_sph s, double *t)
{
	double	a;
	double	b;
	double	c;
	t_vec	dist;

	a = magnitude2(r.dir);
	dist = sub(r.start, s.center);
	b = 2 * dotproduct(r.dir, dist);
	c = magnitude2(dist) - s.radius * s.radius;
	if (b * b - 4 * a * c < 0)
		return (0);
	else
		return (calc_discr(a, b, c, t));
}

/*
**	HITCONE function:
**	Returns 1 if the cone is hit and change the parameter t, else 0
*/

int		hitcone(t_ray r, t_cone co, double *t)
{
	t_vec	mod;
	t_vec	h1;
	t_vec	h2;
	t_vec	dist;

	dist = sub(r.start, co.center);
	h1 = calc_h1(r, co.dir);
	h2 = calc_h2(dist, co.dir);
	mod.x = magnitude2(scale(cos(co.angle * M_PI / 180), h1))
		- pow(sin(co.angle * M_PI / 180) * dotproduct(r.dir, co.dir), 2);
	mod.y = 2 * pow(cos(co.angle * M_PI / 180), 2) * dotproduct(h1, h2)
		- 2 * pow(sin(co.angle * M_PI / 180), 2) * dotproduct(r.dir, co.dir)
		* dotproduct(dist, co.dir);
	mod.z = magnitude2(scale(cos(co.angle * M_PI / 180), h2))
		- pow(sin(co.angle * M_PI / 180) * dotproduct(dist, co.dir), 2);
	if (mod.y * mod.y - 4 * mod.x * mod.z < 0)
		return (0);
	else
		return (calc_discr(mod.x, mod.y, mod.z, t));
}

/*
**	HITCYLINDER function:
**	Returns 1 if the cylinder is hit and change the parameter t, else 0
*/

int		hitcylinder(t_ray r, t_cyl cy, double *t)
{
	t_vec	mod;
	t_vec	h1;
	t_vec	h2;
	t_vec	dist;

	dist = sub(r.start, cy.center);
	h1 = calc_h1(r, cy.dir);
	h2 = calc_h2(dist, cy.dir);
	mod.x = magnitude2(h1);
	mod.y = 2 * dotproduct(h1, h2);
	mod.z = magnitude2(h2) - pow(cy.radius, 2);
	if (mod.y * mod.y - 4 * mod.x * mod.z < 0)
		return (0);
	else
		return (calc_discr(mod.x, mod.y, mod.z, t));
}

/*
**	CALC_DISCR function:
**	Calculate the discriminant of an equation ax^2 + bx + c = 0
*/

int		calc_discr(double a, double b, double c, double *t)
{
	double	sqrtdiscr;
	double	t0;
	double	t1;

	sqrtdiscr = sqrtf(b * b - 4 * a * c);
	t0 = (-b + sqrtdiscr) / (2 * a);
	t1 = (-b - sqrtdiscr) / (2 * a);
	if (t0 > t1)
		t0 = t1;
	if (t0 > 0.001f && (*t == -1 || t0 < *t))
	{
		*t = t0;
		return (1);
	}
	else
		return (0);
}

/*
**	HITPLANE function:
**	Returns 1 if the plane is hit and change the parameter t, else 0
*/

int		hitplane(t_ray r, t_plane p, double *t)
{
	double	t0;

	if (dotproduct(p.dir, r.dir) != 0)
	{
		t0 = -(dotproduct(p.dir, r.start) + p.d)
			/ dotproduct(p.dir, r.dir);
		if (t0 > 0.001f && (*t == -1 || t0 < *t))
		{
			*t = t0;
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}

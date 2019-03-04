/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_normal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:34:11 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/05 09:57:46 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	FIND_NORMAL_VEC_IF_NOT_PLANE function:
**	Finds the normal vector in the point newstart according to the hit item
**	(only if the item != plane)
*/

t_vec		find_normal_vec_if_not_plane(int itemtype, int *curr,
			t_vec newstart, t_env *e)
{
	t_vec	n;

	n = newvec(0, 0, 0);
	if (itemtype == 0)
		n = sub(newstart, e->sph[*curr].center);
	else if (itemtype == 2)
		n = find_cylinder_normal(newstart, e->cylinder[*curr]);
	else if (itemtype == 3)
		n = find_cone_normal(newstart, e->cone[*curr]);
	return (n);
}

/*
**	FIND_CYLINDER_NORMAL function:
**	Calculates the normal vector to a cylinder
*/

t_vec		find_cylinder_normal(t_vec newstart, t_cyl cyl)
{
	t_vec	m;
	t_vec	n;

	m = find_h(cyl.dir, cyl.center, newstart);
	n = sub(newstart, m);
	return (n);
}

/*
**	FIND_CONE_NORMAL function:
**	Calculate the normal vector to plane
*/

t_vec		find_cone_normal(t_vec newstart, t_cone cone)
{
	t_vec	n;
	t_vec	h;
	t_vec	tmp;
	t_vec	tmp2;
	t_vec	sc1;

	h = find_h(cone.dir, cone.center, newstart);
	tmp = sub(cone.center, h);
	tmp2 = sub(newstart, h);
	tmp2 = normalize(tmp2);
	sc1 = scale(cos(cone.angle * M_PI / 180), tmp2);
	if (dotproduct(tmp, cone.dir) > 0)
		tmp2 = scale(sin(cone.angle * M_PI / 180), cone.dir);
	else
		tmp2 = scale(-sin(cone.angle * M_PI / 180), cone.dir);
	n = add(sc1, tmp2);
	return (n);
}

/*
**	FIND_H function:
**	Intermediate function to find normal vector to a cylinder or cone
*/

t_vec		find_h(t_vec cd, t_vec cc, t_vec n)
{
	t_vec	u;
	t_vec	v;
	t_vec	w;
	double	z;

	u = sub(n, cc);
	z = dotproduct(cd, u) / magnitude2(cd);
	v = scale(z, cd);
	w = add(cc, v);
	return (w);
}

/*
**	FIND_MATERIAL function:
**	Finds material of the hit item thanks to the index stored in the structure
*/

t_mat		find_material(int itemtype, int *curr, t_env *e)
{
	t_mat	m;

	m.diffuse = newcolor(0, 0, 0);
	m.reflection = 0;
	m.specvalue = 0;
	m.specpower = 0;
	if (itemtype == 0 && e->sph[*curr].mat < e->nbs[MAT])
		m = e->mat[e->sph[*curr].mat];
	else if (itemtype == 1 && e->plane[*curr].mat < e->nbs[MAT])
		m = e->mat[e->plane[*curr].mat];
	else if (itemtype == 2 && e->cylinder[*curr].mat < e->nbs[MAT])
		m = e->mat[e->cylinder[*curr].mat];
	else if (itemtype == 3 && e->cone[*curr].mat < e->nbs[MAT])
		m = e->mat[e->cone[*curr].mat];
	return (m);
}

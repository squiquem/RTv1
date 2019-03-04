/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:34:11 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/05 11:27:59 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	COLOR_CALC function:
**	The loop is here for reflections
*/

t_color		color_calc(int x, int y, t_env *e)
{
	int		lvl;
	t_work	w;

	w.c = newcolor(0, 0, 0);
	lvl = 0;
	w.coef = 1.0;
	w.r.start = e->cam->pos;
	w.r.dir = set_ray_dir(x, y, e);
	while ((w.coef > 0.0f) && (lvl < 15))
	{
		if (!ray_calc(e, &w))
			break ;
		lvl++;
	}
	return (w.c);
}

/*
**	RAY_CALC function:
**	Find the hit vector
**	Find the normal of the new vector at the point of intersection
**	Find the material to determine the colour
**	Find the value of the light at this point
**	Iterate over the reflection
**	Calculate the reflected ray start and direction
*/

int			ray_calc(t_env *e, t_work *w)
{
	int		curr;
	int		itemtype;
	t_mat	currmat;
	t_vec	newstart;

	curr = -1;
	itemtype = find_closest_item(w->r, e, &newstart, &curr);
	if (itemtype == -1)
		return (0);
	if (itemtype == 1 && dotproduct(w->r.dir, e->plane[curr].dir) > 0)
		w->n = opposite(e->plane[curr].dir);
	else if (itemtype == 1 && dotproduct(w->r.dir, e->plane[curr].dir) < 0)
		w->n = e->plane[curr].dir;
	else
		w->n = find_normal_vec_if_not_plane(itemtype, &curr, newstart, e);
	if (magnitude2(w->n) == 0)
		return (0);
	w->n = normalize(w->n);
	currmat = find_material(itemtype, &curr, e);
	get_light_value(w, newstart, currmat, e);
	w->coef *= currmat.reflection;
	recalculate_ray(&w->r, w->n, newstart);
	return (1);
}

/*
**	GET_LIGHT_VALUE function:
**	Calculation of the light value from diffusion and lighting
**	(Lambert diffusion & Blinn-Phuong reflection)
*/

void		get_light_value(t_work *w, t_vec newstart, t_mat currmat,
			t_env *e)
{
	int		j;
	t_light	currlight;
	t_vec	dist;
	t_ray	lightray;
	double	f;

	j = -1;
	while (++j < e->nbs[LIGHT])
	{
		currlight = e->light[j];
		dist = sub(currlight.pos, newstart);
		if (dotproduct(w->n, dist) <= 0.0f || sqrtf(magnitude2(dist)) <= 0.0f)
			continue;
		lightray.start = newstart;
		lightray.dir = normalize(dist);
		if (!in_shadow(lightray, e, sqrtf(magnitude2(dist))))
		{
			f = lambert(lightray, w->n, w->coef);
			color_lambert(&w->c, f, currlight, currmat);
			f = blinnphuong(lightray, &w->r, w->n, currmat);
			color_blinnphuong(&w->c, f, currlight, w->coef);
		}
	}
}

/*
**	SET_RAY_DIR function:
**	Calculation of the ray parameters from the x and y (screen parameters)
*/

t_vec		set_ray_dir(int x, int y, t_env *e)
{
	t_vec	i;
	t_vec	j;
	t_vec	k;
	t_vec	l;

	k = e->cam->dir;
	if (k.x == 0.0f && k.y == 1.0f && k.z == 0.0f)
		l = newvec(0.0, 0.0, 1.0);
	else
		l = newvec(0.0, 1.0, 0.0);
	i = crossproduct(k, l);
	j = crossproduct(i, k);
	l.x = (IMG_W - (double)x * 2.0) / IMG_W * i.x
			+ (IMG_H - (double)y * 2.0) / IMG_W * j.x + FOV * k.x;
	l.y = (IMG_W - (double)x * 2.0) / IMG_W * i.y
			+ (IMG_H - (double)y * 2.0) / IMG_W * j.y + FOV * k.y;
	l.z = (IMG_W - (double)x * 2.0) / IMG_W * i.z
			+ (IMG_H - (double)y * 2.0) / IMG_W * j.z + FOV * k.z;
	l = normalize(l);
	return (l);
}

/*
**	RECALCULATE_RAY function:
**	Calculate the new ray after hit
*/

void		recalculate_ray(t_ray *r, t_vec n, t_vec newstart)
{
	double	f;
	t_vec	tmp;

	r->start = newstart;
	f = dotproduct(r->dir, n);
	tmp = scale(2.0f * f, n);
	r->dir = sub(r->dir, tmp);
}

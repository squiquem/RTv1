/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_closest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:34:11 by squiquem          #+#    #+#             */
/*   Updated: 2018/09/12 16:23:32 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	FIND_CLOSEST_SPH function:
**	Finds the closest sphere hit by the ray
*/

int			find_closest_sph(t_ray r, t_env *e, double *t)
{
	int	i;
	int	curr;

	i = -1;
	curr = -1;
	while (++i < e->nbs[3])
	{
		if (hitsphere(r, e->sph[i], t))
			curr = i;
	}
	return (curr);
}

/*
**	FIND_CLOSEST_PLANE function:
**	Finds the closest plane hit by the ray
*/

int			find_closest_plane(t_ray r, t_env *e, double *t)
{
	int	i;
	int	curr;

	i = -1;
	curr = -1;
	while (++i < e->nbs[4])
	{
		if (hitplane(r, e->plane[i], t))
			curr = i;
	}
	return (curr);
}

/*
**	FIND_CLOSEST_CYL function:
**	Finds the closest cylinder hit by the ray
*/

int			find_closest_cyl(t_ray r, t_env *e, double *t)
{
	int	i;
	int	curr;

	i = -1;
	curr = -1;
	while (++i < e->nbs[5])
	{
		if (hitcylinder(r, e->cylinder[i], t))
			curr = i;
	}
	return (curr);
}

/*
**	FIND_CLOSEST_CONE function:
**	Finds the closest cone hit by the ray
*/

int			find_closest_cone(t_ray r, t_env *e, double *t)
{
	int	i;
	int	curr;

	i = -1;
	curr = -1;
	while (++i < e->nbs[6])
	{
		if (hitcone(r, e->cone[i], t))
			curr = i;
	}
	return (curr);
}

/*
**	FIND_CLOSEST_ITEM function:
**	Finds the closest item hit by the ray
*/

int			find_closest_item(t_ray r, t_env *e, t_vec *newstart, int *curr)
{
	double	t;
	int		type[4];
	int		i;

	t = -1;
	type[0] = find_closest_sph(r, e, &t);
	type[1] = find_closest_plane(r, e, &t);
	type[2] = find_closest_cyl(r, e, &t);
	type[3] = find_closest_cone(r, e, &t);
	*newstart = add(scale(t, r.dir), r.start);
	i = 3;
	while (type[i] == -1 && i)
		--i;
	while (i && --i >= 0)
		type[i] = -1;
	i = -1;
	while (++i < 4)
	{
		if (type[i] > -1)
		{
			*curr = type[i];
			return (i);
		}
	}
	return (-1);
}

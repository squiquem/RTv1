/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2018/09/12 16:18:09 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	MAGNITUDE2 function:
**	Calculates the squared magnitude of a vector
*/

double	magnitude2(t_vec v)
{
	double	x;

	x = dotproduct(v, v);
	return (x);
}

/*
**	NORMALIZE function:
**	Normalizes a vector if its magnitude != 0
*/

t_vec	normalize(t_vec v)
{
	t_vec	uv;
	double	tmp;
	double	tmp2;

	tmp2 = magnitude2(v);
	if (!tmp2)
		ft_printerror("Vector null");
	tmp = 1.0f / sqrtf(tmp2);
	uv = scale(tmp, v);
	return (uv);
}

/*
**	OPPOSITE function:
**	Returns the opposite vector
*/

t_vec	opposite(t_vec u)
{
	t_vec	w;

	w.x = -u.x;
	w.y = -u.y;
	w.z = -u.z;
	return (w);
}

/*
**	ADD function:
**	Returns the sum of 2 vectors
*/

t_vec	add(t_vec u, t_vec v)
{
	t_vec	w;

	w.x = u.x + v.x;
	w.y = u.y + v.y;
	w.z = u.z + v.z;
	return (w);
}

/*
**	SUB function:
**	Returns the difference of 2 vectors
*/

t_vec	sub(t_vec u, t_vec v)
{
	t_vec	w;

	w.x = u.x - v.x;
	w.y = u.y - v.y;
	w.z = u.z - v.z;
	return (w);
}

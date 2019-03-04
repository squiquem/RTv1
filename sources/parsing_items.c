/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_items.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/04 17:38:18 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	PARSING_LIGHT function:
**	Parses the light parameters in the structure
*/

void	parsing_light(char **s, t_env *e, int *k)
{
	int	i;

	if (ft_strcmp(s[0], "LIGHT"))
		return ;
	i = 0;
	if (table_len(s) != 9 && table_len(s) != 13 && table_len(s) != 17)
		ft_printerror("Invalid file");
	e->light[*k].pos = newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]),
		ft_atoi(s[4]));
	e->light[*k].intensity = newcolor(ft_atoi(s[6] + 1), ft_atoi(s[7]),
			ft_atoi(s[8]));
	while (table_len(s) - i > 9)
	{
		if (*(s[9 + i] + 1) == 'T')
			e->light[*k].pos = add(e->light[*k].pos,
				newvec(ft_atoi(s[10 + i] + 1), ft_atoi(s[11 + i]),
					ft_atoi(s[12 + i])));
		i += 4;
	}
	(*k)++;
}

/*
**	PARSING_SPHERE function:
**	Parses the sphere parameters in the structure
*/

void	parsing_sphere(char **s, t_env *e, int *k)
{
	int		i;

	if (ft_strcmp(s[0], "SPHERE"))
		return ;
	i = 0;
	if (table_len(s) != 9 && table_len(s) != 13 && table_len(s) != 17)
		ft_printerror("Invalid file");
	e->sph[*k] = newsph(newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]), ft_atoi(s[4])),
			ft_atoi(s[6]), ft_atoi(s[8]));
	while (table_len(s) - i > 9)
	{
		if (*(s[9 + i] + 1) == 'T')
			e->sph[*k].center = add(e->sph[*k].center,
				newvec(ft_atoi(s[10 + i] + 1), ft_atoi(s[11 + i]),
				ft_atoi(s[12 + i])));
		i += 4;
	}
	(*k)++;
}

/*
**	PARSING_PLANE function:
**	Parses the plane parameters in the structure
*/

void	parsing_plane(char **s, t_env *e, int *k)
{
	int		i;
	t_plane	p;

	if (ft_strcmp(s[0], "PLANE"))
		return ;
	p = e->plane[*k];
	i = 0;
	if (table_len(s) != 9 && table_len(s) != 13 && table_len(s) != 17)
		ft_printerror("Invalid file");
	p = newplane(newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]), ft_atoi(s[4])),
		ft_atoi(s[6]), ft_atoi(s[8]));
	p.dir = normalize(p.dir);
	while (table_len(s) - i > 9)
	{
		if (*(s[9 + i] + 1) == 'R')
			p.dir = rotate(p.dir, ft_atoi(s[10 + i] + 1), ft_atoi(s[11 + i]),
				ft_atoi(s[12 + i]));
		if (*(s[9 + i] + 1) == 'T')
			p.d = p.d - ft_atoi(s[10 + i] + 1) * p.dir.x - ft_atoi(s[11 + i])
				* p.dir.y - ft_atoi(s[12 + i]) * p.dir.z;
		i += 4;
	}
	e->plane[*k] = p;
	(*k)++;
}

/*
**	PARSING_CYLINDER function:
**	Parses the cylinder parameters in the structure
*/

void	parsing_cylinder(char **s, t_env *e, int *k)
{
	int		i;
	t_cyl	cy;

	if (ft_strcmp(s[0], "CYLINDER"))
		return ;
	cy = e->cylinder[*k];
	i = 0;
	if (table_len(s) != 13 && table_len(s) != 17 && table_len(s) != 21)
		ft_printerror("Invalid file");
	cy = newcyl(newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]), ft_atoi(s[4])),
		newvec(ft_atoi(s[6] + 1), ft_atoi(s[7]), ft_atoi(s[8])),
		ft_atoi(s[10]), ft_atoi(s[12]));
	cy.dir = normalize(cy.dir);
	while (table_len(s) - i > 13)
	{
		if (*(s[13 + i] + 1) == 'R')
			cy.dir = rotate(cy.dir, ft_atoi(s[14 + i] + 1), ft_atoi(s[15 + i]),
				ft_atoi(s[16 + i]));
		if (*(s[13 + i] + 1) == 'T')
			cy.center = add(cy.center, newvec(ft_atoi(s[14 + i] + 1),
				ft_atoi(s[15 + i]), ft_atoi(s[16 + i])));
		i += 4;
	}
	e->cylinder[*k] = cy;
	(*k)++;
}

/*
**	PARSING_CONE function:
**	Parses the cone parameters in the structure
*/

void	parsing_cone(char **s, t_env *e, int *k)
{
	int		i;
	t_cone	co;

	if (ft_strcmp(s[0], "CONE"))
		return ;
	co = e->cone[*k];
	i = 0;
	if (table_len(s) != 13 && table_len(s) != 17 && table_len(s) != 21)
		ft_printerror("Invalid file");
	co = newcone(newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]), ft_atoi(s[4])),
		newvec(ft_atoi(s[6] + 1), ft_atoi(s[7]), ft_atoi(s[8])),
		ft_atoi(s[10]), ft_atoi(s[12]));
	co.dir = normalize(co.dir);
	while (table_len(s) - i > 13)
	{
		if (*(s[13 + i] + 1) == 'R')
			co.dir = rotate(co.dir, ft_atoi(s[14 + i] + 1), ft_atoi(s[15 + i]),
				ft_atoi(s[16 + i]));
		if (*(s[13 + i] + 1) == 'T')
			co.center = add(co.center, newvec(ft_atoi(s[14 + i] + 1),
				ft_atoi(s[15 + i]), ft_atoi(s[16 + i])));
		i += 4;
	}
	e->cone[*k] = co;
	(*k)++;
}

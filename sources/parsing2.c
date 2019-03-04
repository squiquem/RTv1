/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 15:02:34 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/05 09:58:50 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	PARSING_CAM function:
**	Parses the cam parameters in the cam structure
*/

void	parsing_cam(char **s, t_env *e)
{
	int		i;

	i = 0;
	if (ft_strcmp(s[0], "CAM"))
		return ;
	if (table_len(s) != 9 && table_len(s) != 17 && table_len(s) != 13)
		ft_printerror("Invalid file");
	e->cam->pos = newvec(ft_atoi(s[2] + 1), ft_atoi(s[3]), ft_atoi(s[4]));
	e->cam->dir = newvec(ft_atoi(s[6] + 1), ft_atoi(s[7]), ft_atoi(s[8]));
	e->cam->dir = normalize(e->cam->dir);
	while (table_len(s) - i > 9)
	{
		if (*(s[9 + i] + 1) == 'R')
			e->cam->dir = rotate(e->cam->dir, ft_atoi(s[10 + i] + 1),
				ft_atoi(s[11 + i]), ft_atoi(s[12 + i]));
		if (*(s[9 + i] + 1) == 'T')
			e->cam->pos = add(e->cam->pos, newvec(ft_atoi(s[10 + i] + 1),
				ft_atoi(s[11 + i]), ft_atoi(s[12 + i])));
		i += 4;
	}
}

/*
**	PARSING_MAT function:
**	Parses the material parameters in the structure
*/

void	parsing_mat(char **s, t_env *e, int *k)
{
	if (ft_strcmp(s[0], "MAT"))
		return ;
	if (table_len(s) != 11)
		ft_printerror("Invalid file");
	if (ft_atoi(s[6]) < 0 || ft_atoi(s[8]) < 0 || ft_atoi(s[10]) < 0)
		ft_printerror("Wrong value");
	e->mat[*k].diffuse = newcolor(ft_atoi(s[2] + 1), ft_atoi(s[3]),
			ft_atoi(s[4]));
	e->mat[*k].reflection = ft_atoi(s[6]) / 100;
	e->mat[*k].specvalue = ft_atoi(s[8]) / 100;
	e->mat[*k].specpower = ft_atoi(s[10]);
	(*k)++;
}

/*
**	FILL_STRUCT function:
**	Fulfills the environment structure with the items structures
*/

void	fill_struct(t_env *e, char *line, int index[6])
{
	char	**s;

	s = ft_strsplit((char const*)line, ' ');
	parsing_cam(s, e);
	parsing_mat(s, e, &index[0]);
	parsing_light(s, e, &index[1]);
	parsing_sphere(s, e, &index[2]);
	parsing_plane(s, e, &index[3]);
	parsing_cylinder(s, e, &index[4]);
	parsing_cone(s, e, &index[5]);
	ft_freesplit(s);
}

/*
**	TABLE_LEN function:
**	Calculates the length of a char * table
*/

int		table_len(char **s)
{
	int	l;

	l = 0;
	while (s[l] != 0)
		++l;
	return (l);
}

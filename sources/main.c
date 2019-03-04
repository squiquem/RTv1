/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 17:07:15 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/02 09:19:47 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "keyboard.h"

/*
**	QUIT function:
**	Quits when clicking on the red cross
*/

int			quit(void)
{
	exit(1);
	return (0);
}

/*
**	ESCAPE function:
**	Quits when typing ESC key
*/

static int	escape(int keycode, t_env *e)
{
	if (keycode == KEY_ESC)
		exit(1);
	(void)e;
	return (0);
}

/*
**	FILENAME_CONTROL function:
**	Controls if the filename ends with ".rt"
*/

void		filename_control(char *av)
{
	if (ft_strcmp(av + ft_strlen(av) - 3, ".rt"))
		ft_printerror("Please use valid file");
}

/*
**	MAIN function:
*/

int			main(int ac, char **av)
{
	t_env	*e;

	if (ac != 2)
		ft_printerror("Only 1 argument");
	filename_control(av[1]);
	if (!(e = (t_env*)malloc(sizeof(t_env))))
		ft_printerror("Error malloc");
	if (read_file1(av[1], e) == -1)
		ft_printerror("Please enter a valid file");
	if (!(e->mlx = mlx_init()))
		ft_printerror("Error mlx init");
	read_file2(av[1], e);
	e->win = mlx_new_window(e->mlx, WIN_W, WIN_H, "rtv1");
	mlx_expose_hook(e->win, reload, e);
	mlx_key_hook(e->win, escape, e);
	mlx_hook(e->win, 17, 1L << 17, quit, e);
	mlx_loop(e->mlx);
	return (1);
}

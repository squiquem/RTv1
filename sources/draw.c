/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 00:34:11 by squiquem          #+#    #+#             */
/*   Updated: 2018/09/12 15:31:33 by squiquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <string.h>
#include <errno.h>

/*
**	DRAW_POINT function:
**	Puts the color in the unsigned char * image of the environment
*/

static void	draw_point(t_env *e, int x, int y, t_color c)
{
	e->pixel_img[y * e->s_line + x * e->bpp / 8] = (unsigned char)
		ft_min(c.blue * 255.0f, 255.0f);
	e->pixel_img[y * e->s_line + x * e->bpp / 8 + 1] = (unsigned char)
		ft_min(c.green * 255.0f, 255.0f);
	e->pixel_img[y * e->s_line + x * e->bpp / 8 + 2] = (unsigned char)
		ft_min(c.red * 255.0f, 255.0f);
}

/*
**	DRAW function:
**	For Multithreading
*/

static void	*draw(void *e)
{
	t_sgmt			thread;
	int				x;
	int				y;
	pthread_t		s;
	t_color			c;

	thread.start = 0;
	s = pthread_self();
	while (s != ((t_env*)e)->thr[thread.start])
		thread.start++;
	thread.end = (thread.start + 1) * IMG_W / NB_THR;
	thread.start = thread.start * IMG_W / NB_THR;
	y = IMG_H;
	while (--y > -1)
	{
		x = thread.start - 1;
		while (++x < thread.end)
		{
			c = color_calc(x, y, (t_env*)e);
			draw_point((t_env*)e, x, y, c);
		}
	}
	pthread_exit(NULL);
}

/*
**	RELOAD function:
**	Sets image in the window
*/

int			reload(t_env *e)
{
	int	i;
	int	rc;

	if (!(e->img = mlx_new_image(e->mlx, IMG_W, IMG_H)) ||
		!(e->pixel_img = (unsigned char*)mlx_get_data_addr(e->img, &e->bpp,
			&e->s_line, &e->ed)))
		ft_printerror("Error mlx");
	i = -1;
	while (++i < NB_THR)
		if ((rc = pthread_create(&e->thr[i], NULL, draw, e)))
			ft_putendl_fd(strerror(errno), 2);
	i = -1;
	while (++i < NB_THR)
		if (pthread_join(e->thr[i], NULL))
			ft_putendl_fd(strerror(errno), 2);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_destroy_image(e->mlx, e->img);
	return (0);
}

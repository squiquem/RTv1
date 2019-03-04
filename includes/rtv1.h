/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: squiquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:09:49 by squiquem          #+#    #+#             */
/*   Updated: 2018/10/04 19:12:51 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>

# define WIN_H		600
# define WIN_W		800
# define IMG_H		600
# define IMG_W		800
# define NB_THR		8
# define FOV		2.0

# define CAM		0
# define MAT		1
# define LIGHT		2
# define SPH		3
# define PLANE		4
# define CYL		5
# define CONE		6

typedef struct		s_sgmt
{
	int				start;
	int				end;
}					t_sgmt;

typedef struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

typedef struct		s_color
{
	double			red;
	double			green;
	double			blue;
}					t_color;

typedef struct		s_ray
{
	t_vec			start;
	t_vec			dir;
}					t_ray;

typedef struct		s_light
{
	t_vec			pos;
	t_color			intensity;
}					t_light;

typedef struct		s_mat
{
	t_color			diffuse;
	double			reflection;
	double			specvalue;
	double			specpower;
}					t_mat;

typedef struct		s_cam
{
	t_vec			pos;
	t_vec			dir;
}					t_cam;

typedef struct		s_sph
{
	t_vec			center;
	double			radius;
	int				mat;
}					t_sph;

typedef struct		s_plane
{
	t_vec			dir;
	double			d;
	int				mat;
}					t_plane;

typedef struct		s_cone
{
	t_vec			dir;
	t_vec			center;
	double			angle;
	int				mat;
}					t_cone;

typedef struct		s_cyl
{
	t_vec			dir;
	t_vec			center;
	double			radius;
	int				mat;
}					t_cyl;

typedef struct		s_work
{
	t_ray			r;
	t_color			c;
	t_vec			n;
	double			coef;
}					t_work;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned char	*pixel_img;
	int				bpp;
	int				s_line;
	int				ed;
	int				nbs[7];
	t_cam			*cam;
	t_sph			*sph;
	t_plane			*plane;
	t_cone			*cone;
	t_cyl			*cylinder;
	t_mat			*mat;
	t_light			*light;
	pthread_t		thr[NB_THR];
}					t_env;

int					reload(t_env *e);

void				filename_control(char *av);
int					quit(void);

double				magnitude2(t_vec v);
t_vec				normalize(t_vec v);
t_vec				opposite(t_vec v);
t_vec				add(t_vec u, t_vec v);
t_vec				sub(t_vec u, t_vec v);

t_vec				crossproduct(t_vec u, t_vec v);
double				dotproduct(t_vec u, t_vec v);
t_vec				scale(double k, t_vec u);
t_vec				newvec(double x, double y, double z);

int					hitplane(t_ray r, t_plane p, double *t);
int					hitsphere(t_ray r, t_sph s, double *t);
int					hitcylinder(t_ray r, t_cyl c, double *t);
int					hitcone(t_ray r, t_cone c, double *t);
int					calc_discr(double a, double b, double c, double *t);

t_vec				calc_h1(t_ray r, t_vec dir);
t_vec				calc_h2(t_vec dist, t_vec dir);

t_color				color_calc(int x, int y, t_env *e);
t_vec				set_ray_dir(int x, int y, t_env *e);
int					ray_calc(t_env *e, t_work *w);
void				get_light_value(t_work *w, t_vec newstart, t_mat currmat,
					t_env *e);
void				recalculate_ray(t_ray *r, t_vec n, t_vec newstart);

void				color_lambert(t_color *c, double l, t_light currl,
					t_mat currm);
double				lambert(t_ray lightray, t_vec n, double coef);
void				color_blinnphuong(t_color *c, double b, t_light currl,
					double coef);
double				blinnphuong(t_ray lightray, t_ray *r, t_vec n,
					t_mat currm);
int					in_shadow(t_ray lightray, t_env *e, double t);

int					find_closest_sph(t_ray r, t_env *e, double *t);
int					find_closest_plane(t_ray r, t_env *e, double *t);
int					find_closest_cyl(t_ray r, t_env *e, double *t);
int					find_closest_cone(t_ray r, t_env *e, double *t);
int					find_closest_item(t_ray r, t_env *e, t_vec *newstart,
					int *curr);

t_vec				find_normal_vec_if_not_plane(int itemtype, int *curr,
					t_vec newstart, t_env *e);
t_vec				find_cone_normal(t_vec newstart, t_cone cone);
t_vec				find_cylinder_normal(t_vec newstart, t_cyl cyl);
t_vec				find_h(t_vec cd, t_vec cc, t_vec n);
t_mat				find_material(int itemtype, int *curr, t_env *e);

int					read_file1(char *av, t_env *e);
int					read_file2(char *av, t_env *e);
void				count_param_control(char *line, int nbs[6]);
void				count_param(int nbs[6], char **s, int l);
void				build_struct(t_env *e, int nbs[6]);

void				parsing_cam(char **s, t_env *e);
void				parsing_mat(char **s, t_env *e, int *k);
void				fill_struct(t_env *e, char *line, int index[6]);
int					table_len(char **s);

void				parsing_cone(char **s, t_env *e, int *k);
void				parsing_cylinder(char **s, t_env *e, int *k);
void				parsing_plane(char **s, t_env *e, int *k);
void				parsing_sphere(char **s, t_env *e, int *k);
void				parsing_light(char **s, t_env *e, int *k);

t_vec				rotate_x(t_vec u, double angle);
t_vec				rotate_y(t_vec u, double angle);
t_vec				rotate_z(t_vec u, double angle);
t_vec				rotate(t_vec u, double anglex, double angley,
					double anglez);

t_color				newcolor(double r, double g, double b);
t_sph				newsph(t_vec center, double radius, int mat);
t_plane				newplane(t_vec dir, double d, int mat);
t_cyl				newcyl(t_vec dir, t_vec center, double radius, int mat);
t_cone				newcone(t_vec dir, t_vec center, double angle, int mat);

#endif

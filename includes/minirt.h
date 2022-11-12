/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonny <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 12:59:08 by sdonny            #+#    #+#             */
/*   Updated: 2022/06/11 15:20:12 by sdonny           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <float.h>

# include "libft.h"
# include "mlx.h"
# include "get_next_line_bonus.h"

# define WIDTH 1280
# define HEIGHT 720

// FIGURES TYPES
# define SPHERE_TYPE 1
# define PLANE_TYPE 2
# define CYLINDER_TYPE 3
# define CONE_TYPE 4

# define T_MIN 0
# define T_MAX DBL_MAX

# define EPSILON 1e-5

// ERROR MESSAGES
# define SYNTAX "Wrong scene syntax"
# define NO_TOKEN "Was found impossible token or second camera/ambiant light!"
# define MALLOC "Malloc rip"
# define BYE "bye, have a great time\n"
# define RT "Need *.rt file only"
# define FILE_ERR "Can not open file"
# define COORD_RANGE "Too large coordinates, bro"
# define ZERO_NORM "Normal can not be zero, bro"
# define ERROR "ERROR!"
# define INCORRECT_RGB "Incorrect rgb!"
# define NUM_COORDS "Wrong number of coordinates!"
# define NOT_DIGIT "Wrong numeric argument!"
# define BAD_RADIUS "Too large radius, bro"
# define WRONG_DOT "There is no integer part of number!"
# define AMB_RANGE "Ambient ratio is not in range!"
# define NORMAL_RANGE "Normal's range is [-1; 1]!"
# define NO_CUUM "No camera is defined!"
# define NO_AMB "No ambian light is defined!"
# define FOV_GOVNO "Wrong fild of view, bro"

// ERROR CODES
# define SYNTAX_ERROR 228
# define MALLOC_ERROR 11
# define GAY 88
# define CUM 14
# define SEX 13
# define ERROR_CODE 15

# define ONLY_FREE -228

# define START_RECURSION -2
# define NORMAL 1
# define NOT_NORMAL 0

typedef struct s_env
{
	char				*key;
	char				*val;
	struct s_env		*next;
}t_env;

typedef struct s_rgb
{
	double				r;
	double				g;
	double				b;
}t_rgb;

typedef struct s_dot
{
	double				x;
	double				y;
	double				z;
}t_dot;

typedef struct s_vplane
{
	float				width;
	float				height;
	float				ratio;
	float				x_pixel;
	float				y_pixel;
	unsigned char		fov;
}t_vplane;

typedef struct s_ray
{
	t_dot		origin;
	t_dot		direction;
}				t_ray;

typedef struct s_inter_point
{
	double		t;
	double		t1;
	double		t2;
	t_dot		coord;
	t_dot		normal;
	int			hit;
	double		pixel_intensity;
	int			color;
	int			id;
	int			type;
	t_ray		ray;
}				t_inter_point;

typedef struct s_ambient
{
	t_rgb				rgb;
	double				ratio;
	char				quantity;
}t_ambient;

typedef struct s_camera
{
	t_dot				view_point;
	t_dot				n_vector;
	unsigned char		fov;
	char				quantity;
}t_camera;

typedef struct s_light
{
	t_dot				l_point;
	double				brightness;
	t_rgb				rgb;
}t_light;

typedef struct s_figure
{
	char				type;
	t_dot				coordinates;
	t_rgb				rgb;
	t_dot				orientation_vec;
	double				radius;
	double				height;
	char				refl;
	double				dist1;
	double				dist2;
	t_dot				normal;
	struct s_figure		*next;
}t_figure;

typedef struct s_rt
{
	double		x;
	double		ray_coord[2];
	t_vplane	vplane;
	t_dot		ray;
	t_rgb		color;
}t_rt;

typedef struct s_intersec
{
	t_figure			*closest_f;
	double				closest_t;
	double				t_min;
}t_intersec;

typedef struct s_elem
{
	t_dot	cross;
}t_elem;

typedef struct s_parametrs
{
	t_dot				point;
	t_dot				normal;
	t_dot				multed;
	t_dot				view;
	t_intersec			cls;
	t_rgb				color_without_reflection;
	t_rgb				tmp_light;
}t_parametrs;

typedef struct s_ri_cyl
{
	t_dot			cross;
	t_dot			c_to_o;
	t_dot			cross2;
	t_dot			sub;
	double			a;
	double			b;
	double			c;
	double			delta;
}t_ri_cyl;

typedef struct s_inf
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
	t_ambient			amb;
	t_camera			cam;
	t_light				light;
	t_figure			*figures;
	t_dot				*ray;
}t_inf;

t_dot		reflect_ray(t_dot *v1, t_dot *v2);
double		dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b);
double		cyl_dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b);
void		normalize_vector(t_dot *vector);
double		intersect_ray_sphere(t_dot cam_sphere, t_dot *ray,
				t_figure *sphere);
double		cone_dot_product_of_vectors(t_dot *vector_a, t_dot *vector_b,
				double tan);
double		vector_length(t_dot *vector);
int			create_trgb(int t, int r, int g, int b);
t_dot		subtraction_vector(t_dot *vector_a, t_dot *vector_b);
void		my_mlx_pixel_put(t_inf *data, int x, int y, int color);
t_rgb		new_rgb(double x, double y, double z, t_inf *inf);
t_dot		new_dot(double x, double y, double z);
t_inf		*parse(char *filename);
double		ft_dbatoi(char *str, t_inf *inf);
int			ft_arrlen(char **split);
void		ft_clean_split(char **split);
t_rgb		set_rgb(t_inf *inf, char *str);
t_dot		set_coordinates(t_inf *inf, char *str, char flag);
t_figure	*ft_last_figure(t_figure *fig);
void		free_exit(char *desc, t_inf *inf, int exit_code);
void		*free_split(char **split);
t_rgb		change_color_intensity(t_rgb *color, double intense);
double		cyl_and_cap_inter(t_dot o, t_dot *d, t_figure *cyl);
double		compute_lightning(t_dot vec_l, t_inf *inf, double spec,
				t_parametrs *params);
t_dot		multiply_vector(t_dot *vector, double num);
t_dot		addition_vector(t_dot *vector_a, t_dot *vector_b);
void		closest_intersection(t_dot *origin, t_inf *inf, t_intersec *cls);
t_rgb		addition_rgb(t_rgb col1, t_rgb col2);
t_dot		reflect_ray(t_dot *v1, t_dot *v2);
void		get_color(t_dot *origin, t_rgb *rgb, char depth, t_inf *inf);
t_rgb		addition_rgb(t_rgb col1, t_rgb col2);
t_dot		reflect_ray(t_dot *v1, t_dot *v2);
void		ray_tracing(t_inf *inf, int mlx_y, int mlx_x, double y);
char		is_intersect(t_intersec *cls, t_inf *inf, t_dot *origin,
				double flag);
void		reflection(t_rgb *rgb, t_parametrs *params,
				t_inf *inf, char depth);
void		closest_sphere(t_dot *origin, t_figure *figure, t_inf *inf,
				t_intersec *cls);
double		intersect_ray_plane(t_dot o, t_dot *ray, t_dot *coordinates,
				t_dot *orientation_vec);
double		distance(t_dot p1, t_dot p2);
t_dot		vec_cross(t_dot *vector_a, t_dot *vector_b);
t_dot		vec_add(t_dot vector_a, t_dot vector_b);
t_dot		sub(t_dot a, t_dot b);
double		cone_and_cap_inter(t_dot o, t_dot *d, t_figure *cyl);
double		dot(t_dot a, t_dot b);
t_dot		normalize(t_dot a);
t_dot		add(t_dot a, t_dot b);
t_dot		ft_scale(t_dot a, double b);
void		ft_get_normal(t_ray ray, t_dot obj_pos,
				t_inter_point *inter_point);
double		get_norm(t_dot vect);
double		min(double a, double b);
double		set_radius(double diametr, t_inf *inf);
char		set_light(t_inf *inf, char **split);
char		set_cylinder(t_inf *inf, char **split, char type);
char		set_plane(t_inf *inf, char **split);
char		set_sphere(t_inf *inf, char **split);
char		set_ambient(t_inf *inf, char **split);
t_rgb		change_color_light(t_inf *inf, t_rgb *start_rgb);

#endif

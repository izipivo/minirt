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

#include "minirt.h"

static double	cyl_intersect_ray_plane(t_dot *o, t_dot *ray,
				t_dot *coordinates, t_dot *orientation_vec)
{
	t_dot	hui;
	double	tt;
	double	denom;

	tt = DBL_MAX;
	denom = dot_product_of_vectors(orientation_vec, ray);
	if (denom == 0)
		return (tt);
	hui = subtraction_vector(coordinates, o);
	tt = dot_product_of_vectors(orientation_vec, &hui) / denom;
	if (tt <= 0)
		return (DBL_MAX);
	return (tt);
}

double	cap_intersection(t_dot *o, t_dot *d, t_figure *cyl,
		t_dot (*func)(t_dot*, t_dot*))
{
	double	id1;
	double	lol;
	t_dot	ip1;
	t_dot	c1;
	t_dot	mult;

	ip1 = multiply_vector(&cyl->orientation_vec, cyl->height / 2.0);
	c1 = (*func)(&cyl->coordinates, &ip1);
	id1 = cyl_intersect_ray_plane(o, d, &c1, &cyl->orientation_vec);
	if (id1 < DBL_MAX)
	{
		mult = multiply_vector(d, id1);
		ip1 = addition_vector(o, &mult);
		ip1 = subtraction_vector(&ip1, &c1);
		lol = dot_product_of_vectors(&ip1, &ip1);
		if (sqrt(lol) <= cyl->radius)
			return (id1);
	}
	return (DBL_MAX);
}

static double	capsssex(t_figure *cyl, t_dot *d, t_inter_point inter_point,
				t_dot *o)
{
	double	a;
	double	max;
	t_ray	ray;

	ray.origin = *o;
	ray.direction = *d;
	ft_get_normal(ray, cyl->coordinates, &inter_point);
	max = sqrt(pow(cyl->height / 2.0, 2) + pow(cyl->radius, 2));
	if (get_norm(sub(inter_point.coord, cyl->coordinates)) > max)
	{
		inter_point.t = (inter_point.t2);
		ft_get_normal(ray, cyl->coordinates, &inter_point);
	}
	if (get_norm(sub(inter_point.coord, cyl->coordinates)) > max)
		return (DBL_MAX);
	a = dot(cyl->orientation_vec, sub(inter_point.coord, cyl->coordinates));
	inter_point.normal = normalize(sub(inter_point.coord, add(cyl->coordinates,
					ft_scale(cyl->orientation_vec, a))));
	a = dot(ray.direction, inter_point.normal);
	if (a > 0)
		inter_point.normal = ft_scale(inter_point.normal, -1);
	return (inter_point.t);
}

double	intersect_ray_cylinder(t_dot *o, t_dot *d, t_figure *cyl)
{
	t_inter_point	inter_point;
	t_ri_cyl		ri;

	normalize_vector(&cyl->orientation_vec);
	ri.cross = vec_cross(d, &cyl->orientation_vec);
	ri.c_to_o = subtraction_vector(o, &cyl->coordinates);
	ri.cross2 = vec_cross(&ri.c_to_o, &cyl->orientation_vec);
	ri.sub = subtraction_vector(o, &cyl->coordinates);
	ri.a = dot_product_of_vectors(&ri.cross, &ri.cross);
	ri.b = 2 * dot_product_of_vectors(&ri.cross, &ri.cross2);
	ri.c = dot_product_of_vectors(&ri.cross2, &ri.cross2)
		- cyl->radius * cyl->radius;
	ri.delta = ri.b * ri.b - 4 * ri.c * ri.a;
	if (ri.delta < 0)
		return (DBL_MAX);
	inter_point.t1 = (-ri.b - sqrt(ri.delta)) / (2 * ri.a);
	inter_point.t2 = (-ri.b + sqrt(ri.delta)) / (2 * ri.a);
	if (inter_point.t2 < 0 && inter_point.t1 < 0)
		return (DBL_MAX);
	inter_point.t = inter_point.t1;
	if (inter_point.t2 < inter_point.t1)
		inter_point.t = inter_point.t2;
	return (capsssex(cyl, d, inter_point, o));
}

double	cyl_and_cap_inter(t_dot o, t_dot *d, t_figure *cyl)
{
	double	cyl_iner;
	double	cap1_inter;
	double	cap2_inter;

	cap1_inter = DBL_MAX;
	cap2_inter = DBL_MAX;
	cyl_iner = intersect_ray_cylinder(&o, d, cyl);
	cap1_inter = cap_intersection(&o, d, cyl, &addition_vector);
	cap1_inter = cap_intersection(&o, d, cyl, &subtraction_vector);
	return (min(min(cyl_iner, cap1_inter), cap2_inter));
}

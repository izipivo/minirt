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

double	intersect_ray_plane(t_dot o, t_dot *ray, t_dot *coordinates,
			t_dot *orientation_vec)
{
	double	numerator;
	double	denominator;
	double	sol;
	double	tt;

	tt = INT_MAX;
	(void)coordinates;
	denominator = dot_product_of_vectors(ray, orientation_vec);
	if (fabs(denominator) < EPSILON)
		return (tt);
	numerator = dot_product_of_vectors(&o, orientation_vec);
	sol = numerator / denominator;
	if (sol < EPSILON || DBL_MAX <= sol)
		return (tt);
	tt = sol;
	return (tt);
}

double	intersect_ray_sphere(t_dot cam_sphere, t_dot *ray, t_figure *sphere)
{
	double	b;
	double	c;
	double	a;
	double	disc;
	double	tt[2];

	tt[0] = DBL_MAX;
	tt[1] = DBL_MAX;
	a = dot_product_of_vectors(ray, ray);
	b = 2 * dot_product_of_vectors(&cam_sphere, ray);
	c = dot_product_of_vectors(&cam_sphere, &cam_sphere)
		- sphere->radius * sphere->radius;
	disc = b * b - 4 * a * c;
	if (disc < EPSILON)
		return (DBL_MAX);
	tt[0] = (-b - sqrt(disc)) / (2 * a);
	tt[1] = (-b + sqrt(disc)) / (2 * a);
	if (tt[0] <= tt[1])
		return (tt[0]);
	return (tt[1]);
}

double	cone_cap_intersection(t_dot *o, t_dot *d, t_figure *cyl,
		t_dot (*func)(t_dot*, t_dot*))
{
	double	id1;
	double	lol;
	t_dot	ip1;
	t_dot	c1;
	t_dot	mult;

	ip1 = multiply_vector(&cyl->orientation_vec, cyl->height / 2.0);
	c1 = (*func)(&cyl->coordinates, &ip1);
	id1 = intersect_ray_plane(*o, d, &c1, &cyl->orientation_vec);
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

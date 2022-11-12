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

t_dot	new_dot(double x, double y, double z)
{
	t_dot	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_rgb	new_rgb(double x, double y, double z, t_inf *inf)
{
	t_rgb	new;

	if (x < 0 || y < 0 || z < 0)
		free_exit(INCORRECT_RGB, inf, SYNTAX_ERROR);
	new.r = (unsigned char)x % 256;
	new.g = (unsigned char)y % 256;
	new.b = (unsigned char)z % 256;
	return (new);
}

t_dot	subtraction_vector(t_dot *vector_a, t_dot *vector_b)
{
	return (new_dot(vector_a->x - vector_b->x, vector_a->y - vector_b->y,
			vector_a->z - vector_b->z));
}

t_dot	addition_vector(t_dot *vector_a, t_dot *vector_b)
{
	t_dot	vector_c;

	vector_c = new_dot(vector_a->x + vector_b->x, vector_a->y + vector_b->y,
			vector_a->z + vector_b->z);
	return (vector_c);
}

double	vector_length(t_dot *vector)
{
	double	length;

	length = sqrt((vector->x * vector->x)
			+ (vector->y * vector->y) + (vector->z * vector->z));
	return (length);
}

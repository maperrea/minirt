/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:25:51 by maperrea          #+#    #+#             */
/*   Updated: 2020/12/01 18:35:43 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3		fvec3_div(t_fvec3 vec, double div)
{
	return ((t_fvec3){vec.x / div, vec.y / div, vec.z / div});
}

t_fvec3		fvec3_normalize(t_fvec3 vec)
{
	return (fvec3_div(vec, fvec3_length(vec)));
}

t_fvec3		fvec3_add(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_fvec3		fvec3_sub(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_fvec3		fvec3_product(t_fvec3 a, t_fvec3 b)
{
	return ((t_fvec3){(a.y * b.z) - (a.z * b.y),
						(a.z * b.x) - (a.x * b.z),
						(a.x * b.y) - (a.y * b.x)});
}

double		fvec3_dot_product(t_fvec3 a, t_fvec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_fvec3		fvec3_scalar_mult(t_fvec3 v, double x)
{
	return ((t_fvec3){v.x * x, v.y * x, v.z * x});
}

int			is_in_front(t_line3 normal, t_fvec3 vec)
{
	return (fvec3_dot_product(normal.dest, fvec3_sub(vec, normal.orig)) >= 0);
}

int 		is_closer(t_fvec3 a, t_fvec3 b)
{
	return (fvec3_length(a) <= fvec3_length(b));
}

double		fvec3_length(t_fvec3 vec)
{
	return(sqrt(fvec3_dot_product(vec, vec)));
}

t_line3		line_from_points(t_fvec3 orig, t_fvec3 dest)
{
	return ((t_line3){orig, fvec3_normalize(fvec3_sub(dest, orig))});
}

t_fvec3		*line_intersection(t_line3 a, t_line3 b)
{
	double	p;
	double	q;
	t_fvec3	*intersection;

	p = ((b.dest.y * (b.orig.x - a.orig.x)) + (b.dest.x * (a.orig.y - b.orig.y))) /
						((b.dest.y * a.dest.x) - (b.dest.x * a.dest.y));
	q = ((a.dest.x * (a.orig.y - b.orig.y)) + (a.dest.y * (b.orig.x - a.orig.x))) /
						((b.dest.y * a.dest.x) - (b.dest.x * a.dest.y));
	intersection = malloc(sizeof(t_fvec3));
	if (!intersection)
		return (NULL);
	intersection->x = a.orig.x + p * a.dest.x;
	intersection->y = a.orig.y + p * a.dest.y;
	intersection->z = a.orig.z + p * a.dest.z;
	return (intersection);
}

double		fvec3_angle(t_fvec3 a, t_fvec3 b)
{
	return(acos(fvec3_dot_product(fvec3_normalize(a), fvec3_normalize(b))));
}

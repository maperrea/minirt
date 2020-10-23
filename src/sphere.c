/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:59:33 by maperrea          #+#    #+#             */
/*   Updated: 2020/10/23 21:50:37 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3		substitute_in_line(t_line3 ray, double t)
{
	return ((t_fvec3){
			ray.orig.x + t * ray.dest.x,
			ray.orig.y + t * ray.dest.y,
			ray.orig.z + t * ray.dest.z
	});
}

/*
** c (params[2]) does not change for a given object -> optimisation to be done;
*/

double		*sphere_intersection_params(t_line3 ray, t_sphere *sphere)
{
	double	*params;

	if (!(params = malloc(sizeof(double) * 3)))
		return (NULL);
	params[0] = pow(fvec3_length(ray.dest), 2);
	params[1] = 2 * fvec3_dot_product(ray.dest, fvec3_sub(ray.orig, sphere->pos));
	params[2] = fvec3_dot_product(fvec3_sub(ray.orig, sphere->pos), fvec3_sub(ray.orig, sphere->pos)) - pow(sphere->radius, 2);
	return (params);
}

/*
** I should really split the return (NULL) if into multiple ones but yeah, norm
** also, I do the same if twice as it is slightly shorter
*/

t_fvec3		*sphere_intersection(t_line3 ray, void *sphere)
{
	t_fvec3		*result1;
	t_fvec3		*result2;
	double		*t;
	double		*params;

	params = sphere_intersection_params(ray, sphere);
	//printf("params: %g %g %g\n", params[0], params[1], params[2]);
	t = resolve_second_degree(params[0], params[1], params[2]);
	free(params);
	result1 = malloc(sizeof(t_fvec3));
	result2 = malloc(sizeof(t_fvec3));
	if (!t || !result1 || !result2)
		return (NULL);
	*result1 = substitute_in_line(ray, t[0]);
	*result2 = substitute_in_line(ray, t[1]);
	//printf("t: %g | %g\n", t[0], t[1]);
	free(t);
	//printf("result1: %g\nresult2 :%p\n", result1, result2);
	if (fvec3_length(fvec3_sub(*result1, ray.orig))
			< fvec3_length(fvec3_sub(*result2, ray.orig)))
		free(result2);
	else
		free(result1);
	if (fvec3_length(fvec3_sub(*result1, ray.orig))
			< fvec3_length(fvec3_sub(*result2, ray.orig)))
		return (result1);
	else
		return (result2);
};

int			sphere_color(t_line3 ray, t_fvec3 intersection, void *sphere)
{
	int			color;
	t_objects	*closest;
	t_fvec3		closest_intersection;
	t_lights	*lights;
	t_line3		line;
	t_line3		normal;

	(void)ray;
	lights = g_lights;
	color = color_multiply(g_ambient_light.color, g_ambient_light.power);
	normal = line_from_points(((t_sphere *)sphere)->pos, intersection);
	while (lights)
	{
		if (is_in_front(normal, lights->get_pos(lights->light)))
		{
			line = line_from_points(intersection, lights->get_pos(lights->light));
			closest = get_closest_obj(line, &closest_intersection, sphere);
			if (!closest ||
					!is_closer(fvec3_sub(closest_intersection, intersection),
					fvec3_sub(lights->get_pos(lights->light), intersection)))
			{
				color = color_add(color, 
					color_multiply(lights->get_luminosity(lights->light),
				(M_PI_2 - fvec3_angle(normal.dest, line.dest) / M_PI_2)));
				printf("%.2f,%.2f,%.2f %.2f,%.2f,%.2f\n%.2f\n", normal.dest.x, normal.dest.y, normal.dest.z, line.dest.x, line.dest.y, line.dest.z, fvec3_angle(normal.dest, line.dest));
			}
		}
		lights = lights->next;
	}
	color = color_reflect(((t_sphere *)sphere)->color, color);
	return (color);
}

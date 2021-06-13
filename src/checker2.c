/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maperrea <maperrea@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 17:47:24 by maperrea          #+#    #+#             */
/*   Updated: 2021/06/13 17:49:03 by maperrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_c(char *line, int line_nbr)
{
	static t_checker	*checkers[4]
		= {&check_fvec3, &check_fvec3, &check_float, NULL};
	static void			*args[3] = {NULL, NULL, NULL};

	line++;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	required_params(0, 0, 1);
	return (1);
}

int	check_l(char *line, int line_nbr)
{
	static t_checker	*checkers[4]
		= {&check_fvec3, &check_float, &check_color, NULL};
	static void			*args[3] = {NULL, NULL, NULL};

	line++;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

int	check_sp(char *line, int line_nbr)
{
	static t_checker	*checkers[4]
		= {&check_fvec3, &check_float, &check_color, NULL};
	static void			*args[3] = {NULL, NULL, NULL};

	line += 2;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

int	check_pl(char *line, int line_nbr)
{
	static t_checker	*checkers[4]
		= {&check_fvec3, &check_fvec3, &check_color, NULL};
	static void			*args[3] = {NULL, NULL, NULL};

	line += 2;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

int	check_cy(char *line, int line_nbr)
{
	static t_checker	*checkers[6]
		= {&check_fvec3, &check_fvec3, &check_float,
			&check_float, &check_color, NULL};
	static void			*args[5] = {NULL, NULL, NULL, NULL, NULL};

	line += 2;
	if (!line_checker(line, checkers, args))
	{
		printf("Error: line %d: wrong format\n", line_nbr);
		exit(1);
	}
	return (1);
}

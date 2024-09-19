/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:58:58 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/18 20:30:15 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

double	cool_map(double unscaled_num, double new_min, double new_max,
				double old_max)
{
	return (((new_max - new_min) * (unscaled_num) / (old_max) + new_min));
}
double cool_map2(int value, double min, double max, int dimension)
{
	if (dimension <= 0)
		return (0);
	return min + (max - min) * ((double)value / (double)dimension);
}


t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	res;

	res.real = z1.real + z2.real;
	res.i = z1.i + z2.i;
	return (res);
}

t_complex	square_complex(t_complex z)
{
	t_complex	res;

	res.real = (z.real * z.real) - (z.i * z.i);
	res.i = 2 * z.real * z.i;
	return (res);
}

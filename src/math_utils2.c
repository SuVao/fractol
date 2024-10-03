/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:30:07 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/28 16:30:11 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	void_calc(t_fractal *fractal, int x, int y, t_complex c)
{
	static double	c2;

	c2 = (c.real * c.real) + (c.i * c.i);
	if (256.0 * c2 * c2 - 96.0 * c2 + 32.0 * c.real - 3.0 < 0.0 \
		|| 16.0 * (c2 + 2.0 * c.real + 1.0) - 1.0 < 0.0)
	{
		my_pixel_put(&fractal->img, x, y, BLACK);
		return (1);
	}
	return (0);
}

t_complex	phoenix_calc(t_complex z, t_complex z_prev, t_fractal *fractal)
{
	t_complex	res;

	res.real = (z.real * z.real) - (z.i * z.i) + fractal->input1 \
				+ (fractal->input3 * z_prev.real);
	res.i = 2 * z.real * z.i + (-1 * fractal->input2) \
			+ (fractal->input3 * z_prev.i);
	return (res);
}

int	positive(char c, int *sign)
{
	if (c == '-' || c == '+')
	{
		if ('-' == c)
		{
			*sign = -1;
			return (1);
		}
	}
	return (0);
}

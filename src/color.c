/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:17:05 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/26 20:07:18 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

double	clamp(double x, double min_val, double max_val)
{
	if (x < min_val)
		return (min_val);
	else if (x > max_val)
		return (max_val);
	else
		return (x);
}

int	quilez_color(double l, t_color *colors)
{
	colors->r_1 = colors->r;
	colors->g_1 = colors->g;
	colors->b_1 = colors->b;
	colors->r = 0.5 + 0.5 * cos(3.0 + l * 0.15);
	colors->g = 0.5 + 0.5 * cos(3.0 + l * 0.15 + 0.6);
	colors->b = 0.5 + 0.5 * cos(3.0 + l * 0.15 + 1.0);
	colors->red = (int)(colors->r * 255.0);
	colors->green = (int)(colors->g * 255.0);
	colors->blue = (int)(colors->b * 255.0);
	return ((colors->red << 16) | (colors->green << 8) | colors->blue);
}

int	interpolate_color(double t, t_fractal *fractal, int use_quilez)
{
	int		start_r;
	int		start_g;
	int		start_b;

	if (use_quilez)
	{
		fractal->fcolor = quilez_color(t * 512.0, &fractal->colors);
	}
	else
	{
		start_r = fractal->colors.r_1 * 255;
		start_g = fractal->colors.g_1 * 255;
		start_b = fractal->colors.b_1 * 255;
		fractal->colors.red = (int)((1 - t) * start_r + t * 255);
		fractal->colors.green = (int)((1 - t) * start_g + t * 123);
		fractal->colors.blue = (int)((1 - t) * start_b + t * 255);
		fractal->colors.red = clamp(fractal->colors.red, 0, 255);
		fractal->colors.green = clamp(fractal->colors.green, 0, 255);
		fractal->colors.blue = clamp(fractal->colors.blue, 0, 255);
		fractal->fcolor = (fractal->colors.red << 8) \
						| (fractal->colors.green << 16) \
						| fractal->colors.blue;
	}
	return (fractal->fcolor);
}

double	smooth_iteration(int i, t_complex z)
{
	double	log_zn;
	double	log_2;

	log_zn = log(sqrt(z.real * z.real + z.i * z.i));
	log_2 = log(2.0);
	if (log_zn == 0)
		return (i + 1);
	return (i + 1 - log(log_zn) / log_2);
}

int	smoothed_coloring(t_fractal *fractal, int i, t_complex z)
{
	static double	smooth_i;
	static double	smoothed_color;
	static int		color;

	smooth_i = smooth_iteration(i, z);
	smoothed_color = smoothstep(-1, 1, smooth_i / fractal->iters, fractal);
	color = interpolate_color(smoothed_color, fractal, fractal->use_quilez);
	return (color);
}

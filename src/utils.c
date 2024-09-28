/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:30:42 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/28 16:30:45 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

double	map_x(int x, double min, double max, t_fractal *fractal)
{
	min = min * fractal->zoom + fractal->shift_x;
	max = max * fractal->zoom + fractal->shift_x;
	return (min + ((double)x / WIDTH) * (max - min));
}

double	map_y(int y, double min, double max, t_fractal *fractal)
{
	min = min * fractal->zoom + fractal->shift_y;
	max = max * fractal->zoom + fractal->shift_y;
	return (min + ((double)y / HEIGHT) * (max - min));
}

void	zoom_in(int key, t_fractal *fractal, int x, int y)
{
	static double	mouse_x;
	static double	mouse_y;

	mouse_x = map_x(x, -2.0, 2.0, fractal);
	mouse_y = map_y(y, 2.0, -2.0, fractal);
	if (key == SCROLL_UP)
		fractal->zoom *= 0.80;
	fractal->shift_x += (mouse_x - map_x(x, -2.0, 2.0, fractal));
	fractal->shift_y += (mouse_y - map_y(y, 2.0, -2.0, fractal));
	fractal_render(fractal);
}

void	zoom_out(t_fractal *fractal, int x, int y, int key)
{
	static double	mouse_x;
	static double	mouse_y;

	mouse_x = map_x(x, -2.0, 2.0, fractal);
	mouse_y = map_y(y, 2.0, -2.0, fractal);
	if (key == SCROLL_DOWN)
		fractal->zoom *= 1.20;
	fractal->shift_x += (mouse_x - map_x(x, -2.0, 2.0, fractal));
	fractal->shift_y += (mouse_y - map_y(y, 2.0, -2.0, fractal));
	fractal_render(fractal);
}

int	mouse_events(int key, int x, int y, t_fractal *fractal)
{
	if (key == SCROLL_UP)
		zoom_in(key, fractal, x, y);
	else if (key == SCROLL_DOWN)
		zoom_out(fractal, x, y, key);
	return (0);
}

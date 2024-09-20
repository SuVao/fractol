/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:49:36 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/20 16:53:44 by pesilva-         ###   ########.fr       */
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

void zoom_in(int key, t_fractal *fractal, int x, int y)
{
	double mouse_x;
	double mouse_y;

	mouse_x = map_x(x, -2.0, 2.0, fractal);
	mouse_y = map_y(y, 2.0, -2.0, fractal);
	if (key == SCROLL_UP)
		fractal->zoom *= 0.95;  // Zoom in
	fractal->shift_x += (mouse_x - map_x(x, -2.0, 2.0, fractal));
	fractal->shift_y += (mouse_y - map_y(y, 2.0, -2.0, fractal));
	fractal_render(fractal);
}

void	zoom_out(t_fractal *fractal, int x, int y, int key)
{
	double mouse_x;
	double mouse_y;

	mouse_x = map_x(x, -2.0, 2.0, fractal);
	mouse_y = map_y(y, 2.0, -2.0, fractal);
	if (key == SCROLL_DOWN)
		fractal->zoom *= 1.05;  // Zoom out
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

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == ESC || !fractal)
		ft_destroy(fractal);
	else if (keysym == XK_Down)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == LEFT)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == RIGHT)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == MINUS)
		fractal->iters -= 10;
	else if (keysym == PLUS)
		fractal->iters += 10;
	else if (keysym == DOT)
	{
		fractal->zoom = 1.0;
		fractal->shift_x = 0.0;
		fractal->shift_y = 0.0;
		fractal->iters = 42;
	}
	fractal_render(fractal);
	return 0;
}

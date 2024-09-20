/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:49:36 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/20 12:36:20 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

double	map_x(int x, double min, double max, t_fractal *fractal)
{
	min = min / fractal->zoom + fractal->center_x;
	max = max / fractal->zoom + fractal->center_x;
	return (min + ((double)x / WIDTH) * (max - min));
}

double	map_y(int y, double min, double max, t_fractal *fractal)
{
	min = min / fractal->zoom + fractal->center_y;
	max = max / fractal->zoom + fractal->center_y;
	return (min + ((double)y / HEIGHT) * (max - min));
}

void zoom_in(int key, t_fractal *fractal, int x, int y)
{
	fractal->world_x = 0.0;
	fractal->world_y = 0.0;
	fractal->pre_x = 0.0;
	fractal->pre_y = 0.0;
	fractal->pre_x = map_x(x, -2 , 2, fractal) * fractal->zoom;
	fractal->pre_y = map_y(y, 2, -2, fractal)  * fractal->zoom;
	if (key == SCROLL_UP)
		fractal->zoom *= 0.95;  // Zoom in
	printf("shift_x: %f shift_y: %f\n", fractal->shift_x, fractal->shift_y);
	printf("x: %d y: %d\n", x, y);
	printf("world_x: %f world_y: %f\n", fractal->world_x, fractal->world_y);
	printf("center_x: %d center_y: %d \n", fractal->center_x, fractal->center_y);
	/* fractal->world_x = map_x(x, -2, 2, fractal) * fractal->zoom;
    fractal->world_y = map_y(y, 2, -2, fractal) * fractal->zoom; */
	fractal->shift_x *= fractal->zoom;
    fractal->shift_y *= fractal->zoom;
	fractal_render(fractal);
}

void	zoom_out(t_fractal *fractal, int x, int y, int key)
{
	fractal->world_x = 0.0;
	fractal->world_y = 0.0;
	fractal->pre_x = 0.0;
	fractal->pre_y = 0.0;
	fractal->pre_x = map_x(x, -2 , 2, fractal);
	fractal->pre_y = map_y(y, 2, -2, fractal);
	if (key == SCROLL_DOWN)
		fractal->zoom *= 1.05;
	printf("shift_x: %f shift_y: %f\n", fractal->shift_x, fractal->shift_y);
	printf("x: %d y: %d\n", x, y);
	printf("world_x: %f world_y: %f\n", fractal->world_x, fractal->world_y);
	printf("center_x: %d center_y: %d \n", fractal->center_x, fractal->center_y);
	/* fractal->world_x = map_x(x, -2, 2, fractal) * fractal->zoom;
    fractal->world_y = map_y(y, 2, -2, fractal) * fractal->zoom; */
	fractal->shift_x = (x - (WIDTH / 2)) / (WIDTH / 2) * fractal->zoom;
    fractal->shift_y = (y - (HEIGHT / 2)) / (HEIGHT / 2) * fractal->zoom;
	fractal_render(fractal);
}

/* void zoom_out(int key, t_fractal *fractal, int x, int y)
{
	fractal->center_x = 
	fractal->world_x = 0.0;
	fractal->world_y = 0.0;
	fractal->world_x = (x - WIDTH / 2) * fractal->zoom + fractal->shift_x;
	fractal->world_y = (y - WIDTH / 2) * fractal->zoom + fractal->shift_y;
	if (key == SCROLL_DOWN)
		fractal->zoom *= 1.05;  // Zoom out
	fractal->shift_x = fractal->world_x - (x - WIDTH / 2) * fractal->zoom;
	fractal->shift_y = fractal->world_y - (y - HEIGHT / 2) * fractal->zoom;
	fractal_render(fractal);
} */
// centro do x e y 
//x = x - WIDTH / 2
//y = y - HEIGHT / 2
//x = x / (WIDTH / 2)
// shift_x = x 


int	mouse_events(int key, int x, int y, t_fractal *fractal)
{
	fractal->center_x = fractal->shift_x;
	fractal->center_y = fractal->shift_y;
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
		fractal->center_y -= (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->center_y += (0.5 * fractal->zoom);
	else if (keysym == LEFT)
		fractal->center_x -= (0.5 * fractal->zoom);
	else if (keysym == RIGHT)
		fractal->center_x += (0.5 * fractal->zoom);
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
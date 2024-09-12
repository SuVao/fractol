/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:49:36 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/12 17:48:22 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	zoom(int key, t_fractal *fractal, int x, int y)
{
	if (key == SCROLL_UP)
	{
		fractal->zoom *= 1.1;
		fractal->shift_x *= 1.1;
		fractal->shift_y *= 1.1; 
		fractal->shift_x = fractal->shift_x / SCALER + x;
		fractal->shift_y = fractal->shift_y / SCALER + y;
		/* fractal->shift_x += ((x - WIDTH / 2) * 0.1);
		fractal->shift_y += ((y - HEIGHT / 2) * 0.1); */
		fractal_render(fractal);
	}
	else if (key == SCROLL_DOWN)
	{
		fractal->zoom /= SCALER;
		fractal->shift_x = fractal->shift_x / SCALER + x;
		fractal->shift_y = fractal->shift_y / SCALER + y;
		fractal_render(fractal);
	}
}

int	mouse_events(int key, int x, int y, t_fractal *fractal)
{
	int	tmp_x;
	int tmp_y;
	
	if (!fractal)
		return (0);
	tmp_x = (x - (WIDTH / 2)) * 0.1;
	tmp_y = (y - (HEIGHT / 2)) * 0.1;
	if (key == SCROLL_UP || key == 4)
		zoom(key, fractal, tmp_x, tmp_y);
	else if (key == SCROLL_DOWN || key == 5)
		zoom(key, fractal, tmp_x, tmp_y);
	return (0);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == ESC || !fractal)
		ft_destroy(fractal);
	else if (keysym == XK_Down)
		fractal->shift_y += 0.5;
	else if (keysym == XK_Up)
		fractal->shift_y -= 0.5;
	else if (keysym == LEFT)
		fractal->shift_x += 0.5;
	else if (keysym == RIGHT)
		fractal->shift_x -= 0.5;
	else if (keysym == MINUS)
		fractal->iters -= 10;
	else if (keysym == PLUS)
		fractal->iters += 10;
	else if (keysym == DOT)
		fractal_render(fractal);
	fractal_render(fractal);
	return 0;
}
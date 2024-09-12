/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:49:36 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/11 22:54:49 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int zoom_in(int key, t_fractal *fractal)
{
	
}

int	zoom_out(int key, t_fractal *fractal)
{
	
}

int	mouse_events(int key, t_fractal *fractal)
{
	if (key == SCROLL_DOWN)
		zoom_out(key, fractal);
	else if (key == SCROLL_UP)
		zoom_in(key, fractal);
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
	else if (keysym == SCROLL_DOWN || keysym == SCROLL_UP)
		mouse_events(keysym, fractal);
	fractal_render(fractal);
	return 0;
}
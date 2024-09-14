/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:49:36 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/15 00:47:30 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void zoom(int key, t_fractal *fractal, int x, int y)
{
    // Mapeia as coordenadas do rato para as coordenadas do mundo da fractal
    fractal->mouse_world_x = (x - fractal->mouse_x) * fractal->zoom + fractal->shift_x;
    fractal->mouse_world_y = (y - fractal->mouse_y) * fractal->zoom + fractal->shift_y;

    // Aplica o zoom
    if (key == SCROLL_UP)
        fractal->zoom *= 0.95;  // Zoom in
    else if (key == SCROLL_DOWN)
        fractal->zoom *= 1.05;  // Zoom out

    // Ajusta o deslocamento para manter o ponto do rato fixo após o zoom
    fractal->shift_x = fractal->mouse_world_x - (x - fractal->mouse_x) * fractal->zoom;
    fractal->shift_y = fractal->mouse_world_y - (y - fractal->mouse_y) * fractal->zoom;

    // Renderiza a fractal com as novas coordenadas
    fractal_render(fractal);
}
int	mouse_events(int key, int x, int y, t_fractal *fractal)
{
	int	tmp_x;
	int tmp_y;
	
	if (!fractal)
		return (0);
	tmp_x = (x - (fractal->mouse_x)) * 0.1;
	tmp_y = (y - (fractal->mouse_y)) * 0.1;
	if (key == SCROLL_UP)
		zoom(key, fractal, tmp_x, tmp_y);
	else if (key == SCROLL_DOWN)
		zoom(key, fractal, tmp_x, tmp_y);
	return (0);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == ESC || !fractal)
		ft_destroy(fractal);
	else if (keysym == XK_Down)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == LEFT)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == RIGHT)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == MINUS)
		fractal->iters -= 10;
	else if (keysym == PLUS)
		fractal->iters += 10;
	else if (keysym == DOT)
	{
		fractal->zoom = 1.0;
		fractal->shift_x = 0.0;
		fractal->shift_y = 0.0;
	}
	fractal_render(fractal);
	return 0;
}
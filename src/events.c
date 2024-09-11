/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:49:36 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/11 17:25:40 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

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
	fractal_render(fractal);
	return 0;
}
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

int	arrows_events(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Down || keysym == S_K)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == XK_Up || keysym == W_K)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == LEFT || keysym == A_K)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == RIGHT || keysym == D_K)
		fractal->shift_x += (0.5 * fractal->zoom);
	return (0);
}

int	reset_fractal(t_fractal *fractal)
{
	fractal->zoom = 1.0;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->iters = 42;
	fractal->sm1 = 1.0;
	fractal->sm2 = 1.0;
	return (0);
}

int	if_quillez(t_fractal *fractal)
{
	if (fractal->use_quilez == 0)
		fractal->use_quilez = 1;
	else if (fractal->use_quilez == 1)
		fractal->use_quilez = 0;
	return (0);
}

int	reaction(int keysym, t_fractal *fractal)
{
	if (keysym == MINUS)
		fractal->iters -= 10;
	else if (keysym == PLUS)
		fractal->iters += 10;
	return (0);
}

int	r_g_b(int key, t_fractal *fractal)
{
	int	sign_r;
	int	sign_g;
	int	sign_b;

	sign_r = 0;
	sign_g = 0;
	sign_b = 0;
	if (key == R && sign_r == 0)
	{
		fractal->fcolor = COR_VERMELHO_FLUORESCENTE;
		sign_r = 1;
	}
	else if (key == R && sign_r == 1)
	{
		fractal->fcolor = COR_VERMELHO_FLUORESCENTE;
		sign_r = 0;
	}
	else if (key == G && sign_g == 0)
	{
		fractal->fcolor = COR_VERDE_NEON;
		sign_g = 1;
	}
	else if (key == G && sign_g == 1)
	{
		fractal->fcolor = COR_VERDE_LIMA;
		sign_g = 0;
	}
	else if (key == B && sign_b == 0)
	{
		fractal->fcolor = COR_AZUL_TURQUESA;
		sign_b = 1;
	}
	else if (key == B && sign_b == 1)
	{
		fractal->fcolor = STEEL_BLUE;
		sign_b = 0;
	}
	return (0);
}

int	smoth_st(int keysym, t_fractal *fractal)
{
	if (fractal->use_quilez == 1)
	{
		if (keysym == N_K)
			fractal->sm1 = 2.0;
		else if (keysym == M_K)
			fractal->sm1 = 3.0;
		else if (keysym == COMMA)
			fractal->sm1 = 9.0;
	}
	else if (fractal->use_quilez == 0)
	{
		if (keysym == N_K)
			fractal->colors.r_1 = 1.0;
		else if (keysym == M_K)
			fractal->fcolor = fractal->fcolor << 3;
		else if (keysym == COMMA)
			fractal->colors.b_1 = 1.0;
	}
	return (0);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == ESC || !fractal)
		ft_destroy(fractal);
	else if (keysym == XK_Down || keysym == XK_Up \
			|| keysym == LEFT || keysym == RIGHT)
		arrows_events(keysym, fractal);
	else if (keysym == W_K || keysym == S_K \
			|| keysym == A_K || keysym == D_K)
		arrows_events(keysym, fractal);
	else if (keysym == MINUS || keysym == PLUS)
		reaction(keysym, fractal);
	else if (keysym == R || keysym == G || keysym == B)
		r_g_b(keysym, fractal);
	else if (keysym == DOT)
		reset_fractal(fractal);
	else if (keysym == N_K || keysym == M_K || keysym == COMMA)
		smoth_st(keysym, fractal);
	else if (keysym == U_K)
		if_quillez(fractal);
	fractal_render(fractal);
	return (0);
}

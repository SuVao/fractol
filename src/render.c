/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:30:28 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/28 16:30:34 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	iters(t_fractal *fractal, t_complex z, int x, int y)
{
	if ((z.real * z.real) + (z.i * z.i) > fractal->escaped)
	{
		fractal->color_smoth = smoothed_coloring(fractal, fractal->i, z);
		my_pixel_put(&fractal->img, x, y, fractal->color_smoth);
		return (0);
	}
	return (1);
}

void	phoenix_render(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	z_temp;
	t_complex	z_prev;
	int			i;

	i = 0;
	z.i = cool_map(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
	z.real = cool_map(y, +2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	z_prev.real = 0;
	z_prev.i = 0;
	while (i < fractal->iters)
	{
		z_temp = z;
		z = phoenix_calc(z_temp, z_prev, fractal);
		z_prev = z_temp;
		fractal->i = i;
		if (!iters(fractal, z, x, y))
			return ;
		i++;
	}
	my_pixel_put(&fractal->img, x, y, BLACK);
}

void	mandelbrot_render(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;

	i = 0;
	z.real = cool_map(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
	z.i = cool_map(y, +2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	c.real = z.real;
	c.i = z.i;
	if (void_calc(fractal, x, y, c))
		return ;
	while (i < fractal->iters)
	{
		z = sum_complex(square_complex(z), c);
		fractal->i = i;
		if (!iters(fractal, z, x, y))
			return ;
		i++;
	}
	my_pixel_put(&fractal->img, x, y, BLACK);
}

void	julia_render(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;

	i = 0;
	z.real = cool_map(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
	z.i = cool_map(y, +2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	c.real = fractal->input1;
	c.i = fractal->input2;
	if (void_calc(fractal, x, y, c))
		return ;
	while (i < fractal->iters)
	{
		z = sum_complex(square_complex(z), c);
		fractal->i = i;
		if (!iters(fractal, z, x, y))
			return ;
		i++;
	}
	my_pixel_put(&fractal->img, x, y, BLACK);
}

void	fractal_render(t_fractal *fractal)
{
	static int	x;
	static int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (!ft_strncmp(fractal->name, "julia", 5))
				julia_render(x, y, fractal);
			else if (!ft_strncmp(fractal->name, "mandelbrot", 10))
				mandelbrot_render(x, y, fractal);
			else if (!ft_strncmp(fractal->name, "phoenix", 10))
				phoenix_render(x, y, fractal);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx_connetion, fractal->mlx_window, \
							fractal->img.img, 0, 0);
}

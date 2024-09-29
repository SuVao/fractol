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

t_complex	multiply_complex(t_complex a, t_complex b)
{
	t_complex result;

	result.real = (a.real * b.real) - (a.i * b.i);
	result.i = (a.real * b.i) + (a.i * b.real);
	return (result);
}

double	smoothstep(double edge0, double edge1, double x, t_fractal *fractal)
{
	x = clamp(((x - edge0)) / (fractal->sm1 * \
			(edge1 - edge0)), 0.0, 1.0);
	return (x * x * (3 - 2 * x));
}

void	my_pixel_put(t_data *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

void	mandel_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->real = fractal->input1;
		c->i = fractal->input2;
	}
	else if (!ft_strncmp(fractal->name, "mandelbrot", 10))
	{
		c->real = z->real;
		c->i = z->i;
	}
	else if (!ft_strncmp(fractal->name, "phoenix", 7))
	{
		c->real = fractal->input1;
		c->i = fractal->input2;
	}
}

int	iters(t_fractal *fractal, t_complex z, int i, int x, int y)
{
	if ((z.real * z.real) + (z.i * z.i) > fractal->escaped)
	{
		fractal->color_smoth = smoothed_coloring(fractal, i, z);
		my_pixel_put(&fractal->img, x, y, fractal->color_smoth);
		return (0);
	}
	return (1);
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
		if ((z.real * z.real) + (z.i * z.i) > fractal->escaped)
		{
			fractal->color_smoth = smoothed_coloring(fractal, i, z);
			my_pixel_put(&fractal->img, x, y, fractal->color_smoth);
			return ;
		}
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
		if ((z.real * z.real) + (z.i * z.i) > fractal->escaped)
		{
			fractal->color_smoth = smoothed_coloring(fractal, i, z);
			my_pixel_put(&fractal->img, x, y, fractal->color_smoth);
			return ;
		}
		i++;
	}
	my_pixel_put(&fractal->img, x, y, BLACK);
}

void	phoenix_render(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	t_complex	z_prev;
	t_complex 	z_temp;
	int			i;

	i = 0;
	z.real = cool_map(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
	z.i = cool_map(y, +2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	z_prev.real = 0;
	z_prev.i = 0;
	mandel_julia(&z, &c, fractal);
	if (void_calc(fractal, x, y, c))
		return ;
	while (i < fractal->iters)
	{
		z_temp = z;
		z = sum_complex(square_complex(z), multiply_complex(fractal->p, z_prev));
		z_prev = z_temp;
		if (!iters(fractal, z, i, x, y))
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

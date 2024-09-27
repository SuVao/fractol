#include "../inc/fractol.h"

double	smoothstep(double edge0, double edge1, double x, t_fractal *fractal)
{
	x = clamp((fractal->sm2 * (x - edge0)) / (fractal->sm1 * \
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
}

void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.real = cool_map(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
	z.i = cool_map(y, +2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	mandel_julia(&z, &c, fractal);
	if (void_calc(fractal, x, y, c))
		return ;
	while (i < fractal->iters)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.real * z.real) + (z.i * z.i) > fractal->escaped)
		{
			color = smoothed_coloring(fractal, i, z);
			my_pixel_put(&fractal->img, x, y, color);
			return ;
		}
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
			handle_pixel(x, y, fractal);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx_connetion, fractal->mlx_window, \
							fractal->img.img, 0, 0);
}

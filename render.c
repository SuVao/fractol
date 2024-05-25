#include "fractol.h"

void	my_pixel_put(t_data *img, int x, int y, int color)
{
	int offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.real = 0.0;
	z.i = 0.0;

	c.real = cool_map(x, -2, +2, WIDTH) + fractal->shift_x;
	c.i = cool_map(y, +2, -2, HEIGHT) + fractal->shift_y;

	while (i < fractal->iters)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.real * z.real) + (z.i * z.i) > fractal->escaped)
		{
			color = cool_map(i, WHITE, BLACK, fractal->iters);
			my_pixel_put(&fractal->img ,x, y, color);
			return ;
		}
		i++;
	}
	my_pixel_put(&fractal->img, x, y, BLACK);
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

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
	mlx_put_image_to_window(fractal->mlx_connetion, fractal->mlx_window, 
							fractal->img.img, 0, 0);
}
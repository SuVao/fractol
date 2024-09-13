#include "../fractol.h"

double smooth_iteration(int i, t_complex z)
{
	/* return i + 1 - log(log(sqrt(z.real * z.real + z.i * z.i))) / log(2.0); */
	double log_zn;
	double log_2;

	log_zn = log(sqrt(z.real * z.real + z.i * z.i));
	log_2  = log(2.0);
	if (log_zn == 0) // Prevenir divisão por zero
		return i + 1;

	return (i + 1 - log(log_zn) / log_2);
}

void	my_pixel_put(t_data *img, int x, int y, int color)
{
	int offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8)); //bits sao sempre 32
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

double smoothstep(double edge0, double edge1, double x)
{
	x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);

	return (x * x * (3 - 2 * x));
}

double clamp(double x, double min_val, double max_val)
{
	if (x < min_val)
		return min_val;
	else if (x > max_val)
		return max_val;
	else
		return x;
}

int interpolate_color(double t, int color1, int color2)
{
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;

	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;

	int r = (int)((1 - t) * r1 + t * r2);
	int g = (int)((1 - t) * g1 + t * g2);
	int b = (int)((1 - t) * b1 + t * b2);

	return ((r << 16) | (g << 8) | b);
}

void handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex z;
	t_complex c;
	int i;
	int color;
	double c2;
	double smooth_i;
	double smoothed_color;

	i = 0;
	z.real = 0.0;
	z.i = 0.0;
	c.real = (cool_map(x, -2, +2, WIDTH) * fractal->zoom) + fractal->shift_x;
	c.i = (cool_map(y, +2, -2, HEIGHT) * fractal->zoom)+ fractal->shift_y;
	fractal->ori_x = c.real;
	fractal->ori_y = c.i;
	/* printf("x: %f, y: %f\n", fractal->ori_x, fractal->ori_y); */
	c2 = (c.real * c.real) + (c.i * c.i);

	if (256.0 * c2 * c2 - 96.0 * c2 + 32.0 * c.real - 3.0 < 0.0 ||
		16.0 * (c2 + 2.0 * c.real + 1.0) - 1.0 < 0.0)
	{
		my_pixel_put(&fractal->img, x, y, BLACK);
		return;
	}
	while (i < fractal->iters)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.real * z.real) + (z.i * z.i) > fractal->escaped)
		{
			smooth_i = smooth_iteration(i, z);
			smoothed_color = smoothstep(-0.5, 0.5, smooth_i / fractal->iters);
			color = interpolate_color(smoothed_color, BLACK, COR_MAGENTA_PSICODELICO);
			my_pixel_put(&fractal->img, x, y, color);
			return;
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

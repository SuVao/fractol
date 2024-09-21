#include "../inc/fractol.h"

double	smooth_iteration(int i, t_complex z)
{
	double	log_zn;
	double	log_2;

	log_zn = log(sqrt(z.real * z.real + z.i * z.i));
	log_2 = log(2.0);
	if (log_zn == 0)
		return (i + 1);
	return (i + 1 - log(log_zn) / log_2);
}

void	my_pixel_put(t_data *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

double	smoothstep(double edge0, double edge1, double x)
{
	x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
	return (x * x * (3 - 2 * x));
}

double	clamp(double x, double min_val, double max_val)
{
	if (x < min_val)
		return (min_val);
	else if (x > max_val)
		return (max_val);
	else
		return (x);
}

// int	interpolate_color(double t, t_fractal *fractal, int i)
// {
// 	int		red;
// 	int		green;
// 	int		blue;
// 	int		color;

// 	red = (int)(fractal->r) * (255 * ((1 - (i * CL))) + t);
// 	green = (int)(fractal->g) * (255 * ((1 - (i * CL))) + t);
// 	blue = (int)(fractal->b) * (255 * ((1 - (i * CL))) + t);
// 	color = red << 16 | green << 8 | blue;
// 	return (color);
// }

// int interpolate_color(double t, t_fractal *fractal, int i)
// {
// 	int		red;
// 	int		green;
// 	int		blue;
// 	int		color;

// 	(void)i;
// 	// Usa o valor de t para calcular as cores de forma progressiva
// 	red = (int)((fractal->r) * (255 * (1 - t)) + (t * 255));
// 	green = (int)((fractal->g) * (255 * (1 - t)) + (t * 255));
// 	blue = (int)((fractal->b) * (255 * (1 - t)) + (t * 255));

// 	// Garante que os valores de cor fiquem dentro do intervalo válido
// 	red = clamp(red, 0, 255);
// 	green = clamp(green, 0, 255);
// 	blue = clamp(blue, 0, 255);

// 	// Junta os valores de red, green, blue em um único valor de cor
// 	color = (red << 16) | (green << 8) | blue;
// 	return (color);
// }

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

void	void_calc(t_fractal *fractal, int x, int y, t_complex c)
{
	double	c2;

	c2 = (c.real * c.real) + (c.i * c.i);
	if (256.0 * c2 * c2 - 96.0 * c2 + 32.0 * c.real - 3.0 < 0.0 \
		|| 16.0 * (c2 + 2.0 * c.real + 1.0) - 1.0 < 0.0)
	{
		my_pixel_put(&fractal->img, x, y, BLACK);
		return ;
	}
}

int	smoothed_coloring(t_fractal *fractal, int i, t_complex z)
{
	double	smooth_i;
	double	smoothed_color;
	int		color;

	smooth_i = smooth_iteration(i, z);
	smoothed_color = smoothstep(-1, 1, smooth_i / fractal->iters);
	color = interpolate_color(smoothed_color, BLACK, WHITE);
	return (color);
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
	c.real = cool_map(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
	c.i = cool_map(y, +2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	void_calc(fractal, x, y, c);
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
	mlx_put_image_to_window(fractal->mlx_connetion, fractal->mlx_window, \
							fractal->img.img, 0, 0);
}

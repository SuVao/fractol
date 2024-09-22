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

int quilez_color(double l)
{
	double r, g, b;

	// Geração de cores com base na lógica de Inigo Quilez
	r = 0.5 + 0.5 * cos(3.0 + l * 0.15);
	g = 0.5 + 0.5 * cos(3.0 + l * 0.15 + 0.6);
	b = 0.5 + 0.5 * cos(3.0 + l * 0.15 + 1.0);

	// Converter para o formato RGB
	int red = (int)(r * 255.0);
	int green = (int)(g * 255.0);
	int blue = (int)(b * 255.0);

	// Retornar a cor no formato hexadecimal (0xRRGGBB)
	return (red << 16) | (green << 8) | blue;
}

// int interpolate_color(double t, t_fractal *fractal, int use_quilez)
// {
// 	// Se use_quilez for verdadeiro (diferente de 0), usa a paleta de Quilez
// 	if (use_quilez)
// 	{
// 		// Mapeia t para a função quilez_color
// 		fractal->color = quilez_color(t * 512.0); // Mapeando t para a escala de iterações
// 	}
// 	else
// 	{
// 		// Interpolação de cores personalizada usando r, g, b
// 		fractal->red = (int)((fractal->r) * (255 * (1 - t)) + (t * 255));
// 		fractal->green = (int)((fractal->g) * (255 * (1 - t)) + (t * 255));
// 		fractal->blue = (int)((fractal->b) * (255 * (1 - t)) + (t * 255));

// 		// Garante que os valores de cor fiquem dentro do intervalo válido
// 		fractal->red = clamp(fractal->r +   fractal->red, 0, 255);
// 		fractal->green = clamp(fractal->g + fractal->green, 0, 255);
// 		fractal->blue =clamp(fractal->b +   fractal->blue, 0, 255);

// 		// Junta os valores de red, green, blue em um único valor de cor
// 		fractal->color = (fractal->red << 16) | (fractal->green << 8) | fractal->blue;
// 	}
// 	return (fractal->color);
// }

int interpolate_color(double t, t_fractal *fractal, int use_quilez)
{
	if (use_quilez)
	{
		// Usa a paleta de Quilez para calcular a cor
		fractal->color = quilez_color(t * 512.0);
	}
	else
	{
		// Valores de RGB base
		int start_r = fractal->r * 255; // cor inicial de r, g, b
		int start_g = fractal->g * 255;
		int start_b = fractal->b * 255;

		// Valores de RGB de destino (podes mudar as cores de destino conforme desejado)
		int end_r = 255; // cor final de r (branco ou outra cor de destino)
		int end_g = 0;   // cor final de g
		int end_b = 255; // cor final de b

		// Interpolação linear das cores com base no valor de t
		fractal->red = (int)((1 - t) * start_r + t * end_r);
		fractal->green = (int)((1 - t) * start_g + t * end_g);
		fractal->blue = (int)((1 - t) * start_b + t * end_b);

		// Assegura que as cores estão no intervalo válido (0 a 255)
		fractal->red = clamp(fractal->red, 0, 255);
		fractal->green = clamp(fractal->green, 0, 255);
		fractal->blue = clamp(fractal->blue, 0, 255);

		// Combina os valores RGB num único valor de cor
		fractal->color = (fractal->red << 16) | (fractal->green << 8) | fractal->blue;
	}
	return (fractal->color);
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
	color = interpolate_color(smoothed_color, fractal, fractal->use_quilez);
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

#include "../inc/fractol.h"

int	void_calc(t_fractal *fractal, int x, int y, t_complex c)
{
	static double	c2;

	c2 = (c.real * c.real) + (c.i * c.i);
	if (256.0 * c2 * c2 - 96.0 * c2 + 32.0 * c.real - 3.0 < 0.0 \
		|| 16.0 * (c2 + 2.0 * c.real + 1.0) - 1.0 < 0.0)
	{
		my_pixel_put(&fractal->img, x, y, BLACK);
		return (1);
	}
	return (0);
}

#include "../inc/fractol.h"

void	dat_init(t_fractal *fractal)
{
	if (!fractal)
		return ;
	fractal->escaped = 4;
	fractal->iters = 100;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->colors.r = 1.2;
	fractal->colors.g = 0.5;
	fractal->colors.b = 0.2;
	fractal->use_quilez = 1;
	fractal->colors.red = 1;
	fractal->colors.green = 1;
	fractal->colors.blue = 1;
	fractal->fcolor = 0x000000;
	fractal->sm1 = 1;
	fractal->sm2 = 1;
}

void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window, KeyPress,
							 KeyPressMask,
							 key_handler,
							 fractal);

	mlx_mouse_hook(fractal->mlx_window, &mouse_events, fractal);
	mlx_hook(fractal->mlx_window, DestroyNotify,
							 StructureNotifyMask,
							 ft_destroy,
							 fractal);
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connetion = mlx_init();
	if (fractal->mlx_connetion == NULL)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_connetion,
										WIDTH,
										HEIGHT,
										fractal->name);
	if (NULL == fractal->mlx_window)
		destroyer(fractal);
	fractal->img.img = mlx_new_image(fractal->mlx_connetion, WIDTH,
									HEIGHT);
	if (NULL == fractal->img.img)
		destroyer(fractal);
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img,
										&fractal->img.bits_per_pixel,
										&fractal->img.line_length,
										&fractal->img.endian);
	events_init(fractal);
	dat_init(fractal);
}

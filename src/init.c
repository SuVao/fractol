#include "../fractol.h"

void	dat_init(t_fractal *fractal)
{
	fractal->escaped = 4;
	fractal->iters = 42;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
/* 	fractal->ori_x = 0.0;
	fractal->ori_y = 0.0;
	fractal->zoom = 0.0; */
}

void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window, KeyPress,
							 KeyPressMask,
							 key_handler,
							 fractal);
	/* mlx_mouse_hook(fractal->mlx_window, zooming, fractal); */
/* 	mlx_hook(fractal->mlx_window, BottonPress,
							 BottonPressMask,
							 rato_handler,
							 fractal);*/
	mlx_mouse_hook(fractal->mlx_window, mouse_events, NULL);
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
	{
		mlx_destroy_display(fractal->mlx_connetion);
		free(fractal->mlx_connetion);
		malloc_error();
	}
	fractal->img.img = mlx_new_image(fractal->mlx_connetion, WIDTH,
									HEIGHT);
	if (NULL == fractal->img.img)
	{
		mlx_destroy_window(fractal->mlx_connetion, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_connetion);
		free(fractal->mlx_connetion);
		malloc_error();
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img,
										&fractal->img.bits_per_pixel,
										&fractal->img.line_length,
										&fractal->img.endian);
	events_init(fractal);
	dat_init(fractal);
}

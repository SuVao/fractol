#include "../inc/fractol.h"

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
	{
		fractal.name = av[1];
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connetion);
	}
	else if (4 == ac && !ft_strncmp(av[1], "julia", 5))
	{
		fractal.name = av[1];
		fractal.input1 = atod(av[2]);
		fractal.input2 = atod(av[3]);
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connetion);
	}
	/*else if (4 == ac && !ft_strncmp(av[1], "phoenix", 7))
	{
		fractal.name = av[1];
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connetion);
	} */
	else
	{
		ft_error();
		exit(EXIT_FAILURE);
	}
}

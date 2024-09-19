#include "../inc/fractol.h"

/* void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	t_data	img;
	void	*mlx;
	void	*mlx_win;
	int c = 0;
	unsigned int color;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 800, "Hello world!");
	img.img = mlx_new_image(mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
			&img.line_length, &img.endian);

	for (int i = 200; i <= 600; i++)
	{
		for (int j = 200; j <= 600; j++)
		{
			while (c < 10)
			{
				color = (rand() % 0x1000000);
				c++;
			}
			my_mlx_pixel_put(&img, j, i, color);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
} */

int main(int ac, char **av)
{
	t_fractal	fractal;
	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
	{
		fractal.name = av[1];
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connetion);
	}
	/* else if (4 == ac && !ft_strncmp(av[1], "julia", 5))
	{
		fractal.name = av[1];
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_connetion);
	}
	else if (4 == ac && !ft_strncmp(av[1], "phoenix", 7))
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
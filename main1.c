#include "fractol.h"

int	main(void)
{
	t_data	img;
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	mlx_loop(mlx);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
			&img.line_length, &img.endian);
}

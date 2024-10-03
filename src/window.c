/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:06:58 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/28 16:30:51 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	ft_destroy(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connetion, fractal->img.img);
	mlx_destroy_window(fractal->mlx_connetion, fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connetion);
	free(fractal->mlx_connetion);
	exit (EXIT_SUCCESS);
}

double	smoothstep(double edge0, double edge1, double x, t_fractal *fractal)
{
	x = clamp(((x - edge0)) / (fractal->sm1 * \
			(edge1 - edge0)), 0.0, 1.0);
	return (x * x * (3 - 2 * x));
}

void	my_pixel_put(t_data *img, int x, int y, int color)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

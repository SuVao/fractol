/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:04:50 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/20 16:54:06 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	ft_error(void)
{
	printf("./fractol <fractal set>\n");
	printf("Mandelbrot -> ./fractol mandelbrot\n");
	printf("Julia -> ./fractol julia <float 1> <float 2>\n");
	printf("Phoenix -> ./fractol phoenix <float 1> <float 2> <float 3>\n");
}

void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}

void	destroyer(t_fractal *fractal)
{
	if (fractal)
	{
		if (fractal->mlx_connetion && fractal->mlx_window)
			mlx_destroy_window(fractal->mlx_connetion, fractal->mlx_window);
		if (fractal->mlx_connetion)
		{
			mlx_destroy_display(fractal->mlx_connetion);
			free(fractal->mlx_connetion);
		}
		if (fractal)
			free(fractal);
	}
	malloc_error();
}

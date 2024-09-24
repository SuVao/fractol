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
	printf("Mandelbrot -> ./fractol Mandelbrot\n");
	printf("Julia -> ./fractol Julia <float 1> <float 2>\n");
	printf("Phoenix -> ./fractol Phoenix <float 1> <float 2> <float 3>\n");
}

void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}

void	msg_error(char	*s, t_fractal *fractal)
{
    int o;

	if (!s)
		return ;
	else
	{
		 o = write(2, s, sizeof(s));
		(void)o;
		ft_destroy(fractal);
	}
}

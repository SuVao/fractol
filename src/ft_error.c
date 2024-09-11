/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:04:50 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/02 18:36:44 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

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
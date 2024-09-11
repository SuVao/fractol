/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:06:58 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/02 18:37:08 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	ft_destroy(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connetion, fractal->img.img);
	mlx_destroy_window(fractal->mlx_connetion, fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_connetion);
	free(fractal->mlx_connetion);
	exit (EXIT_SUCCESS);
}

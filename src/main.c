/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:29:55 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/28 16:29:57 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

static void	phoenix_or_julia(int ac, char **av, t_fractal *fractal)
{
	if (ac == 5)
	{
		fractal->input1 = atod(av[2]);
		fractal->input2 = atod(av[3]);
		fractal->input3 = atod(av[4]);
	}
	else if (ac == 4)
	{
		fractal->input1 = atod(av[2]);
		fractal->input2 = atod(av[3]);
	}
}

static void	init_fract(int ac, char **av, t_fractal *fractal)
{
	phoenix_or_julia(ac, av, fractal);
	fractal->name = av[1];
	fractal_init(fractal);
	fractal_render(fractal);
	mlx_loop(fractal->mlx_connetion);
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if (ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
		init_fract(ac, av, &fractal);
	else if (4 == ac && !ft_strncmp(av[1], "julia", 5))
		init_fract(ac, av, &fractal);
	else if (5 == ac && !ft_strncmp(av[1], "phoenix", 7))
		init_fract(ac, av, &fractal);
	else
	{
		ft_error();
		exit(EXIT_FAILURE);
	}
}

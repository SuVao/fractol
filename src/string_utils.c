/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:57:55 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/26 19:57:57 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t nb)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (nb == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && i < nb - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	reset_fractal(t_fractal *fractal)
{
	fractal->zoom = 1.0;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->iters = 42;
	fractal->sm1 = 1.0;
	fractal->colors.k_r = 0.0;
	fractal->colors.k_g = 0.6;
	fractal->colors.k_b = 1.0;
	return (0);
}

int	smoth_st(int keysym, t_fractal *fractal)
{
	if (fractal->use_quilez == 1)
	{
		if (keysym == N_K)
			fractal->sm1 = 2.0;
		else if (keysym == M_K)
			fractal->sm1 = 3.0;
		else if (keysym == COMMA)
			fractal->sm1 = 9.0;
	}
	else if (fractal->use_quilez == 0)
	{
		if (keysym == N_K)
			fractal->sm1 = 2.0;
		else if (keysym == M_K)
			fractal->sm1 = 3.0;
		else if (keysym == COMMA)
			fractal->sm1 = 9.0;
	}
	return (0);
}

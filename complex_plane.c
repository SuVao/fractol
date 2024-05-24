/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:30:43 by pesilva-          #+#    #+#             */
/*   Updated: 2024/05/24 14:25:23 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* int main()
{
	t_complex	z;
	t_complex	c;
	double		tmp_real;
	z.real = 0;
	z.i = 0;

	c.real = 0.25;
	c.i = 0.4;

	for (int i = 0; i < 42; ++i)
	{
		tmp_real = (z.real * z.real) - (z.i * z.i);
		z.i = 2 * z.real * z.i;
		z.real = tmp_real;
		
		z.real += c.real;
		z.i += c.i;

		printf("iiteracoes: n-> %d real:%f imaginario:%f \n", i, z.real, z.i);
	}
	return (0);
} */
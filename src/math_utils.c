/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:58:58 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/18 20:30:15 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

double	cool_map(double unscaled_num, double new_min, double new_max,
				double old_max)
{
	return (((new_max - new_min) * (unscaled_num) / (old_max) + new_min));
}
double cool_map2(int value, double min, double max, int dimension)
{
	if (dimension <= 0)
		return (0);
	return min + (max - min) * ((double)value / (double)dimension);
}


t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	res;

	res.real = z1.real + z2.real;
	res.i = z1.i + z2.i;
	return (res);
}

t_complex	square_complex(t_complex z)
{
	t_complex	res;

	res.real = (z.real * z.real) - (z.i * z.i);
	res.i = 2 * z.real * z.i;
	return (res);
}

double	atod(char *str)
{
	double	result;
	double	decimal_part;
	int		sign;
	int		i;

	result = 0.0;
	decimal_part = 0.0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10.0) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		double divisor = 10.0;
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			decimal_part += (str[i] - '0') / divisor;
			divisor *= 10.0;
			i++;
		}
	}
	return (sign * (result + decimal_part));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:17:05 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/14 17:02:08 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
/* 
int interpolate_color(double t, int color1, int color2)
{
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;
	
	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;

	int r = (int)((1 - t) * r1 + t * r2);
	int g = (int)((1 - t) * g1 + t * g2);
	int b = (int)((1 - t) * b1 + t * b2);

	return ((r << 16) | (g << 8) | b);
} */

/* void	color_1(int color1, int	r1, int g1, int b1)
{
	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = color1 & 0xFF;
} */
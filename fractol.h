/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:58:00 by pesilva-          #+#    #+#             */
/*   Updated: 2024/05/24 17:13:07 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minilibx-linux/mlx.h"
#include <fcntl.h>

typedef struct	s_complex
{
	double	real;
	double	i;
}				t_complex;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	char	*pixels_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct s_fractal
{
	void	*mlx_connetion;
	void	*mlx_window;
	t_data	img;
	char	*name;
	double	escaped;
	int		iters;
}				t_fractal;

# define HEIGHT 800
# define WIDTH 800
# define MAX_ITER 1
# define KC 0.001
# define SCALER 0.1
# define XMIN 0.0
# define YMIN 0.0

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define COR_ROXA 0x800080
# define COR_VERDE_LIMA 0x00FF00
# define COR_ROSA_CHOQUE 0xFF007F
# define COR_AMARELO_BRILHANTE 0xFFFF00
# define COR_AZUL_TURQUESA 0x00FFFF
# define COR_LARANJA_PSICODELICO 0xFFA500
# define COR_MAGENTA_PSICODELICO 0xFF00FF
# define COR_CIANO_PSICODELICO 0x00FFEE
# define COR_VERDE_NEON 0x39FF14
# define COR_VERMELHO_FLUORESCENTE 0xFF2400


void		ft_error(void);
int			ft_strncmp(const char *s1, const char *s2, size_t nb);
void		fractal_init(t_fractal *fractal);
void		malloc_error(void);
double		cool_map(double unscaled_num, double new_min, double new_max,
				double old_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);
void		fractal_render(t_fractal *fractal);
void		dat_init(t_fractal *fractal);
void		my_pixel_put(t_data *img, int x, int y, int color);
void		handle_pixel(int x, int y, t_fractal *fractal);

#endif
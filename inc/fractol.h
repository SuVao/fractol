/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:21:03 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/20 16:53:04 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../minilibx-linux/mlx.h"
#include <fcntl.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <math.h>

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
	double	shift_x;
	double	shift_y;
	double		r;
	double		g;
	double		b;
	double	zoom;
	int		use_quilez;
	int		red;
	int		green;
	int		blue;
	int		color;
}				t_fractal;

# define HEIGHT 800
# define WIDTH 800
# define MAX_ITER 1
# define KC 0.001
# define SCALER 1.1
# define XMIN 0.0
# define YMIN 0.0

/*---------------KEYS---------------*/

# define ESC 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define NUMPLUS 65451
# define NUMMINUS 65453
# define NUMDOT 65439
# define DOT 46
# define MINUS 45
# define PLUS 61
# define IT 105
# define SPC 32
# define W_K 119
# define A_K 97
# define S_K 115
# define D_K 100
# define U_K 117
# define SHIFT 65505
# define R 114
# define G 103
# define B 98
# define SCROLL_UP 4
# define SCROLL_DOWN 5

/*--------------CORES----------------*/
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
# define STEEL_BLUE 0x4682B4
# define CASTANHO 0X964B00

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
int			key_handler(int keysym, t_fractal *fractal);
int			ft_destroy(t_fractal *fractal);
double		clamp(double x, double min_val, double max_val);
int			mouse_events(int key, int x, int y, t_fractal *fractal);
double		cool_map2(int value, double min, double max, int dimension);
void		zoom_out(t_fractal *fractal, int x, int y, int key);
double		map_x(int x, double min, double max, t_fractal *fractal);
double		map_y(int x, double min, double max, t_fractal *fractal);
void		msg_error(char	*s, t_fractal *fractal);
//int			interpolate_color(double t, int color1, int color2);
//int interpolate_color(double t);
int interpolate_color(double t, t_fractal *fractal, int use_quilez);

#endif

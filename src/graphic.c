/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:56:23 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/18 21:31:17 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"
#include "geometryfdf.h"
#include <math.h>

int	pixel_to_buffer(t_pixel pixel, t_image buffer)
{
	char	*adress;
	char			*pixel_mem;
	float			x;	
	float			y;	

	pixel_mem = NULL;
	adress = mlx_get_data_addr(buffer.img_context, &buffer.bit_pixel,\
							&buffer.size_line, &buffer.endian);
	clip_pixel(&pixel);
	x = matrix_get_coord(pixel.coords, 0, 0);
	y = matrix_get_coord(pixel.coords, 1, 0);
	if (adress == NULL || isnan(x) || isnan(y))
		return (1);
	pixel_mem = adress + (((int) y) * buffer.size_line) + (((int) x) * (buffer.bit_pixel / 8));
	ft_memcpy(pixel_mem, &pixel.color.value, sizeof(int));
	return (0);
}

void	color_buffer(t_color color, t_image buffer)
{
	size_t	counter;

	counter = 0;
	while (counter < W_WIDTH * W_HEIGHT)
		ft_memcpy(&(((int *)(buffer.img_content))[counter++]), &color.value, sizeof(int));
}

static	t_line	set_line_param(t_pixel a, t_pixel b)
{
	t_line	line;

	line.xa = (int)(matrix_get_coord(a.coords, 0, 0));
	line.ya = (int)(matrix_get_coord(a.coords, 1, 0));
	line.xb = (int)(matrix_get_coord(b.coords, 0, 0));
	line.yb = (int)(matrix_get_coord(b.coords, 1, 0));
	line.dx = abs(line.xb - line.xa);
	line.dy = abs(line.yb - line.ya);
	if (line.xa < line.xb)
		line.sx = 1;
	else
		line.sx = -1;
	if (line.ya < line.yb)
		line.sy = 1;
	else
		line.sy = -1;
	line.error = line.dx - line.dy;
	line.er2 = 2 * line.error;
	return (line);
}

static void	bound_pixel(t_pixel *pixel, size_t x, size_t y, float value, t_color color)
{
	pixel->color = color;
	matrix_set_coord(pixel->coords, x, y, value);
}
t_pixel	*clip_pixel(t_pixel *pixel)
{
	t_color	bound_color;

	bound_color = init_color(255, 0, 0, 0);
	if (matrix_get_coord(pixel->coords, 0, 0) >= W_WIDTH)
		bound_pixel(pixel, 0, 0, W_WIDTH - 1, bound_color);
	if (matrix_get_coord(pixel->coords, 0, 0) < 0)
		bound_pixel(pixel, 0, 0, 0, bound_color);
	if (matrix_get_coord(pixel->coords, 1, 0) >= W_HEIGHT)
		bound_pixel(pixel, 1, 0, W_HEIGHT - 1, bound_color);
	if (matrix_get_coord(pixel->coords, 1, 0) < 0)
		bound_pixel(pixel, 1, 0, 0, bound_color);
	return (pixel);
}

int	line_to_buffer(t_pixel point_a, t_pixel point_b, t_image buffer)
{
	t_line	line;
	t_pixel	pixel;

	line = set_line_param(point_a, point_b);
	pixel = init_pixel(point_a.color, (float) line.xa, (float) line.ya);
	if (pixel.coords == NULL)
		return (1);
	while (1)
	{
		pixel_to_buffer(pixel, buffer);
		if (line.xa == line.xb && line.ya == line.yb)
			break ;
		line.er2 = 2 * line.error;
		if (line.er2 > -line.dy)
		{
			line.error -= line.dy;
			line.xa += line.sx;
		}
		if (line.er2 < line.dx)
		{
			line.error += line.dx;
			line.ya += line.sy;
		}
		(pixel.coords->index)[0][0] = (float) line.xa;
		(pixel.coords->index)[1][0] = (float) line.ya;
	}
	free_pixel(&pixel);
	return (0);
}
static float	fixed_cosf(void)
{
	static float	angle;

	if (angle == 0.0F)
		angle = (float) cos(ISO_ANGLE * M_PI / 180);
	return (angle);
}
static float	fixed_sinf(void)
{
	static float	angle;

	if (angle == 0.0F)
		angle = (float) sin(ISO_ANGLE * M_PI / 180);
	return (angle);
}

t_pixel	project_vertex(t_vertex vertex, t_geometry *geo, t_color color)
{
	float	x;
	float	y;
	float	z;
	float	iso_x;
	float	iso_y;

	x = (matrix_get_coord(vertex.coords, 0, 0) - geo->center_x) * geo->scale;
	y = (matrix_get_coord(vertex.coords, 1, 0) - geo->center_y) * geo->scale;
	z = matrix_get_coord(vertex.coords, 2, 0) * (geo->scale / 2);
	iso_x = (x - y) * fixed_cosf();
	iso_y = (x + y) * fixed_sinf() - z;
	iso_x += W_WIDTH / 2;
	iso_y += W_HEIGHT / 2;
	return (init_pixel(color, iso_x, iso_y));
}


void	draw_geometry(t_env env, t_geometry *geometry, t_color color)
{
	size_t	i;
	t_edge	*edge_list;
	t_pixel	pixel_a;
	t_pixel	pixel_b;

	if (geometry == NULL || geometry->edge_list == NULL)
		return ;
	i = 0;
	edge_list = geometry->edge_list;
	while (edge_list[i].vtx_a != NULL)
	{
		pixel_a = project_vertex(*edge_list[i].vtx_a, geometry, color);
		if (pixel_a.coords == NULL)
			return ;
		pixel_b = project_vertex(*edge_list[i].vtx_b, geometry, color);
		if (pixel_b.coords == NULL)
		{
			free_pixel(&pixel_a);
			return ;
		}
		line_to_buffer(pixel_a, pixel_b, env.image);
		free_pixel(&pixel_a);
		free_pixel(&pixel_b);
		i++;
	}
}

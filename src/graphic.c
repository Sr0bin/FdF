/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:56:23 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/14 16:23:28 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"

int	pixel_to_buffer(t_pixel pixel, t_image buffer)
{
	char	*adress;
	char			*pixel_mem;
	float			x;	
	float			y;	

	pixel_mem = NULL;
	adress = mlx_get_data_addr(buffer.img_context, &buffer.bit_pixel,\
							&buffer.size_line, &buffer.endian);
	x = matrix_get_coord(pixel.coords, 0, 0);
	y = matrix_get_coord(pixel.coords, 1, 0);
	if (adress == NULL || x == NAN || y == NAN)
		return (1);
	pixel_mem = adress + (((int) y) * buffer.size_line) + (((int) x) * (buffer.bit_pixel / 8));
	ft_memcpy(pixel_mem, &pixel.color.value, sizeof(int));
	return (0);
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

int	line_to_buffer(t_pixel point_a, t_pixel point_b, t_image buffer)
{
	t_line	line;
	t_pixel	pixel;

	line = set_line_param(point_a, point_b);
	pixel = init_pixel(point_a.color, (float) line.xa, (float) line.ya);
	while (1)
	{
		pixel_to_buffer(pixel, buffer);
		if (line.xa == line.xb && line.ya == line.yb)
			break;
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

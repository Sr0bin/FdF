/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 23:17:01 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/19 23:34:06 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static	void	update_pixel_coord(t_pixel pixel, float x, float y)
{
	matrix_set_coord(pixel.coords, 0, 0, x);
	matrix_set_coord(pixel.coords, 1, 0, y);
}

static	void	update_line(t_line *line)
{
	line->er2 = 2 * line->error;
	if (line->er2 > -line->dy)
	{
		line->error -= line->dy;
		line->xa += line->sx;
	}
	if (line->er2 < line->dx)
	{
		line->error += line->dx;
		line->ya += line->sy;
	}
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
		update_line(&line);
		update_pixel_coord(pixel, (float) line.xa, (float) line.ya);
	}
	return (free_pixel(&pixel));
}

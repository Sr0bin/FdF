/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:31:47 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/20 23:36:42 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_pixel	init_pixel(t_color color, float x, float y)
{
	t_pixel	pixel;

	pixel = (const t_pixel){0};
	pixel.color = color;
	pixel.coords = create_matrix(2, 1);
	if (pixel.coords == NULL)
		return ((const t_pixel){0});
	if (x >= W_WIDTH)
		matrix_set_coord(pixel.coords, 0, 0, W_WIDTH);
	if (x < 0)
		matrix_set_coord(pixel.coords, 0, 0, 0);
	if (y >= W_HEIGHT)
		matrix_set_coord(pixel.coords, 1, 0, W_HEIGHT);
	if (y < 0)
		matrix_set_coord(pixel.coords, 1, 0, 0);
	matrix_set_coord(pixel.coords, 0, 0, x);
	matrix_set_coord(pixel.coords, 1, 0, y);
	return (pixel);
}

t_vertex	init_vertex(t_matrix coords)
{
	t_vertex	vertex;

	vertex.coords = coords;
	return (vertex);
}

t_color	init_color(t_uchar r, t_uchar g, t_uchar b, t_uchar a)
{
	t_color	color;

	color = (const t_color){0};
	color.a = a;
	color.r = r;
	color.b = b;
	color.g = g;
	return (color);
}

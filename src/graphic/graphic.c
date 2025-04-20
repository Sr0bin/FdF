/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:56:23 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/20 23:30:35 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"
#include "geometryfdf.h"
#include <math.h>

static void	bound_pixel(t_pixel *pixel, size_t x, size_t y, float value)
{
	t_color	bound_color;

	bound_color = init_color(255, 0, 0, 0);
	pixel->color = bound_color;
	matrix_set_coord(pixel->coords, x, y, value);
}

t_pixel	*clip_pixel(t_pixel *pixel)
{
	if (matrix_get_coord(pixel->coords, 0, 0) >= W_WIDTH)
		bound_pixel(pixel, 0, 0, W_WIDTH - 1);
	if (matrix_get_coord(pixel->coords, 0, 0) <= 0)
		bound_pixel(pixel, 0, 0, 0);
	if (matrix_get_coord(pixel->coords, 1, 0) >= W_HEIGHT)
		bound_pixel(pixel, 1, 0, W_HEIGHT - 1);
	if (matrix_get_coord(pixel->coords, 1, 0) <= 0)
		bound_pixel(pixel, 1, 0, 0);
	return (pixel);
}

int	free_pixel(t_pixel *pixel)
{
	free_matrix(pixel->coords);
	*pixel = (const t_pixel){0};
	return (0);
}

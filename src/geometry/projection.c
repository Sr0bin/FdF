/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:57:50 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/19 23:36:24 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:58:06 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/18 16:45:44 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*free_camera(t_camera *camera)
{
	if (camera == NULL)
		return (NULL);
	if (camera->position != NULL)
		free(camera->position);
	if (camera->rotation != NULL)
		free(camera->rotation);
	if (camera->projection != NULL)
		free(camera->projection);
	free(camera);
	return (NULL);
}
static t_camera	*init_camera_matrix(t_camera *camera)
{
	camera->position = create_matrix(3,1);
	if (camera->position == NULL)
		return (free_camera(camera));
	camera->rotation = create_matrix(3,3);
	if (camera->rotation == NULL)
		return (free_camera(camera));
	camera->projection = create_matrix(4,4);
	if (camera->projection == NULL)
		return (free_camera(camera));
	return (camera);
}

static	void	init_camera_coords(t_camera *camera)
{
	matrix_set_coord(camera->position, 0, 0, 0);
	matrix_set_coord(camera->position, 1, 0, 0);
	matrix_set_coord(camera->position, 2, 0, 0);
	matrix_set_identity(camera->rotation);
}

t_camera	*init_camera(float fov, float aspect_ratio, float near, float far)
{
	t_camera	*camera;
	float	scale;
	float	range_inv;


	camera = ft_calloc(1, sizeof(t_camera));
	if (camera == NULL)
		return (free_camera(camera));
	scale = 1.0f / (float) tan((double) (fov * 0.5F));
	if (init_camera_matrix(camera) == NULL)
		return (NULL);
	init_camera_coords(camera);
	matrix_set_coord(camera->projection, 0, 0, scale / aspect);

	return (camera);
}

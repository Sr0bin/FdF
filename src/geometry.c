/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:26:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/18 19:26:55 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_geometry	*init_geometry(int	**map)
{
	t_geometry	*geometry;

	geometry = ft_calloc(1, sizeof(t_geometry));
	if (geometry == NULL)
		return (NULL);
	geometry->col_len = 0;
	while (map[geometry->col_len] != NULL)
		geometry->col_len++;
	if (geometry->col_len > 0)
		geometry->row_len = (size_t) map[0][0];
	else
		geometry->row_len = 0;
	geometry->vertex_list = init_vertex_list(map);
	if (geometry->vertex_list == NULL)
		return (free_geometry(&geometry));
	geometry->edge_list = init_edge_list(geometry);
	if (geometry->edge_list == NULL)
		return (free_geometry(&geometry));
	geometry->center_x = (float)(geometry->row_len - 1) * 0.5F;
	geometry->center_y = (float)(geometry->col_len - 1) * 0.5F;
	geometry->scale = fminf(W_WIDTH / (float)(geometry->col_len * 2), \
			W_HEIGHT / (float)(geometry->row_len * 2));
	return (geometry);
}

void	*free_geometry(t_geometry **geometry)
{
	t_geometry	*freed;

	if (geometry == NULL || *geometry == NULL)
		return (NULL);
	freed = *geometry;
	if (freed->vertex_list != NULL)
		free_vertex_list(freed->vertex_list);
	if (freed->edge_list != NULL)
		free(freed->edge_list);
	free(freed);
	*geometry = NULL;
	return (NULL);
}

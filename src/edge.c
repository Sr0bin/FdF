/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:25:22 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/18 18:55:06 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_edge	*init_edge_list(t_geometry *geo)
{
	t_edge	*edge_list;
	size_t	vtx_i;
	size_t	edge_i;

	edge_list = ft_calloc(((geo->row_len - 1) * geo->col_len) + \
				(geo->row_len * (geo->col_len - 1)) + 1, sizeof(t_edge));
	if (edge_list == NULL)
		return (NULL);
	vtx_i = 0;
	edge_i = 0;
	while (vtx_i < geo->row_len * geo->col_len)
	{
		if (vtx_i % geo->row_len < geo->row_len - 1)
		{
			edge_list[edge_i].vtx_a = &geo->vertex_list[vtx_i];
			edge_list[edge_i++].vtx_b = &geo->vertex_list[vtx_i + 1];
		}
		if (vtx_i / geo->row_len < geo->col_len - 1)
		{
			edge_list[edge_i].vtx_a = &geo->vertex_list[vtx_i];
			edge_list[edge_i++].vtx_b = &geo->vertex_list[vtx_i + geo->row_len];
		}
		vtx_i++;
	}
	return (edge_list);
}

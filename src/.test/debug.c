/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:48:03 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/16 14:45:11 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"
#include <stdio.h>

void	print_vertex(t_vertex vertex)
{
	print_matrix(vertex.coords);
}
void	print_vertex_list(t_vertex *list)
{
	size_t	counter;
	counter = 0;
	while ((list[counter]).coords != NULL)
	{
		printf("Vertex number : %zu \n", counter);
		print_vertex(list[counter++]);
	}
}
void	print_edge_list(t_edge *list)
{
	size_t	counter;

	counter = 0;
	while (list[counter].vtx_a != NULL && list[counter].vtx_b != NULL)
	{
		printf("Edge number : %zu \n", counter);
		printf("Vertex A:\n");
		print_vertex(*list[counter].vtx_a);
		printf("Vertex B:\n");
		print_vertex(*list[counter].vtx_b);
		printf("\n");
		counter++;
	}
}

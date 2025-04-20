/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometryfdf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:31:17 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/19 22:53:10 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRYFDF_H
# define GEOMETRYFDF_H
# include "struct.h"

t_edge	*init_edge_list(t_geometry *geo);
size_t	vertex_list_len(t_vertex	*vertex_list);
t_pixel	project_vertex(t_vertex vertex, t_geometry *geometry, t_color color);
t_vertex	*init_vertex_list(int	**map);
t_vertex	init_vertex(t_matrix coords);
void	*free_vertex_list(t_vertex	*list);
t_geometry	*init_geometry(int	**map);
void	draw_geometry(t_env env, t_geometry *geometry, t_color color);
void	*free_geometry(t_geometry **geometry);
#endif

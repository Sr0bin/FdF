/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:16:18 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/16 14:45:20 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "struct.h"
/* ************************************************************************** */
/*                                                                            */
/*                               DEBUG		                                  */
/*                                                                            */
/* ************************************************************************** */
void	matrix_test(void);
void	graphic_test(void);
void	print_vertex(t_vertex vertex);
void	print_vertex_list(t_vertex *list);
void	print_edge_list(t_edge *list);
#endif

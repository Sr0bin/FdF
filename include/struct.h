/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:18:38 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/22 12:07:41 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*                      FORWARD DECLARATION									  */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_pixel		t_pixel;
typedef struct s_image		t_image;
typedef struct s_line		t_line;
typedef struct s_env		t_env;
typedef struct s_vertex		t_vertex;
typedef struct s_edge		t_edge;
typedef struct s_geometry	t_geometry;
typedef union s_color		t_color;
typedef unsigned char		t_uchar;

/* ************************************************************************** */
/*                                                                            */
/*                               DRAW		                                  */
/*                                                                            */
/* ************************************************************************** */

typedef union s_color
{
	int	value;
	struct
	{
		unsigned char	g;
		unsigned char	b;
		unsigned char	r;
		unsigned char	a;
	};
}	t_color;

typedef struct s_pixel
{
	t_color		color;
	t_matrix	coords;
}	t_pixel;

typedef struct s_line
{
	int	xa;
	int	ya;
	int	xb;
	int	yb;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	err2;
}	t_line;

typedef struct s_image
{
	void	*img_context;
	void	*img_content;
	int		bit_pixel;
	int		size_line;
	int		endian;
}	t_image;
typedef struct s_env
{
	void		*context;
	void		*window;
	t_image		image;
	t_geometry	*geometry;
}	t_env;

/* ************************************************************************** */
/*                                                                            */
/*                               GEOMETRY	                                  */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_vertex
{
	t_matrix	coords;
}	t_vertex;

typedef struct s_edge
{
	t_vertex	*vtx_a;
	t_vertex	*vtx_b;
}	t_edge;

typedef struct s_geometry
{
	t_vertex	*vertex_list;
	t_edge		*edge_list;
	size_t		row_len;
	size_t		col_len;
	float		center_x;
	float		center_y;
	float		scale;
}	t_geometry;

#endif

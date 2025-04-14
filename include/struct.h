/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:18:38 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/14 16:11:21 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "libft.h"

typedef	union	s_color
{
	int	value;
	struct
	{
		unsigned char	a;
		unsigned char	r;
		unsigned char	g;
		unsigned char	b;

	};
}	t_color;

typedef struct s_pixel
{
	t_color color;
	t_matrix coords;

} t_pixel;

typedef	struct	s_image
{

	void	*img_context;
	void	*img_content;
	int		bit_pixel;
	int		size_line;
	int		endian;
} t_image;

typedef	struct	s_line
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
	int	er2;
}	t_line;
typedef struct s_env
{
	void	*context;
	void	*window;
	t_image	image;
} t_env;
#endif

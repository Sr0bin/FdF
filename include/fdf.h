/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:18:05 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/19 23:47:27 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include "struct.h"
# include "error.h"
# include "parsing.h"
# include "graphic.h"
# include "geometryfdf.h"
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define W_WIDTH 2000
# define W_HEIGHT 1000
# define TRANSLATE 5
# define ISO_ANGLE 30
# define SCALE 10

int	clean_exit(void *env);
#endif

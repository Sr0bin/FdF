/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:18:05 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/14 17:30:18 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include "struct.h"
# include "error.h"
# define W_WIDTH 1000
# define W_HEIGHT 1000
void	free_mlx(t_env *mlx_env);
int	clean_exit(void *env);
t_env	init_env(void);
t_image	init_image(t_env env);
t_pixel	init_pixel(t_color color, float x, float y);
void	free_pixel(t_pixel *pixel);
t_color	init_color(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
int	pixel_to_buffer(t_pixel pixel, t_image buffer);
int	line_to_buffer(t_pixel point_a, t_pixel point_b, t_image buffer);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:45:43 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/18 20:28:42 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H
# include "struct.h"
void	free_mlx(t_env *mlx_env);
t_env	init_env(int	***map);
void	init_mlx_hooks(t_env mlx_env);
t_image	init_image(t_env env);
t_pixel	init_pixel(t_color color, float x, float y);
t_pixel	*clip_pixel(t_pixel *pixel);
void	update_image(t_env mlx_env);
void	color_buffer(t_color color, t_image buffer);
void	free_pixel(t_pixel *pixel);
int	key_hook(int keycode, t_env *mlx_env);
t_color	init_color(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
int	pixel_to_buffer(t_pixel pixel, t_image buffer);
int	line_to_buffer(t_pixel point_a, t_pixel point_b, t_image buffer);
#endif

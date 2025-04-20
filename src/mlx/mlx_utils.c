/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:05:53 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/19 23:39:29 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometryfdf.h"

t_env	init_env(int	***map)
{
	t_env	mlx_env;

	mlx_env = (const t_env){0};
	mlx_env.context = mlx_init();
	if (mlx_env.context == NULL)
		return ((const t_env){0});
	mlx_env.window = mlx_new_window(mlx_env.context, \
		W_WIDTH, W_HEIGHT, (char *)"Fil de Fer");
	if (mlx_env.window == NULL)
		return (free_mlx(&mlx_env));
	mlx_env.image = init_image(mlx_env);
	if (mlx_env.image.img_context == NULL)
		return (free_mlx(&mlx_env));
	mlx_env.geometry = init_geometry(*map);
	if (mlx_env.geometry == NULL)
		return (free_mlx(&mlx_env));
	free_array((void ***) map);
	return (mlx_env);
}

t_image	init_image(t_env env)
{
	t_image	image;

	image = (const t_image){0};
	image.img_context = mlx_new_image(env.context, W_WIDTH, W_HEIGHT);
	if (image.img_context == NULL)
		return ((const t_image){0});
	image.img_content = mlx_get_data_addr(image.img_context, &image.bit_pixel, \
					&image.size_line, &image.endian);
	if (image.img_content == NULL)
	{
		mlx_destroy_image(&env, image.img_context);
		return ((const t_image){0});
	}
	return (image);
}

void	update_image(t_env mlx_env)
{
	t_color	edge_color;

	edge_color = init_color(255, 255, 255, 255);
	color_buffer(init_color(0, 0, 0, 0), mlx_env.image);
	draw_geometry(mlx_env, mlx_env.geometry, edge_color);
	mlx_put_image_to_window(mlx_env.context, mlx_env.window, \
		mlx_env.image.img_context, 0, 0);
}

t_env	free_mlx(t_env *mlx_env)
{
	if (mlx_env->geometry != NULL)
		free_geometry(&mlx_env->geometry);
	if (mlx_env->image.img_context != NULL)
		mlx_destroy_image(mlx_env->context, (mlx_env->image).img_context);
	if (mlx_env->window != NULL)
		mlx_destroy_window(mlx_env->context, mlx_env->window);
	if (mlx_env->context != NULL)
	{
		mlx_destroy_display(mlx_env->context);
		free(mlx_env->context);
	}
	mlx_env->window = NULL;
	mlx_env->context = NULL;
	return ((const t_env){0});
}

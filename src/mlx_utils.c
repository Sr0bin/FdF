/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:05:53 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/18 20:32:44 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometryfdf.h"
#include <X11/keysym.h>

t_env	init_env(int	***map)
{
	t_env	mlx_env;

	mlx_env = (const t_env){0};
	mlx_env.context = mlx_init();
	if (mlx_env.context == NULL)
		return ((const t_env){0});
	mlx_env.window = mlx_new_window(mlx_env.context, W_WIDTH, W_HEIGHT, (char *)"Test window");
	if (mlx_env.window == NULL)
	{
		free_mlx(&mlx_env);
		return ((const t_env){0});
	}
	mlx_env.image = init_image(mlx_env);
	if (mlx_env.image.img_context == NULL)
	{
		free_mlx(&mlx_env);
		return ((const t_env){0});
	}
	mlx_env.geometry = init_geometry(*map);
	if (mlx_env.geometry == NULL)
	{
		free_mlx(&mlx_env);
		return ((const t_env){0});
	}
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
	mlx_put_image_to_window(mlx_env.context, mlx_env.window, mlx_env.image.img_context, 0, 0);
}
static void	key_hook_translate(int keycode, t_env *mlx_env)
{
	if (keycode == XK_Up)
		mlx_env->geometry->center_y += TRANSLATE;
	if (keycode == XK_Down)
		mlx_env->geometry->center_y -= TRANSLATE;
	if (keycode == XK_Left)
		mlx_env->geometry->center_x += TRANSLATE;
	if (keycode == XK_Right)
		mlx_env->geometry->center_x -= TRANSLATE;
}
static void	key_hook_scale(int keycode, t_env *mlx_env)
{
	if (keycode == XK_d)
		mlx_env->geometry->scale *= 2;
	if (keycode == XK_s)
		mlx_env->geometry->scale /= 2;
}

int	key_hook(int keycode, t_env *mlx_env)
{
	if (keycode == XK_Escape)
	{
		clean_exit(mlx_env);
		return (0);
	}
	key_hook_translate(keycode, mlx_env);
	key_hook_scale(keycode, mlx_env);
	update_image(*mlx_env);
	return (0);
}
void	init_mlx_hooks(t_env mlx_env)
{
	mlx_hook(mlx_env.window, 17, 0, clean_exit, &mlx_env);
	mlx_hook(mlx_env.window, 2, (1L<<0), key_hook, &mlx_env);

}
void	free_mlx(t_env *mlx_env)
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
}

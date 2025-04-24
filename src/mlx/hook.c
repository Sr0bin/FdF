/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 23:19:29 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/24 18:23:29 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/keysym.h>

static void	key_hook_translate(int keycode, t_env *mlx_env)
{
	t_geometry	*geometry;

	geometry = mlx_env->geometry;
	if (keycode == XK_Up && geometry->center_y < MAX_TRANSLATE)
		geometry->center_y += TRANSLATE;
	if (keycode == XK_Down && geometry->center_y < MAX_TRANSLATE)
		geometry->center_y -= TRANSLATE;
	if (keycode == XK_Left && geometry->center_x < MAX_TRANSLATE)
		geometry->center_x += TRANSLATE;
	if (keycode == XK_Right && geometry->center_x < MAX_TRANSLATE)
		geometry->center_x -= TRANSLATE;
}

static void	key_hook_scale(int keycode, t_env *mlx_env)
{
	t_geometry	*geometry;

	geometry = mlx_env->geometry;
	if (keycode == XK_d && geometry->scale < MAX_SCALE)
		geometry->scale *= 2;
	if (keycode == XK_s)
		geometry->scale /= 2;
}

int	clean_exit(void *env)
{
	env = (t_env *) env;
	free_mlx(env, NULL);
	exit(EXIT_SUCCESS);
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
	mlx_hook(mlx_env.window, 2, (1L << 0), key_hook, &mlx_env);
}

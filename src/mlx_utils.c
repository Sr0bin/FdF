/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:05:53 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/14 17:18:31 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	free_mlx(t_env *mlx_env)
{
	if (mlx_env->image.img_context != NULL)
		mlx_destroy_image(mlx_env->context, (mlx_env->image).img_context);
	if (mlx_env->window != NULL)
		mlx_destroy_window(mlx_env->context, mlx_env->window);
	if (mlx_env->context != NULL)
		mlx_destroy_display(mlx_env->context);
	mlx_env->window = NULL;
	mlx_env->context = NULL;
}

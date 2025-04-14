/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:16:06 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/14 17:33:00 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "geometry.h"
#include "mlx.h"


t_image	init_image(t_env env)
{
	t_image image;

	image = (const t_image){0};
	image.img_context = mlx_new_image(env.context, W_WIDTH, W_HEIGHT);
	if (image.img_context == NULL)
		return ((const t_image){0});
	image.img_content = mlx_get_data_addr(image.img_context, &image.bit_pixel,\
									   &image.size_line, &image.endian);
	if (image.img_content == NULL)
	{
		mlx_destroy_image(&env, image.img_context);
		return ((const t_image){0});
	}
	return (image);
}

t_env	init_env(void)
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
	return (mlx_env);
}

t_pixel	init_pixel(t_color color, float x, float y)
{
	t_pixel pixel;

	pixel = (const t_pixel){0};
	if (x > W_WIDTH || y > W_HEIGHT)
		return ((const t_pixel){0});
	pixel.color = color;
	pixel.coords = create_matrix(2, 0);
	if (pixel.coords == NULL)
		return ((const t_pixel){0});
	pixel.coords->index[0][0] = x;
	pixel.coords->index[1][0] = y;
	return (pixel);
}
void	free_pixel(t_pixel *pixel)
{
	free_matrix(pixel->coords);
	*pixel = (const t_pixel){ 0 };
}
t_color	init_color(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
	t_color color;

	color = (const t_color){0};
	color.a = a;
	color.r = r;
	color.b = b;
	color.g = g;
	return (color);
}
int	clean_exit(void *env)
{
	env = (t_env *) env;
	free_mlx(env);
	exit(EXIT_SUCCESS);
}
int	main(void)
{
	t_env	mlx_env;
	t_pixel	pixel;
	t_pixel	pixel2;

	mlx_env = init_env();
	if (mlx_env.context == NULL)
		return (1);
	pixel = init_pixel(init_color(255,255,255, 0), 100, 10);
	pixel2 = init_pixel(init_color(255,255,255, 0), 0, 400);
	line_to_buffer(pixel, pixel2, mlx_env.image);
	pixel.coords->index[0][0] = 0;
	line_to_buffer(pixel, pixel2, mlx_env.image);
	mlx_put_image_to_window(mlx_env.context, mlx_env.window, mlx_env.image.img_context, 0, 0);
	free_pixel(&pixel);
	free_pixel(&pixel2);
	/*free_mlx(&mlx_env);*/
	/*clean_exit(1, mlx_env);*/
	mlx_hook(mlx_env.window, 17, 0, clean_exit, &mlx_env);
	mlx_loop(mlx_env.context);
}

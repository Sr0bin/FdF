/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:16:06 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/18 20:00:54 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "fdf.h"
#include "geometryfdf.h"
#include "graphic.h"
#include "mlx.h"
#include "parsing.h"
#include <stdlib.h>

void	free_pixel(t_pixel *pixel)
{
	free_matrix(pixel->coords);
	*pixel = (const t_pixel){0};
}

int	clean_exit(void *env)
{
	env = (t_env *) env;
	free_mlx(env);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_env	mlx_env;
	int	**map_array;


	(void) argc;
	/*(void) argv;*/
	map_array = array_populate(argv[1]);
	if (map_array == NULL)
		return (1);
	//TODO: Check
	mlx_env = init_env(&map_array);
	if (mlx_env.context == NULL)
		return (EXIT_FAILURE);
	/*print_edge_list(mlx_env.geometry->edge_list);*/
	/*edge_color = init_color(255, 255, 255, 255);*/
	/*draw_geometry(mlx_env, mlx_env.geometry, edge_color);*/
	/*mlx_put_image_to_window(mlx_env.context, mlx_env.window, mlx_env.image.img_context, 0, 0);*/
	update_image(mlx_env);
	init_mlx_hooks(mlx_env);
	/*mlx_hook(mlx_env.window, 17, 0, clean_exit, &mlx_env);*/
	mlx_loop(mlx_env.context);
	/*print_edge_list(geometry->edge_list);*/
	/*list = init_vertex_list(map_array);*/
	/*print_vertex_list(list);*/
	/*free_vertex_list(list);*/

	/*graphic_test();*/

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:16:06 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/20 20:53:02 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "fdf.h"
#include "geometryfdf.h"
#include "graphic.h"
#include "mlx.h"
#include "parsing.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_env	mlx_env;
	int		**map_array;

	(void) argc;
	if (argc != 2)
		return (EXIT_FAILURE);
	map_array = array_populate(argv[1]);
	if (map_array == NULL)
		return (1);
	mlx_env = init_env(&map_array);
	if (mlx_env.context == NULL)
		return (EXIT_FAILURE);
	update_image(mlx_env);
	init_mlx_hooks(mlx_env);
	mlx_loop(mlx_env.context);
}

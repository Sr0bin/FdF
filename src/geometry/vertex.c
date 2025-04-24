/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:45:40 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/21 19:25:14 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	map_size(int **map)
{
	size_t	i;
	size_t	counter;
	int		*temp;

	i = 0;
	counter = 0;
	temp = *map;
	while (temp != NULL)
	{
		i += (size_t) temp[0];
		temp = map[counter++];
	}
	return (i);
}

static	void	*add_vertex_line(int *array, int depth, t_vertex *list)
{
	int			i;
	t_matrix	coords;
	size_t		counter;

	i = 1;
	counter = 0;
	while (i < array[0] + 1)
	{
		coords = create_matrix(3, 1);
		if (coords == NULL)
			return (NULL);
		coords->index[0][0] = (float) i;
		coords->index[1][0] = (float) depth;
		coords->index[2][0] = (float) array[i];
		list[counter++] = init_vertex(coords);
		i++;
	}
	return (list);
}

void	*free_vertex_list(t_vertex	*list)
{
	size_t	counter;

	counter = 0;
	if (list == NULL)
		return (NULL);
	while (list[counter].coords != NULL)
	{
		free_matrix((list[counter].coords));
		counter++;
	}
	free(list);
	return (NULL);
}

size_t	vertex_list_len(t_vertex	*vertex_list)
{
	size_t	counter;

	counter = 0;
	if (vertex_list == NULL)
		return (0);
	while ((vertex_list[counter]).coords != NULL)
		counter++;
	return (counter);
}

t_vertex	*init_vertex_list(int	**map)
{
	t_vertex	*vertex_list;
	t_vertex	*temp_list;
	int			i;
	int			counter;

	i = 0;
	counter = 0;
	vertex_list = ft_calloc(map_size(map) + 1, sizeof(t_vertex));
	if (vertex_list == NULL)
		return (NULL);
	while (map[i] != NULL)
	{
		temp_list = add_vertex_line(map[i], i, &vertex_list[counter]);
		if (temp_list == NULL)
			return (free_vertex_list(vertex_list));
		counter += map[i][0];
		i++;
	}
	return (vertex_list);
}

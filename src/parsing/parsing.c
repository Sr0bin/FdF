/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:29:44 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/24 20:53:29 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	**array_valid(int **map)
{
	size_t	counter;
	size_t	temp;
	int		j;

	counter = 0;
	while (map[counter] != NULL)
	{
		temp = counter;
		j = map[counter][0];
		while (map[temp] != NULL)
		{
			if (map[temp][0] != j)
				return (NULL);
			temp++;
		}
		counter++;
	}
	return (map);
}

static char	*remove_nl(char *line)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

static	void	*free_close_array(int **array, int fd)
{
	if (fd != -1)
		close(fd);
	if (array != NULL)
		return (free_array((void ***) &array));
	return (NULL);
}

static int	**array_loop(int **array, int fd)
{
	char	*line;
	size_t	counter;

	counter = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = remove_nl(line);
		array[counter++] = array_init(line);
		free(line);
		if (array[counter - 1] == NULL)
			return (free_close_array(array, fd));
		line = get_next_line(fd);
	}
	close(fd);
	return (array);
}

int	**array_populate(const char *path)
{
	int		**array;
	int		fd;

	if (line_count(path) == -1)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	array = ft_calloc((size_t) line_count(path) + 1, sizeof(*array));
	if (array == NULL)
		return (free_close_array(NULL, fd));
	array = array_loop(array, fd);
	if (array != NULL && array_valid(array) != NULL)
		return (array);
	return (free_array((void ***) &array));
}

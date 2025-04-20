/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:29:44 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/21 00:43:11 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	size_t	contain_forbidden_c(char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter] != '\0')
	{
		if (!ft_issign(str[counter]) && !ft_isdigit(str[counter]) \
			&& !ft_iswhitespace(str[counter]))
		{
			return (1);
		}
		counter++;
	}
	return (0);
}

static int	line_count(const char *path)
{
	int		line_count;
	int		fd;
	char	*line;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (line != NULL && contain_forbidden_c(line))
		{
			free(line);
			return (-1);
		}
		line_count++;
	}
	close(fd);
	return (line_count);
}

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

int	**array_populate(const char *path)
{
	int		**array;
	int		fd;
	int		counter;
	char	*line;

	counter = 0;
	if (line_count(path) == -1)
		return (NULL);
	fd = open(path, O_RDONLY);
	array = ft_calloc((size_t) line_count(path) + 1, sizeof(*array));
	if (array == NULL)
		return (NULL);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		array[counter++] = array_init(line);
		free(line);
		line = get_next_line(fd);
	}
	if (array_valid(array) != NULL)
		return (array);
	return (free_array((void ***) &array));
}

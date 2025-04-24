/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:34:29 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/24 20:35:41 by rorollin         ###   ########.fr       */
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

static	int	free_line(char	*line, int fd)
{
	free(line);
	close(fd);
	return (-1);
}

int	line_count(const char *path)
{
	int		line_count;
	int		fd;
	char	*line;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	if (line != NULL && contain_forbidden_c(line))
		return (free_line(line, fd));
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (line != NULL && contain_forbidden_c(line))
			return (free_line(line, fd));
		line_count++;
	}
	close(fd);
	return (line_count);
}

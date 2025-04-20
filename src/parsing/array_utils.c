/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:44:47 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/21 00:20:58 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	array_length(void **array)
{
	size_t	size;

	size = 0;
	if (array == NULL)
		return (0);
	while (array[size] != NULL)
		size++;
	return (size);
}

void	*free_array(void ***array)
{
	size_t	counter;

	counter = 0;
	if (array == NULL || *array == NULL)
		return (NULL);
	while ((*array)[counter] != NULL)
		free((*array)[counter++]);
	free((*array)[counter]);
	free((void *) *array);
	*array = NULL;
	return (NULL);
}

int	*array_init(char *str)
{
	int			*array;
	char		**nmbrs;
	size_t		len;
	long long	temp;

	nmbrs = ft_split(str, ' ');
	if (nmbrs == NULL)
		return (free_array((void ***) &nmbrs));
	len = array_length((void **) nmbrs);
	array = ft_calloc(sizeof(*array), len + 1);
	if (array == NULL)
		return (free_array((void ***) &nmbrs));
	array[0] = (int) len;
	while (len != 0)
	{
		temp = ft_atol(nmbrs[len - 1]);
		if (temp > INT_MAX || temp < INT_MIN)
		{
			free(array);
			return (free_array((void ***) &nmbrs));
		}
		array[len--] = (int) temp;
	}
	free_array((void ***) &nmbrs);
	return (array);
}

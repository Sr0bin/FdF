/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:44:47 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/18 21:43:41 by rorollin         ###   ########.fr       */
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
	free((void *) *array);
	*array = NULL;
	return (NULL);
}

static void	free_p(void **p)
{
	free(*p);
	p = NULL;
}

int	*array_init(char *str)
{
	int			*array;
	char		**nmbrs;
	size_t		len;
	long long	temp;

	nmbrs = ft_split(str, ' ');
	if (nmbrs == NULL)
		return (NULL);
	len = array_length((void **) nmbrs);
	if (len == 0)
		return (free_array((void ***) &nmbrs));
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

int	*array_join(int	**ar1, int **ar2)
{
	int	i;
	int	*new_array;

	i = 1;
	new_array = ft_calloc(sizeof(**ar1), (size_t)((*ar1)[0] + (*ar2)[0] + 1));
	if (new_array == NULL)
	{
		free(*ar2);
		return (NULL);
	}
	new_array[0] = (*ar1)[0] + (*ar2)[0];
	while (i < (*ar1)[0] + 1)
	{
		new_array[i] = (*ar1)[i];
		i++;
	}
	while (i < (*ar1)[0] + (*ar2)[0] + 1)
	{
		new_array[i] = (*ar2)[i - (*ar1)[0]];
		i++;
	}
	free_p((void **)ar1);
	free_p((void **)ar2);
	return (new_array);
}

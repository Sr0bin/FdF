/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:41:34 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/18 21:43:03 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "struct.h"

int	*array_init(char *str);
int	*array_join(int	**ar1, int **ar2);
int	**array_populate(const char *path);
int	line_count(const char *path);
void	*free_array(void ***array);
#endif

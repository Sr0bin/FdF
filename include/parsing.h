/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:41:34 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/24 20:35:50 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "struct.h"

/* ************************************************************************** */
/*                               ARRAY		                                  */
/* ************************************************************************** */

int		*array_init(char *str);
int		**array_populate(const char *path);
void	*free_array(void ***array);
int		line_count(const char *path);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:58:58 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/20 23:36:51 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color_buffer(t_color color, t_image buffer)
{
	size_t	counter;

	counter = 0;
	while (counter < W_WIDTH * W_HEIGHT)
	{
		ft_memcpy(&(((int *)(buffer.img_content))[counter++]), \
			&color.value, sizeof(int));
	}
}

int	pixel_to_buffer(t_pixel pixel, t_image buffer)
{
	char	*adress;
	char	*pixel_mem;
	float	x;	
	float	y;	

	pixel_mem = NULL;
	adress = mlx_get_data_addr(buffer.img_context, &buffer.bit_pixel, \
							&buffer.size_line, &buffer.endian);
	clip_pixel(&pixel);
	x = matrix_get_coord(pixel.coords, 0, 0);
	y = matrix_get_coord(pixel.coords, 1, 0);
	if (adress == NULL || isnan(x) || isnan(y))
		return (1);
	pixel_mem = adress + (((int) y) * buffer.size_line) + \
		(((int) x) * (buffer.bit_pixel / 8));
	ft_memcpy(pixel_mem, &pixel.color.value, sizeof(int));
	return (0);
}

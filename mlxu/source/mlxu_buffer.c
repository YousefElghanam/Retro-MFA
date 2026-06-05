/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxu_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:28:17 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/05 20:51:01 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx_utils.h"

void	mlxu_pixel_put_buffer(t_mlxu *env, int x, int y, int color)
{
	char	*pixel;
	
	if (x < 0 || y < 0
		|| x >= env->active.img->size.x || y >= env->active.img->size.y)
		return ;
	pixel = env->active.img->mem;
	pixel += env->active.img->offset.x * x;
	pixel += env->active.img->offset.y * y;
	*(int *) pixel = color;
}

int		mlxu_pixel_get_buffer(t_mlxu_img *buffer, int x, int y)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= buffer->size.x || y >= buffer->size.y)
		return (0);
	pixel = buffer->mem;
	pixel += buffer->offset.y * y;
	pixel += buffer->offset.x * x;
	return (*(int *) pixel);
}

void	mlxu_flush_buffer(t_mlxu *env)
{
	mlx_put_image_to_window(\
		env->mlx_ptr, \
		env->active.win->ptr, \
		env->active.img->ptr, \
		0, 0);
	if (env->active.img == &env->active.win->buffer_1)
		env->active.img = &env->active.win->buffer_2;
	else
		env->active.img = &env->active.win->buffer_1;
}

void	mlxu_clear_buffer(t_mlxu_img *buffer)
{
	size_t	total_bytes;

	total_bytes = buffer->bytes_line * buffer->size.y;
	bzero(buffer->mem, total_bytes);
}

// OLD VERSION
// void	mlxu_clear_buffer(t_mlxu *env)
// {
// 	t_mlxu_2d	c;

	
// 	c.x = 0;
// 	while (c.x < env->active.win->size.x)
// 	{
// 		c.y = 0;
// 		while (c.y < env->active.win->size.y)
// 			mlxu_pixel_put_buffer(env, c, BLACK);
// 		{
// 			c.y++;
// 		}
// 		c.x++;
// 	}
// }

/*
	SOME NOTES FOR LATER TIME
	when resetting whole image
		maybe a comparison is faster than overwriting every pixel in mem?
		if new col != stored col then put the pixel there
		=> whats definitely faster is zeroing the whole memoryspace
		interesting for bonus part
*/

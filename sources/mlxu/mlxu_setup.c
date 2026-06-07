/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxu_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:11:09 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/07 04:07:18 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

/*
	the whole idea is to have:
		- multiple winows per single display
		- two images buffers per single window
*/

static void	mlxu_setup_buffer_offset(t_mlxu_img *buffer)
{
	buffer->offset.x = (buffer->bits_pixel / BYTE);
	buffer->offset.y = buffer->bytes_line;
}

static int	mlxu_setup_double_buffer(t_mlxu *env)
{
	t_mlxu_win	*win;

	win = env->active.win;
	win->buffer_1.ptr = mlx_new_image(env->mlx_ptr, win->size.x, win->size.y);
	win->buffer_2.ptr = mlx_new_image(env->mlx_ptr, win->size.x, win->size.y);
	if (!win->buffer_1.ptr || !win->buffer_2.ptr)
		return (mlxu_terminate(env, ERR_MLX_IMG));
	win->buffer_1.mem = mlx_get_data_addr(\
							win->buffer_1.ptr, \
							&win->buffer_1.bits_pixel, \
							&win->buffer_1.bytes_line, \
							&win->buffer_1.endian);
	win->buffer_2.mem = mlx_get_data_addr(\
							win->buffer_2.ptr, \
							&win->buffer_2.bits_pixel, \
							&win->buffer_2.bytes_line, \
							&win->buffer_2.endian);
	if (!win->buffer_1.mem || !win->buffer_2.mem)
		return (mlxu_terminate(env, ERR_MLX_IMG));
	mlxu_setup_buffer_offset(&win->buffer_1);
	mlxu_setup_buffer_offset(&win->buffer_2);
	win->buffer_1.size = win->size; // NEW needs validation if it works
	win->buffer_2.size = win->size; // NEW needs validation if it works
	return (0);
}

int mlxu_setup_new_buffer(t_mlxu *env)
{
	t_mlxu_img	*img;
	t_list_dl	*node;

	if (!env->mlx_ptr)
		return (mlxu_terminate(env, ERR_MLX_PTR));
	img = calloc(1, sizeof (t_mlxu_img));
	if (!img)
		return (mlxu_terminate(env, ERR_MLX_IMG));
	img->ptr = mlx_new_image(env->mlx_ptr,
		env->active.win->size.x, env->active.win->size.y);
	if (!img)
		return (mlxu_terminate(env, ERR_MLX_IMG));
	img->mem = mlx_get_data_addr(\
				img->ptr, \
				&img->bits_pixel, \
				&img->bytes_line, \
				&img->endian);
	if (!img->mem)
		return (mlxu_terminate(env, ERR_MLX_IMG));
	node = lstnew_cdl(img);
	if (!node)
		return (mlxu_terminate(env, ERR_MLX_IMG));
	mlxu_setup_buffer_offset(img);
	img->size = env->active.win->size;
	img->mlx_ptr = env->mlx_ptr;
	env->active.img = img;
	lstadd_back_cdl(&env->images, node);
	return (0);
}

int	mlxu_setup_new_win(t_mlxu *env, char *title, t_mlxu_2d size)
{
	t_list		*node;
	t_mlxu_win	*window;
	int			ret;

	if (!env->mlx_ptr)
		return (mlxu_terminate(env, ERR_MLX_PTR));
	window = calloc(1, sizeof (t_mlxu_win));
	if (!window)
		return (mlxu_terminate(env, ERR_MEM_WIN));
	node = ft_lstnew(window);
	if (!node)
		return (mlxu_terminate(env, ERR_MEM_WIN));
	ft_lstadd_back(&env->windows, node);
	window->ptr = mlx_new_window(env->mlx_ptr, size.x, size.y, title);
	if (!window->ptr)
		return (mlxu_terminate(env, ERR_MLX_WIN));
	window->size.x = size.x;
	window->size.y = size.y;
	window->title = title;
	window->mlx_ptr = env->mlx_ptr;
	env->active.win = window;
	ret = mlxu_setup_double_buffer(env);
	env->active.img = &window->buffer_1;
	return (ret);
}

int	mlxu_setup_new_display(t_mlxu *env)
{
	if (!env->mlx_ptr)
		env->mlx_ptr = mlx_init();
	if (!env->mlx_ptr)
		return (mlxu_terminate(env, ERR_MLX_INI));
	mlx_get_screen_size(env->mlx_ptr, &env->dsp_size.x, &env->dsp_size.y);
	return (0);
}

/*	DOES NOTHING - CAMPUS MLX ALSO DOESN'T RETURN ANYTHING
int	mlxu_setup_new_display(t_mlxu *env)
{
	int	err;

	if (!env->mlx_ptr)
		env->mlx_ptr = mlx_init();
	if (!env->mlx_ptr)
		return (mlxu_terminate(env, ERR_MLX_INI));
	err = 0;
	err = mlx_get_screen_size(env->mlx_ptr, &env->dsp_size.x, &env->dsp_size.y);
	if (err != 0)
		return (mlxu_terminate(env, ERR_MLX_INI));
	return (0);
}
*/

int	mlxu_create_buffer_from_xpm(t_mlxu *env, t_mlxu_img *buffer, char *path)
{
	if (!env || !env->mlx_ptr || !buffer || !path)
		return (mlxu_terminate(env, ERR_XPM_ARG));
	buffer->ptr = mlx_xpm_file_to_image(\
		env->mlx_ptr, \
		path, \
		&buffer->size.x, \
		&buffer->size.y);
	if (!buffer->ptr)
		return (mlxu_terminate(env, ERR_MLX_XPM));
	buffer->mem = mlx_get_data_addr(\
		buffer->ptr, \
		&buffer->bits_pixel, \
		&buffer->bytes_line, \
		&buffer->endian);
	if (!buffer->mem)
		return (mlxu_terminate(env, ERR_MLX_GDA));
	mlxu_setup_buffer_offset(buffer);
	return (0);
}

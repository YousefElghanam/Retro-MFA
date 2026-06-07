/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxu_terminate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:11:40 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/07 03:26:11 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

static void	mlxu_clear_window(void *window)
{
	t_mlxu_win	*content;

	content = window;
	if (content)
	{
		if (content->buffer_1.ptr)
			mlx_destroy_image(content->mlx_ptr, content->buffer_1.ptr);
		if (content->buffer_2.ptr)
			mlx_destroy_image(content->mlx_ptr, content->buffer_2.ptr);
		if (content->ptr)
			mlx_destroy_window(content->mlx_ptr, content->ptr);
		free(content);
	}
	content = NULL;
}

static void	mlxu_terminate_windows(t_mlxu *env)
{
	if (env->windows)
		ft_lstclear(&env->windows, mlxu_clear_window);
	env->active.img = NULL;
}

static void mlxu_clear_image(void *image)
{
	t_mlxu_img	*content;

	content = image;
	if (content)
		mlx_destroy_image(content->mlx_ptr, content->ptr);
	content = NULL;
}

static void mlxu_terminate_images(t_mlxu *env)
{
	if (env->images)
		lstclear_cdl(&env->images, mlxu_clear_image);
	env->active.img = NULL;
}

int	mlxu_terminate(t_mlxu *env, char *msg)
{
	int	err;

	if (msg)
		err = dprintf(STDERR_FILENO, "%s\n", msg);
	else
		err = 0;
	if (!env || !env->mlx_ptr)
		return (err);
	if (env->windows)
		mlxu_terminate_windows(env);
	if (env->images)
		mlxu_terminate_images(env);
	mlx_destroy_display(env->mlx_ptr);
	free(env->mlx_ptr);
	env->mlx_ptr = NULL;
	return (err);
}

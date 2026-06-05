/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:33:50 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/05 20:56:09 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx_utils.h"

/*
	Deletes the node LST by freeing its content with DEL
	and then freeing the node itself.
*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
		del(lst->content);
	lst->next = NULL;
	free(lst);
}

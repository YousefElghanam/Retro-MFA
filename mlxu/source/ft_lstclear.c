/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:41:43 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/05 20:54:28 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx_utils.h"

/*
	Deletes and frees current and all successor nodes of LST
	using DEL for the content and setting the head pointer to NULL.
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		next = (**lst).next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
	*lst = NULL;
}

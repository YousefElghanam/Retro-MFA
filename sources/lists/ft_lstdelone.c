/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:33:50 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/07 02:56:03 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

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

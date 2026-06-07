/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_cdl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:11:16 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/07 02:55:31 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

// delete and free content of a NODE using DEL, setting next&prev to NULL
void	lstdelone_cdl(t_list_dl *node, void (*del)(void *))
{
	if (node && del)
		del(node->content);
	node->next = NULL;
	node->prev = NULL;
	free(node);
}

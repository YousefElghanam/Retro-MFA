/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_cdl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:11:53 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/07 02:55:31 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

// iterate through list HEAD, clear and free each node, set HEAD to NULL
void	lstclear_cdl(t_list_dl **head, void (*del)(void *))
{
	t_list_dl	*node;
	t_list_dl	*next;

	if (!head || !del)
		return ;
	node = *head;
	while (node)
	{
		next = node->next;
		lstdelone_cdl(node, del);
		node = next;
		if (node == *head)
			break ;
	}
	*head = NULL;
}

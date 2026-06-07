/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listadd_back_cdl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:06:36 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/07 02:55:31 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

// add NEW node at the back of circular doubly linked list HEAD
void	lstadd_back_cdl(t_list_dl **head, t_list_dl *new)
{
	if (!new || !head)
		return ;
	if (!*head)
	{
		*head = new;
		(*head)->next = new;
		(*head)->prev = new;
		return ;
	}
	new->next = *head;
	new->prev = (*head)->prev;
	new->prev->next = new;
	(*head)->prev = new;
}

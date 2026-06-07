/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:50:09 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/07 02:56:03 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lists.h"

/*
	Returns the last node of the list or NULL if the list is empty.
*/

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

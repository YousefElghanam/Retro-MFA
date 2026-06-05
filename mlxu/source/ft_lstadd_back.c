/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mweghofe <mweghofe@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:19:13 by mweghofe          #+#    #+#             */
/*   Updated: 2026/06/05 20:54:23 by mweghofe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx_utils.h"

/*
	Adds the node NEW at the end of the list LST.
	beware the gentle difference:
	the **lst pointer in the argument changes the head when it is empty
	not to add the new node
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*append;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	append = ft_lstlast(*lst);
	append->next = new;
}

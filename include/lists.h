#ifndef LISTS_H
# define LISTS_H

#include <stdlib.h>

// structure for singly linked list with pointers for CONTENT and NEXT
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// structure for doubly linked list with pointers for CONTENT, NEXT and PREVIOUS
typedef struct s_list_dl
{
	struct s_list_dl	*next;
	struct s_list_dl	*prev;
	void				*content;
}	t_list_dl;

// Initializes .content with CONTENT and .next with NULL.
t_list		*ft_lstnew(void *content);
// Returns the last node of LST
t_list		*ft_lstlast(t_list *lst);
// Adds the node NEW at the end of LST.
void		ft_lstadd_back(t_list **lst, t_list *new);
// Deletes .content of node LST with function DEL and frees the node itself.
void		ft_lstdelone(t_list *lst, void (*del)(void *));
// Deletes and frees the given node LST and all successors.
// Uses DEL to clear .content. 
void		ft_lstclear(t_list **lst, void (*del)(void *));

// create new node with given CONTENT
t_list_dl	*lstnew_cdl(void *content);
// add NEW node at the front of circular doubly linked list HEAD
void		lstadd_front_cdl(t_list_dl **head, t_list_dl *new);
// add NEW node at the back of circular doubly linked list HEAD
void		lstadd_back_cdl(t_list_dl **head, t_list_dl *new);
// delete and free content of a NODE using DEL, setting next&prev to NULL
void		lstdelone_cdl(t_list_dl *node, void (*del)(void *));
// iterate through list HEAD, clear and free each node, set HEAD to NULL
void		lstclear_cdl(t_list_dl **head, void (*del)(void *));

#endif
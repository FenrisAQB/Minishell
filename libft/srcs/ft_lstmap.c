/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:55:12 by cdorig            #+#    #+#             */
/*   Updated: 2024/11/05 15:48:31 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_item;
	t_list	*new_lst;
	void	*new_content;

	if (!lst || !f || !del)
		return (0);
	new_lst = 0;
	while (lst)
	{
		new_content = f(lst->content);
		new_item = ft_lstnew(new_content);
		if (!new_item)
		{
			del(new_content);
			ft_lstclear(&new_lst, del);
			return (0);
		}
		ft_lstadd_back(&new_lst, new_item);
		lst = lst->next;
	}
	return (new_lst);
}

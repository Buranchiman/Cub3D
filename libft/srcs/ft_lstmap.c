/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:06:46 by wivallee          #+#    #+#             */
/*   Updated: 2024/11/14 15:09:12 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp1;
	t_list	*tmp2;

	if (lst == NULL)
		return (NULL);
	tmp1 = lst;
	new = ft_lstnew(f(tmp1->content));
	if (new == NULL)
		return (NULL);
	tmp1 = tmp1->next;
	while (tmp1 != NULL)
	{
		tmp2 = ft_lstnew(f(tmp1->content));
		if (tmp2 == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, tmp2);
		tmp1 = tmp1->next;
	}
	return (new);
}

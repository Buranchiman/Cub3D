/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:53:14 by wivallee          #+#    #+#             */
/*   Updated: 2024/11/08 15:26:36 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*point;

	if (lst != NULL)
	{
		while (*lst != NULL)
		{
			point = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = point;
		}
	}
}

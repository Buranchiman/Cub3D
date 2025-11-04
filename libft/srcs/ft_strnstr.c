/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:12:03 by wivallee          #+#    #+#             */
/*   Updated: 2024/11/12 13:59:15 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	j = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			while (big[i + j] == little[j] && big[i + j] && little[j]
				&& i + j < len)
				j++;
			if (little[j] == '\0')
				return (&((char *)big)[i]);
			else
				j = 0;
		}
		i++;
	}
	return (NULL);
}

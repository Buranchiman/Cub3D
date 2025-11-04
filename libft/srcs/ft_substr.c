/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:10:47 by wivallee          #+#    #+#             */
/*   Updated: 2024/11/14 15:17:35 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_calc(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	if (start >= ft_strlen(s))
		return (0);
	else if (i - start < len)
		return (i - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*ret;
	size_t			size;

	if (s == NULL)
		return (NULL);
	size = len_calc(s, start, len);
	ret = ft_calloc(size + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = s[start + i];
		i++;
	}
	return (ret);
}

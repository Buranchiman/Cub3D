/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:04:05 by wivallee          #+#    #+#             */
/*   Updated: 2024/11/08 16:31:49 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	destlen;
	size_t	i;

	if (dst == NULL && siz == 0)
		return (0);
	destlen = ft_strlen(dst);
	i = 0;
	while (i + destlen + 1 < siz && src[i])
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	if (destlen < siz)
		return (ft_strlen(src) + destlen);
	else
		return (ft_strlen(src) + siz);
}

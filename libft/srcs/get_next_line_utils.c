/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:15:50 by wivallee          #+#    #+#             */
/*   Updated: 2025/01/14 15:41:20 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_clean_clear(char *ret, char *line)
{
	if (ret)
		free(ret);
	if (line)
		ft_bzero(line, ft_strlen(line));
}

int	ft_strindex(const char *s, int c)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (((unsigned char *)s)[i] == (unsigned char)c)
				return (i);
			i++;
		}
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (i);
	}
	return (-1);
}

static char	*malloc_error(char const **s1)
{
	if (*s1)
		free((char *)*s1);
	return (NULL);
}

char	*ft_strjoinfree(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*cat;

	cat = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (cat == NULL)
		return (malloc_error(&s1));
	ft_bzero(cat, ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	while (s1 && s1[i])
	{
		cat[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		cat[i + j] = s2[j];
		j++;
	}
	if (s1)
		free((char *)s1);
	return (cat);
}

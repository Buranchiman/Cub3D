/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillyd <chillyd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:32:36 by wivallee          #+#    #+#             */
/*   Updated: 2025/01/13 11:40:18 by chillyd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_len(const char *s, char c, unsigned int index)
{
	unsigned int	i;

	i = index;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i - index);
}

void	ft_clear_tab(char **tab)
{
	unsigned int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

static int	ft_word_count(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_get_word(const char *s, char c, unsigned int number)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i] && count < number)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c && count < number)
			i++;
	}
	return (ft_substr(s, i, ft_word_len(s, c, i)));
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	j;
	unsigned int	words;

	if (s == NULL)
		return (NULL);
	words = ft_word_count(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (tab == NULL)
		return (NULL);
	j = 0;
	while (j < words)
	{
		tab[j] = ft_get_word(s, c, j + 1);
		if (tab[j] == NULL)
		{
			ft_clear_tab(tab);
			return (NULL);
		}
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

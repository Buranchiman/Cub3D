/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:57:36 by wivallee          #+#    #+#             */
/*   Updated: 2024/12/11 14:12:16 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	if (siz == 0)
		return (len);
	i = 0;
	while (i + 1 < siz && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

char	*ft_subfree(char const*s, unsigned int start, size_t len, char *mem)
{
	size_t			i;
	char			*ret;
	size_t			size;

	if (s == NULL)
		return (NULL);
	size = len;
	if (start >= ft_strlen(s))
		size = 0;
	else if (ft_strlen(s) - start < len)
		size = ft_strlen(s) - start;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, size + 1);
	i = 0;
	while (i < size)
	{
		ret[i] = s[start + i];
		i++;
	}
	if (mem)
		free(mem);
	return (ret);
}

char	*ft_reading(int fd, char *dest)
{
	char		*tmp;
	ssize_t		bytes_read;

	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (tmp == NULL)
		return (NULL);
	bytes_read = 1;
	while (ft_strindex(dest, '\n') == -1)
	{
		ft_bzero(tmp, BUFFER_SIZE + 1);
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
		{
			free(dest);
			free(tmp);
			return (NULL);
		}
		dest = ft_strjoinfree(dest, tmp);
		if (dest == NULL)
			return (NULL);
	}
	free(tmp);
	return (dest);
}

int	ft_cut_line(char **ret, char *line)
{
	unsigned int	i;

	if (ft_strlen(line) > 0)
	{
		i = 0;
		while (line[i] && line[i] != '\n')
			i++;
		*ret = ft_subfree(line, 0, i + 1, *ret);
		if (*ret == NULL)
			return (1);
		if (line[i])
			ft_strlcpy(line, &line[i + 1], ft_strlen(line));
		else
			ft_bzero(line, ft_strlen(line));
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	line[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*ret;

	if (fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	ret = NULL;
	ft_cut_line(&ret, line[fd]);
	if (ft_strindex(ret, '\n') != -1)
	{
		return (ret);
	}
	ret = ft_reading(fd, ret);
	if (ret == NULL)
		return (NULL);
	if (ft_strindex(ret, '\n') != -1)
	{
		ft_strlcpy(line[fd], &ret[ft_strindex(ret, '\n') + 1], ft_strlen(ret));
		ret = ft_subfree(ret, 0, ft_strindex(ret, '\n') + 1, ret);
		if (ret == NULL)
			return (NULL);
	}
	return (ret);
}

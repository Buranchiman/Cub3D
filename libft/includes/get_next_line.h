/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chillyd <chillyd@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:01:22 by wivallee          #+#    #+#             */
/*   Updated: 2024/12/16 15:41:06 by chillyd          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "ultralibft.h"

void			ft_clean_clear(char *ret, char *line);
int				ft_strindex(const char *s, int c);
char			*ft_strjoinfree(char const *s1, char const *s2);
char			*ft_subfree(char const*s, unsigned int start,
					size_t len, char *mem);
char			*get_next_line(int fd);

#endif
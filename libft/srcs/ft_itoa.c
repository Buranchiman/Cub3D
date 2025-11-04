/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:19:33 by wivallee          #+#    #+#             */
/*   Updated: 2024/11/14 14:41:51 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tabbing(int signe, unsigned int power, unsigned int holder,
	unsigned int size)
{
	char			*ret;
	unsigned int	i;

	ret = ft_calloc(size + 1, sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	if (signe < 0)
	{
		ret[0] = '-';
		i = 1;
	}
	while (i < size)
	{
		ret[i] = (holder / power) + '0';
		holder = holder % power;
		power = power / 10;
		i++;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	unsigned int	power;
	unsigned int	holder;
	unsigned int	size;
	int				signe;

	size = 1;
	power = 1;
	signe = 1;
	if (n < 0)
	{
		size++;
		holder = -n;
		signe = -signe;
	}
	else
		holder = n;
	while (power <= holder / 10)
	{
		power = power * 10;
		size++;
	}
	return (ft_tabbing(signe, power, holder, size));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wivallee <wivallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:10:28 by wivallee          #+#    #+#             */
/*   Updated: 2025/01/14 15:56:22 by wivallee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "ultralibft.h"

int	ft_putstr_fdlen(const char *s, int fd);
int	ft_putnbr_base(unsigned long nbr, char *base, int sign, int fd);
int	ft_print_hexa(unsigned int nb, char c, int fd);
int	ft_print_add(unsigned long add, int fd);
int	ft_print_number(int nb, int fd);
int	ft_printf(int fd, const char *format, ...);

#endif

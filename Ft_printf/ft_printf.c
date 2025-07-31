/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:09:24 by jaeklee           #+#    #+#             */
/*   Updated: 2025/05/20 15:23:21 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(va_list args, char format)
{
	int	p_len;

	p_len = 0;
	if (format == 'c')
		p_len += ft_printchar(va_arg(args, int));
	else if (format == 's')
		p_len += ft_printstr(va_arg(args, char *));
	else if (format == '%')
		p_len += ft_printpercent();
	else if (format == 'p')
		p_len += ft_printptr(va_arg(args, unsigned long));
	else if (format == 'd' || format == 'i')
		p_len += ft_printnbr(va_arg(args, int));
	else if (format == 'u')
		p_len += ft_printunnbr(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		p_len += ft_printhex(va_arg(args, unsigned int), format);
	else
		p_len += write(1, &format, 1);
	if (p_len == -1)
		return (-1);
	return (p_len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		p_len;
	int		check;

	va_start(args, str);
	i = 0;
	p_len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '\0')
			check = ft_format(args, str[++i]);
		else
			check = write(1, &str[i], 1);
		if (check == -1)
		{
			va_end(args);
			return (-1);
		}
		p_len = p_len + check;
		i++;
	}
	va_end(args);
	return (p_len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:10:04 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/31 15:15:16 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		i++;
		n = n / 16;
	}
	return (i);
}

char	*ft_hexchar(unsigned int n, const char scale)
{
	int				len;
	unsigned int	num;
	char			*tmp;
	char			*hexchar;

	num = n;
	if (scale == 'x')
		hexchar = "0123456789abcdef";
	else if (scale == 'X')
		hexchar = "0123456789ABCDEF";
	if (num == 0)
		return (ft_strdup("0"));
	len = ft_hexlen(n);
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	tmp[len] = '\0';
	while (len > 0)
	{
		len --;
		tmp[len] = hexchar[num % 16];
		num = num / 16;
	}
	return (tmp);
}

int	ft_printhex(unsigned int n, const char scale)
{
	char	*hexchar;
	int		i;
	int		len;

	i = 0;
	hexchar = ft_hexchar(n, scale);
	if (!hexchar)
		return (0);
	len = ft_hexlen(n);
	while (i < len)
	{
		write(1, &hexchar[i], 1);
		i++;
	}
	free(hexchar);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:10:31 by jaeklee           #+#    #+#             */
/*   Updated: 2025/05/20 15:20:33 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptrlen(unsigned long n)
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

char	*ft_ptrchar(unsigned long n)
{
	int				len;
	char			*temp;
	char			*ptrchar;
	unsigned long	num;

	len = ft_ptrlen(n);
	num = n;
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	temp[len] = '\0';
	ptrchar = "0123456789abcdef";
	while (len > 0)
	{
		len--;
		temp[len] = ptrchar[num % 16];
		num /= 16;
	}
	return (temp);
}

int	ft_printptr(unsigned long ptr)
{
	char	*temp;
	int		len;
	int		i;

	i = 0;
	if (ptr == 0)
	{
		ft_printstr("(nil)");
		return (5);
	}
	len = ft_ptrlen(ptr);
	temp = ft_ptrchar(ptr);
	if (!temp)
		return (0);
	else
	{
		write(1, "0x", 2);
	}
	while (i < len)
	{
		write(1, &temp[i], 1);
		i++;
	}
	free(temp);
	return (len + 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_un.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:08:47 by jaeklee           #+#    #+#             */
/*   Updated: 2025/05/20 15:19:48 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	numlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_uitoa(unsigned int n)
{
	char			*tmp;
	unsigned int	num;
	int				len;

	num = n;
	len = numlen(n);
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	tmp[len] = '\0';
	while (len > 0)
	{
		len--;
		tmp[len] = (num % 10) + '0';
		num = num / 10;
	}
	return (tmp);
}

int	ft_printunnbr(unsigned int n)
{
	char	*num;
	int		len;

	num = ft_uitoa(n);
	len = ft_printstr(num);
	free(num);
	return (len);
}

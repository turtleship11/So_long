/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:16:07 by jaeklee           #+#    #+#             */
/*   Updated: 2025/05/20 15:21:16 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	countnum(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*temp;
	long	num;

	num = n;
	len = countnum(n);
	temp = malloc(len + 1);
	if (!temp)
		return (NULL);
	temp[len] = '\0';
	if (num < 0)
		num = -num;
	while (len--)
	{
		temp[len] = (num % 10) + '0';
		num = num / 10;
	}
	if (n < 0)
		temp[0] = '-';
	return (temp);
}

int	ft_printnbr(int n)
{
	int		p;
	char	*num;

	p = 0;
	num = ft_itoa(n);
	p = ft_printstr(num);
	free(num);
	return (p);
}

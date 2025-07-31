/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:15:55 by jaeklee           #+#    #+#             */
/*   Updated: 2025/07/31 15:06:13 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h> // va_list
# include <stdlib.h> // malloc,free
# include <unistd.h> // write
# include "../libft/libft.h"

int		ft_printchar(int c);
int		ft_printstr(char *str);
int		ft_printptr(unsigned long ptr);
int		ft_printunnbr(unsigned int n);
int		ft_printhex(unsigned int n, const char scale);
char	*ft_itoa(int n);
int		ft_printf(const char *str, ...);
int		ft_printpercent(void);
int		ft_printnbr(int n);
#endif

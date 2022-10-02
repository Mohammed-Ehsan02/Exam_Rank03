/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 14:09:20 by mkhan             #+#    #+#             */
/*   Updated: 2022/05/19 16:51:02 by mkhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_hexadec(unsigned long n)
{
	int		len;
	char	*s;

	s = "0123456789abcdef";
	len = 0;
	if (n > 15)
		len += ft_hexadec(n / 16);
	len += ft_putchar(s[n % 16]);
	return (len);
}

int	ft_hexaddr(unsigned long n)
{
	int	len;

	len = ft_putstr("0x");
	if (n == 0)
		len += ft_putchar('0');
	else
		len += ft_hexadec(n);
	return (len);
}

int	ft_intdec(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
	{
		len += ft_putstr("-2147483648");
		return (len);
	}
	if (n < 0)
	{
		len += ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		len += ft_intdec(n / 10);
	len += ft_putchar((n % 10) + '0');
	return (len);
}

int	ft_unint(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
		len += ft_unint(n / 10);
	len += ft_putchar((n % 10) + '0');
	return (len);
}

int	ft_hexalow(unsigned int n)
{
	int		len;
	char	*s;

	len = 0;
	s = "0123456789abcdef";
	if (n > 15)
		len += ft_hexalow(n / 16);
	len += ft_putchar(s[n % 16]);
	return (len);
}

int	ft_hexacap(unsigned int n)
{
	int		len;
	char	*s;

	len = 0;
	s = "0123456789ABCDEF";
	if (n > 15)
		len += ft_hexacap(n / 16);
	len += ft_putchar(s[n % 16]);
	return (len);
}

int	ft_checkformat(char c, va_list lst)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar(va_arg(lst, int));
	else if (c == 's')
		len += ft_putstr(va_arg(lst, char *));
	else if (c == 'p')
		len += ft_hexaddr(va_arg(lst, unsigned long));
	else if (c == 'd' || c == 'i')
		len += ft_intdec(va_arg(lst, int));
	else if (c == 'u')
		len += ft_unint(va_arg(lst, unsigned int));
	else if (c == 'x')
		len += ft_hexalow(va_arg(lst, unsigned int));
	else if (c == 'X')
		len += ft_hexacap(va_arg(lst, unsigned int));
	else if (c == '%')
		len += ft_putchar(c);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	lst;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(lst, str);
	while (str[i])
	{
		if (str[i] == '%')
			len += ft_checkformat(str[++i], lst);
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(lst);
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanejar <zanejar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 06:45:24 by zanejar           #+#    #+#             */
/*   Updated: 2023/03/09 07:26:55 by zanejar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static	int	ft_countlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n != 0)
	{
		n = (n / 10);
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nbr;
	char	*ptr;

	nbr = n;
	if (nbr == 0)
		return (ft_strdup("0"));
	len = ft_countlen(nbr);
	ptr = malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (0);
	if (nbr < 0)
	{
		nbr = nbr * (-1);
		ptr[0] = '-';
	}
	ptr[len--] = '\0';
	while (nbr != 0)
	{
		ptr[len--] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	char	o;
	char	*d;
	int		i;

	o = (char)c;
	d = (char *)s;
	i = 0;
	if (o == '\0')
	{
		while (d[i])
			i++;
		return (&d[i]);
	}
	while (d[i])
	{
		if (d[i] == o)
			return (&d[i]);
		i++;
	}
	return (0);
}

int	ft_nstrncmp(char *s1, char *s2, int n)
{
	if (!s1 || !s2)
		return (-1);
	while (n && *s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
		--n;
	}
	if (n == 0)
	{
		return (0);
	}
	else
	{
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	}
}

int	vars_init(char *line)
{
	g_b.i = 0;
	g_b.d = 0;
	g_b.s = 0;
	return (quotes_check(line, g_b.i, g_b.d, g_b.s));
}

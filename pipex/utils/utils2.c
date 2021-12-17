/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:56:16 by snakita           #+#    #+#             */
/*   Updated: 2021/12/14 15:56:18 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	i = len;
	if (len > ft_strlen(s))
		i = ft_strlen(s);
	str = (char *)malloc(i + 1);
	if (str)
	{
		i = 0;
		while (start-- > 0 && *s)
			s++;
		while (*s && i < len)
		{
			str[i] = *s++;
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *(unsigned char *)s1
		&& (*(unsigned char *)s1 == *(unsigned char *)s2))
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str)
	{
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		j = -1;
		while (s2[++j])
			str[j + i] = s2[j];
		str[j + i] = '\0';
		free((void *)s1);
		return (str);
	}
	return (NULL);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

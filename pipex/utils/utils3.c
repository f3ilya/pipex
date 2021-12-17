/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakita <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:39:56 by snakita           #+#    #+#             */
/*   Updated: 2021/10/16 18:40:01 by snakita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	chw(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (j);
}

static int	bykvi(char const *s, char c, unsigned int k)
{
	unsigned int	j;

	j = 0;
	while (s[k] != c && s[k])
	{
		k++;
		j++;
	}
	return (j);
}

static char	**otmena(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

static char	**strgo(char const *s, char c, unsigned int i, char **str)
{
	unsigned int	j;
	char			*w;

	j = 0;
	while (s[i])
	{
		if (s[i] == c && s[i])
			i++;
		else
		{
			w = (char *)malloc(sizeof(char) * (bykvi(s, c, i) + 1));
			if (!w)
				return (otmena(str));
			while (s[i] != c && s[i])
				w[j++] = s[i++];
			w[j] = '\0';
			j = 0;
			*str++ = w;
		}
	}
	*str++ = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	unsigned int		i;
	unsigned int		k;
	char				**str;

	i = 0;
	if (!s)
		return (NULL);
	k = chw(s, c);
	str = (char **)malloc(sizeof(char *) * (k + 1));
	if (!str)
		return (NULL);
	if (strgo(s, c, i, str))
		return (str);
	return (NULL);
}

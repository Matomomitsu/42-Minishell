/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlins <rlins@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:01:18 by rlins             #+#    #+#             */
/*   Updated: 2022/12/12 11:52:59 by rlins            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countc(const char *s, char c)
{
	size_t	i;
	size_t	counter;
	size_t	o;

	i = 0;
	counter = 0;
	while (s[i])
	{
		o = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i++] != c)
			o++;
		if (o != 0)
			counter++;
	}
	return (counter);
}

static void	splitstr(char **str, char c, char const *s, size_t countc)
{
	size_t	i;
	size_t	malloc_size;
	size_t	j;

	i = 0;
	j = 0;
	while (j < countc)
	{
		malloc_size = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i++] != c)
			malloc_size++;
		str[j] = (char *)malloc((malloc_size + 1) * sizeof(char));
		if (str[j++] == NULL)
		{
			str = NULL;
			break ;
		}
	}
}

static void	putchar_str(char const *s, char **str, char c, size_t countc)
{
	size_t	i;
	size_t	j;
	size_t	o;

	i = 0;
	j = 0;
	while (j < countc)
	{
		o = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] != c && s[i])
			str[j][o++] = s[i++];
		str[j][o] = '\0';
		j++;
	}
	str[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	countc;

	if (!s)
		return (NULL);
	countc = ft_countc(s, c);
	str = (char **)malloc((countc + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	splitstr(str, c, s, countc);
	if (str == NULL)
		return (NULL);
	putchar_str(s, str, c, countc);
	return (str);
}

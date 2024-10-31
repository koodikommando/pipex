/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:31:53 by okarejok          #+#    #+#             */
/*   Updated: 2023/11/03 16:12:04 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_wrd_len(char const *s, char const c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (len);
		else if (s[i] != c)
			len++;
		i++;
	}
	return (len);
}

static void	free_memory(char **strings, int j)
{
	while (j >= 0)
	{
		free(strings[j]);
		j--;
	}
	free(strings);
}

static char	**allocate_mem(char const *s, char const c, char **strings)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			strings[j] = ft_substr(s, i, ft_get_wrd_len(&s[i], c));
			if (!strings[j])
			{
				free_memory(strings, j);
				return (NULL);
			}
			j++;
			i = i + ft_get_wrd_len(&s[i], c);
		}
	}
	strings[j] = NULL;
	return (strings);
}

static int	count_words(char const *s, char const c)
{
	int		in_wrd;
	size_t	i;
	int		wrd_count;

	wrd_count = 0;
	i = 0;
	in_wrd = 0;
	while (s[i])
	{
		if (s[i] == c)
			in_wrd = 0;
		else if (!in_wrd)
		{
			in_wrd = 1;
			wrd_count++;
		}
		i++;
	}
	return (wrd_count);
}

char	**ft_split(char const *s, char const c)
{
	char	**strings;

	if (!s)
		return (NULL);
	strings = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strings)
		return (NULL);
	if (!allocate_mem(s, c, strings))
		return (NULL);
	return (strings);
}

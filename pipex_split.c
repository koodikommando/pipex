/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:34:59 by okarejok          #+#    #+#             */
/*   Updated: 2024/02/05 19:42:35 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"

static void	free_memory(char **strings, int j)
{
	while (j >= 0)
	{
		free(strings[j]);
		j--;
	}
	free(strings);
}

static char	*allocate_mem(char const *s, int *i)
{
	int		start;
	int		end;
	char	quote;

	while (s[*i] == ' ')
		(*i)++;
	if (s[*i] == '"' || s[*i] == '\'')
	{
		quote = s[*i];
		(*i)++;
		start = *i;
		while (s[*i] && s[*i] != quote)
			(*i)++;
		end = *i;
		if (s[*i])
			(*i)++;
	}
	else
	{
		start = *i;
		while (s[*i] && s[*i] != ' ')
			(*i)++;
		end = *i;
	}
	return (ft_substr(s, start, end - start));
}

static int	inside_quotes(char c, char *q)
{
	static char	save;
	int			i;

	i = 0;
	if ((c == '\'' || c == '"') && *q == 0)
	{
		save = c;
		*q = 1;
		return (1);
	}
	else if ((c == '\'' || c == '"') && save == c)
	{
		save = 0;
		*q = 0;
		return (0);
	}
	return (0);
}

static int	count_words(char const *s, char const c)
{
	int		in_wrd;
	size_t	i;
	int		wrd_count;
	char	quote;

	wrd_count = 0;
	i = 0;
	in_wrd = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == c && !quote)
			in_wrd = 0;
		else if (inside_quotes(s[i], &quote))
		{
			in_wrd = 1;
			wrd_count++;
		}
		else if (!in_wrd)
		{
			in_wrd = 1;
			wrd_count++;
		}
		i++;
	}
	return (wrd_count);
}

char	**pipex_split(char const *s, char const c)
{
	char	**strings;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	strings = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!strings)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_words(s, c))
	{
		strings[j] = allocate_mem(s, &i);
		if (!strings[j])
		{
			free_memory(strings, j);
		}
		j++;
	}
	strings[count_words(s, c)] = NULL; 
	return (strings);
}
/*
int main(void)
{
	char	**splitted;

	splitted = pipex_split("awk '{count ++} END {print count}'", ' ');
	int i = 0;
	while (splitted[i])
	{
		printf("%d: %s\n",i, splitted[i]);
		i++;
	}
}*/
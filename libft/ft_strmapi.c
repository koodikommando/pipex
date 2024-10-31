/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:46:40 by okarejok          #+#    #+#             */
/*   Updated: 2023/11/02 11:55:59 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*mapped_str;

	i = 0;
	if (!s || !f)
		return (NULL);
	mapped_str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!mapped_str)
		return (NULL);
	while (s[i])
	{
		mapped_str[i] = f(i, s[i]);
		i++;
	}
	mapped_str[i] = '\0';
	return (mapped_str);
}

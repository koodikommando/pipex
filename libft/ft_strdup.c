/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:45:08 by okarejok          #+#    #+#             */
/*   Updated: 2023/10/30 11:48:13 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*str_new;

	len = ft_strlen(s1);
	i = 0;
	str_new = (char *)malloc((len + 1) * sizeof(char));
	if (!(str_new))
		return (NULL);
	while (s1[i])
	{
		str_new[i] = s1[i];
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}

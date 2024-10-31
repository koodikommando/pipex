/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:24:58 by okarejok          #+#    #+#             */
/*   Updated: 2023/11/04 16:22:11 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*s_ptr;
	size_t			len;

	s_ptr = (char *)s;
	len = ft_strlen(s);
	if (!s)
		return (s_ptr);
	while (len > 0)
	{
		if (s_ptr[len] == (char)c)
			return (&s_ptr[len]);
		len--;
	}
	if (s_ptr[len] == (char)c)
		return (&s_ptr[len]);
	return (NULL);
}

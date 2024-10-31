/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okarejok <okarejok@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:04:02 by okarejok          #+#    #+#             */
/*   Updated: 2023/11/07 15:26:22 by okarejok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_digits(int n)
{
	size_t	digits;

	digits = 0;
	if (n == 0)
		return (digits = 1);
	while (n != 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	size_t	digits;
	char	*output;
	long	num;

	num = n;
	digits = get_digits(num);
	if (num < 0)
	{
		digits++;
		num = num * -1;
	}
	output = (char *)malloc(sizeof(char) * (digits + 1));
	if (!output)
		return (NULL);
	output[digits] = '\0';
	while (digits > 0)
	{
		output[--digits] = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		output[0] = '-';
	return (output);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:42:14 by jofoto            #+#    #+#             */
/*   Updated: 2022/11/28 18:38:18 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	result;

	result = 0;
	if (s == 0)
		return (0);
	while (*s != 0)
	{
		result++;
		s++;
	}
	return (result);
}
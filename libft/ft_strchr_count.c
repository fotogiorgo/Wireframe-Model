/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofoto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:16:21 by jofoto            #+#    #+#             */
/*   Updated: 2022/11/15 11:41:35 by jofoto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strchr_count(const char *str, int c)
{
	int	ret;

	ret = 0;
	while (*str != 0)
	{
		if (*str == (unsigned char)c)
			ret++;
		str++;
	}
	return (ret);
}
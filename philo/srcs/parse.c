/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:19:27 by ykai-yua          #+#    #+#             */
/*   Updated: 2024/10/05 15:26:21 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && n - 1 > i && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_check_overflow(const char *num_str)
{
	const char	*int_min_str;
	const char	*int_max_str;
	size_t		len;
	int			is_neg;

	int_min_str = "-2147483648";
	int_max_str = "2147483647";
	len = ft_strlen(num_str);
	is_neg = 0;
	if (num_str[0] == '-')
	{
		is_neg = 1;
		num_str++;
		len--;
	}
	if ((is_neg && len > 10) || (!is_neg && len > 10))
		return (1);
	if ((is_neg && len == 10 && ft_strncmp(num_str, int_min_str + 1, len) > 0)
		|| (!is_neg && len == 10 && ft_strncmp(num_str, int_max_str, len) > 0))
		return (1);
	return (0);
}

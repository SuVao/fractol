/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pesilva- <pesilva-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:57:55 by pesilva-          #+#    #+#             */
/*   Updated: 2024/09/26 19:57:57 by pesilva-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t nb)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (nb == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && i < nb - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}


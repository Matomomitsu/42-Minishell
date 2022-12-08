/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:40:33 by rlins             #+#    #+#             */
/*   Updated: 2022/12/07 17:11:37 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t	length;
	char	*result;

	if (src == NULL)
		return (NULL);
	length = ft_strlen(src) + 1;
	result = (char *)malloc(length);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, src, length);
	return (result);
}

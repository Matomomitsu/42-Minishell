/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtomomit <mtomomit@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:21:38 by mtomomit          #+#    #+#             */
/*   Updated: 2022/08/12 22:50:08 by mtomomit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, size_t size)
{
	char	*temp;

	if (!str)
		return (NULL);
	else
	{
		temp = (char *)malloc(sizeof(char) * (size));
		ft_strlcpy(temp, str, size + 1);
		free(str);
	}
	if (!temp)
		return (NULL);
	return (temp);
}

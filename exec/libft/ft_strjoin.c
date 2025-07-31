/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waissi <waissi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:43:53 by waissi            #+#    #+#             */
/*   Updated: 2025/07/31 12:31:07 by adahab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void	ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	//dest[i] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				ttl;
	char			*r;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if ((!s1 && !s2) || (!s1 || !s2))
		return (NULL);
	ttl = ft_strlen((char *)str1) + ft_strlen((char *)str2);
	r = ft_calloc(ttl + 1, sizeof(char));
	if (!r)
		return (NULL);
	ft_strcpy(r, (char *)str1);
	ft_strcat(r, (char *)str2);
	//free(s1);
	return ((char *)r);
}
/*
int	main(void)
{
	char	ch[] = "baysal ";
	char	chh[] = "kbir";

	printf("%s",ft_strjoin(ch,chh));
}
*/

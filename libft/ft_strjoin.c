/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:50:46 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/14 16:17:46 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	while (s1 && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		if (s2[j] == '\n')
			break ;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

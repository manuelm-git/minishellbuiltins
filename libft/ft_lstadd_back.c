/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:40:25 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/14 16:29:50 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*last;

	last = ft_lstlast(*lst);
	if (!lst || !new)
		return (NULL);
	if (!*lst)
	{
		*lst = new;
		return (NULL);
	}
	last->next = new;
	new->prev = last;
	return (new);
}

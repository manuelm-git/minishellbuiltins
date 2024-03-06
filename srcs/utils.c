/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:56:04 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/05 18:16:50 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_data *node)
{
	t_data	*current;

	while (node)
	{
		current = node;
		node = node->next;
		free_array(current->args);
		free_array(current->infile);
		free_array(current->outfile);
		free_array(current->outflag);
		free_array(current->envpexport);
		free_array(current->envp);
		free(current);
	}
}

t_data	*ft_lstfirst(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev != NULL)
		lst = lst->prev;
	return (lst);
}

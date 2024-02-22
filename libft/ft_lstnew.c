/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:15:27 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/22 18:00:12 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_data(t_data *node)
{
	node->args = NULL;
	node->fd[0] = 0;
	node->fd[1] = 1;
	node->infile = NULL;
	node->outfile = NULL;
	node->outflag = NULL;
	node->next = NULL;
	node->prev = NULL;
	node->envp = NULL;
	node->numofargs = 0;
}

t_data	*ft_lstnew(char **envp)
{
	t_data	*ptr;

	ptr = ft_calloc(1, sizeof(t_data));
	if (!ptr)
		return (NULL);
	init_data(ptr);
	ptr->envp = dpdup(envp);
	return (ptr);
}

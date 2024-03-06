/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:30:04 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/05 16:35:38 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// add_args - appends a string to an already existing array of strings
/*
int	*add_int(int *array, int value)
{
	int		size;
	int		i;
	int		len;

	while (array && array[len])
} */
char	**add_args(char **args, char *token)
{
	int i;
	int len;
	char	**ptr;
	
	i = 0;
	len = 0;
	while (args && args[len])
		len++;
	ptr = ft_calloc((len + 2), sizeof(char *));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = args[i];
		i++;
	}
	ptr[i] = ft_strdup(token);
	free(args);
	return (ptr);
}

// parser - takes the tokens given by lexer and assigns them to a linked list

t_data	*parser(char **token)
{
	t_data	*data;
	int		i;

	i = 0;
	data = ft_lstnew();
	data->numofargs = 0;
	while (token[i])
	{
		while (token[i] && ft_strncmp(token[i], "|", 2))
		{
			if (!ft_strncmp(token[i], "<", 2) && ++i)
				data->infile = add_args(data->infile, token[i]);
			else if (!ft_strncmp(token[i], ">", 2) && ++i)
			{
				data->outfile = add_args(data->outfile, token[i]);
				data->outflag = add_args(data->outflag, "0");
			}
			else if (!ft_strncmp(token[i], ">>", 3) && ++i)
			{
				data->outfile = add_args(data->outfile, token[i]);
				data->outflag = add_args(data->outflag, "1");
			}
			else
				data->args = add_args(data->args, token[i]);
			i++;
		}
		if (token[i] && !ft_strncmp(token[i], "|", 2))
		{
			data = ft_lstadd_back(&data, ft_lstnew());
			i++;
		}
	}
	data->numofargs = i;
	free_array(token);
	return (ft_lstfirst(data));
}

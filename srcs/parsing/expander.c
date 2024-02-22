/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:31:37 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/16 16:52:43 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*rem_quotes(char *str);

char	*expand(char *str, char **envp);

//Checks if there are quoted or expandable strings

void	expander(t_data *current, char **envp)
{
	int		j;

	while (current)
	{
		j = 0;
		while (current->args && current->args[j])
		{
			if (current->args[j][0] == 36 && current->args[j][1])
				current->args[j] = expand(current->args[j], envp);
			else if (current->args[j][0] == 34)
			{
				current->args[j] = rem_quotes(current->args[j]);
				if (current->args[j][0] == 36 && current->args[j][1])
					current->args[j] = expand(current->args[j], envp);
			}
			else if (current->args[j][0] == 39)
				current->args[j] = rem_quotes(current->args[j]);
			j++;
		}
		current = current->next;
	}
}

//Removes quotes from the string by moving every character one position
//to the left and setting the last 2 to NULLs

char	*rem_quotes(char *str)
{
	int		i;
	int		len;

	len = ft_strlen(str);
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && i < (len - 2))
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i++] = '\0';
	str[i++] = '\0';
	return (str);
}

//Searchs for the string in the environment variables
//If found, frees the string and returns a copy of the variable's value

char	*expand(char *str, char **envp)
{
	char	*str1;
	char	*env;
	int		i;
	int		len;

	i = 0;
	env = NULL;
	if (!envp)
		return (NULL);
	len = ft_strlen(str);
	str1 = ft_strdup(&str[1]);
	while (envp && envp[i] && ft_strncmp(str1, envp[i], ft_strlen(str1)))
		i++;
	if (envp[i] && !ft_strncmp(str1, envp[i], ft_strlen(str1)))
		env = ft_strdup(&envp[i][len]);
	free(str);
	free(str1);
	return (env);
}

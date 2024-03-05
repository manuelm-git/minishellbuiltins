/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:59:31 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/05 12:32:39 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// count_op - runs through the string and counts each operator found
// Probably needs fix to account for >> and <<

int	count_op(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			i = i + (inv_comma(str, i, str[i])) + 1;
		if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i
				+ 1] == '>'))
		{
			count++;
			i++;
		}
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			count++;
		i++;
	}
	return (count);
}

// alloc_sep - allocates the memory for new string with spaces
// between each operator (strlen + operator x 2 + \0)

char	*alloc_sep(char *str)
{
	int		len;
	int		count;
	char	*ptr;

	count = count_op(str);
	len = ft_strlen(str);
	ptr = ft_calloc((len + (count * 2) + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	return (ptr);
}

// separate - function that adds a space before and after each operator
// takes into account if it's just > or if it's >> and ignores stuff in ""

char	*separate(char *str, char *ptr)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			k = (inv_comma(str, i, str[i])) + 1;
		while (k-- > 0)
			ptr[j++] = str[i++];
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			ptr[j++] = ' ';
			ptr[j++] = str[i++];
			if ((str[i] != '|' && str[i] == str[i - 1]))
				ptr[j++] = str[i++];
			ptr[j++] = ' ';
		}
		else
			ptr[j++] = str[i++];
	}
	return (ptr);
}
// lexer - runs everything else, separate then split, and frees everything.

char	**lexer(char *str)
{
	char	*ptr;
	char	*sep;
	char	**lex;

	ptr = alloc_sep(str);
	sep = separate(str, ptr);
	lex = ft_split(sep, ' ');
	free(sep);
	return (lex);
}
// main for testing lexer

/* int	main(int argc, char **argv)
{
	char	**lex;
	int		i;

	i = 0;
	lex = NULL;
	if (argc == 2)
	{
		lex = lexer(argv[1]);
		while (lex[i])
		{
			printf("%s\n", lex[i]);
			i++;
		}
		i = 0;
		while (lex[i])
		{
			free(lex[i]);
			i++;
		}
		free(lex);
	}
	return (0);
} */

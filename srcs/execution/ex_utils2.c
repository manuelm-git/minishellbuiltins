/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:41:51 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/05 12:31:26 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Checks if there is an infile and/or outfile on the node
// If there is, opens them and dups the file descriptor to stdin or stdout
// Works for multiple infiles and outfiles

int	infile_check(int dups[2], t_data *data);

int	outfile_check(int dups[2], t_data *data);

int	file_check(int dups[2], t_data *data)
{
	if (infile_check(dups, data) && outfile_check(dups, data))
		return (1);
	return (0);
}

int	infile_check(int dups[2], t_data *data)
{
	int	fd;
	int	i;

	i = 0;
	while (data->infile && data->infile[i])
	{
		fd = open(data->infile[i], O_RDONLY);
		if (fd < 0)
		{
			perror(data->infile[i]);
			return (0);
		}
		dups[0] = dupcheck(fd, dups[0]);
		close(fd);
		i++;
	}
	return (1);
}

int	outfile_check(int dups[2], t_data *data)
{
	int	fd;
	int	i;

	i = 0;
	while (data->outfile && data->outfile[i])
	{
		if (!ft_strncmp(data->outflag[i], "0", 1))
			fd = open(data->outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(data->outfile[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(data->outfile[i]);
			return (0);
		}
		dups[1] = dupcheck(fd, dups[1]);
		close(fd);
		i++;
	}
	return (1);
}

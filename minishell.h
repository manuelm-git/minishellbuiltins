/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:43:38 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/03/06 16:25:47 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// struct used to store the command to execute, arguments for said command
// the stdin and stdout of said command and a flag to recognise a pipe

typedef struct s_data
{
	char			**args;
	int				numofargs;
	int				fd[2];
	char			**infile;
	char			**outfile;
	char			**outflag;
	struct s_data	*next;
	struct s_data	*prev;
	char			**envp;
	char			**envpexport;
}					t_data;

// typedef struct s_envp
// {
// 	char *previous;
// 	char *next;
// 	char *content;
// }	t_envp;

// utils.c

t_data				*minishelldata(void);

void				free_all(t_data *node);

t_data				*ft_lstfirst(t_data *lst);

// ex_utils1.c

int					pcheck(char *ptr);

char				*rem_quotes(char *str);

char				*pathtest(char *env, char *arg);

char				*check_path(char *arg, char **envp);

int					dupcheck(int file_fd, int fd);

void				close_fd(int *fd);

// ex_utils2.c

int					file_check(int dups[2], t_data *data);

char				**dpdup(char **str);

int					getdpsize(char **str);

void				free_array(char **str);

void 				clean_env();
// executor.c

void				execution(t_data *data, char **envp);

int					check_builtin(t_data *data);

// builtins.c

void				exec_pwd(void);

void				exec_cd(t_data *data);

void				exec_exit(t_data *data);

void				exec_echo(t_data *data);

void				exportonly(char **envpsorted);

void				exec_env(t_data *data);

void				exec_export(t_data *data);

// forks.c

void				first_fork(t_data *data, char **envp);

void				mid_fork(t_data *data, char **envp);

void				last_fork(t_data *data, char **envp);

// expander.c

void				expander(t_data *data, char **envp);

// parser.c

t_data				*parser(char **token);

char				**add_args(char **args, char *token);

// lexer.c

char				**lexer(char *str);

// libft

int					inv_comma(char const *ptr, int i, char c);

char				**ft_split(char const *s, char c);

char				*ft_substr(const char *s, unsigned int start, size_t len);

size_t				ft_strlcpy(char *dst, const char *src, size_t size);

void				*ft_calloc(size_t nmemb, size_t size);

void				ft_bzero(void *s, size_t n);

size_t				ft_strlen(const char *str);

t_data				*ft_lstnew(void);

t_data				*ft_lstadd_back(t_data **lst, t_data *new);

int					ft_lstsize(t_data *lst);

t_data				*ft_lstlast(t_data *lst);

int					ft_strncmp(const char *s1, const char *s2, size_t n);

char				*ft_strdup(const char *s);

void				*ft_memcpy(void *dest, const void *src, size_t n);

char				*ft_strjoin(char *s1, char *s2);

int					ft_isdigit(char *str);

int					ft_atoi(char *nptr);

char	*ft_strchr(const char *str, int c);
#endif
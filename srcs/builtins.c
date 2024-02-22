/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:18:32 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/02/22 17:59:29 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pwd(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	if (cwd != NULL)
		printf("%s\n", cwd);
}

void	exec_cd(t_data *data)
{
	int	i;

	i = 0;
	while (data->args[i])
		i++;
	if (i <= 2)
	{
		if (!data->args[1] || !ft_strncmp(data->args[1], "--", 3))
			chdir(getenv("HOME"));
		else if (!ft_strncmp(data->args[1], "-", 2))
			chdir(getenv("OLDPWD"));
		else if (!access(data->args[1], F_OK))
			chdir(data->args[1]);
		else
			printf("cd : no such file or directory: %s\n", data->args[1]);
	}
	else
		printf("cd: too many arguments\n");
}

void	exec_exit(t_data *data)
{
	int	exitcode;
	int	i;

	i = 0;
	exitcode = 0;
	while (data->args[i])
		i++;
	printf("exit\n");
	if (i <= 2)
	{
		if (i == 2 && ft_isdigit(data->args[1]))
		{
			printf("exit : %s: numeric argument required\n", data->args[1]);
			exitcode = 255;
		}
		else if (i == 2 && !ft_isdigit(data->args[1]))
		{
			exitcode = ft_atoi(data->args[1]);
		}
		free_all(ft_lstfirst(data));
		exit(exitcode);
	}
	else
		printf("exit: too many arguments\n");
}


//env
void exec_env(t_data *data)
{
    int i = 0;
    if(data->args[1])
    {
        printf("env: '%s': No such file or directory",data->args[1]);
    }
    else
    {
        while (data->envp[i])
        {
            printf("%s\n",data->envp[i]);
            i++;
        }
    }
}


//



//echo

void exec_echo(t_data *data)
{
    int newline;
    int i;

    newline = 0;
    i = 1;

    if(data->numofargs >= 2)
    {
        if(!ft_strncmp(data->args[1],"-n",2))
        {
            newline = 1;        
        }
        else
        {
            while (data->args[i])
            {
                write(1,data->args[i],ft_strlen(data->args[i]));
                i++;
            }
            
        }
        if(newline == 0)
            write(1,"\n",1);
    }
    else
        write(1,"\n",1);
}
//

int ft_isalnum(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] >= '0' && str[i] <= '9'))
            return (1);
        else if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
            return (1);
        i++;
    }
    return(0);
}

//export

//free array

void free_array(char **str)
{
    if(str == NULL)
    {
        return;
    }

	int i;

	i = 0;    
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
//dup de variavel DP
char **dpdup(char **str)
{
	char **dup;
	size_t i;

	i = 0;
	while(str[i] != NULL)
		i++;
	dup = ft_calloc(sizeof(char *), i + 1);
	if(!dup)
		return(0);
	i = 0;
	while (str[i] != NULL)
	{
		dup[i] = ft_strdup(str[i]);
		if(dup[i] == NULL)
		{
			free_array(dup);
			return(dup);
		}
		i++;
	}
	return(dup);
}
//obter tamanho de uma variavel double pointer (DP)
int getdpsize(char **str)
{
    int i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}

char **sortenvp(char **envpsorted,int envp_size)
{
    int swapped;
    int i;
    char *temp;
    swapped = 1;

    while (swapped)
    {
        swapped = 0;
        i = 0;
        while (i < envp_size - 1)
        {
            if(ft_strncmp(envpsorted[i],envpsorted[i + 1],envp_size) > 0)
            {
                swapped = 1;
                temp = envpsorted[i];
                envpsorted[i] = envpsorted[i + 1];
                envpsorted[i + 1] = temp;
            }
            i++;
        }
        envp_size--;
    }
    return(envpsorted);
}
void printenvpsorted(char **envpsorted)
{
    int i;
    char previouschar;
    int j;

    i = 0;
    while(envpsorted[i])
    {
        j = 0;
        write(1,"declare -x ",12);
        while(envpsorted[i][j] != '\0')
        {
            previouschar = envpsorted[i][j];
            write(1,&envpsorted[i][j],1);
            if(previouschar == '=' )
            {
                write(1,"\"",1);
            }
            j++;
        }
        write(1,"\"",1);
        write(1,"\n",1);
        i++;
    }
    free_array(envpsorted);
}
void exportonly(t_data *data)
{
    char **envpsorted;
    int envp_size;
    
    envp_size = getdpsize(data->envp);
    envpsorted = ft_calloc((envp_size + 1),sizeof(char *));
    if(!envpsorted)
        return;
    envpsorted = sortenvp(dpdup(data->envp),envp_size);
    printenvpsorted(envpsorted);
    
}

void exporterror(t_data *data,char **new,int i)
{
    write(2,"export: \'",10);
    write(2,data->args[i],ft_strlen(data->args[i]));
    write(2,"\': not a valid identifier\n",26);
    free_array(new);
}

int searchinenvp(t_data *data,char *input)
{
    int i;

    i = 0;
    while (data->envp[i])
    {
        if(ft_strncmp(data->envp[i],input,ft_strlen(input)))
            return(i);
        i++;
    }
    return(0);
}
// void exportwithargs(t_data *data,char **new,int i)
// {
//     if(!new || !new[0])
//     {
//         exporterror(data,new,i);
//         return;
//     }    
//     if(!searchinenvp(data,new[0]))
    
// }
void exec_export(t_data *data)
{
    char **new;
    int i;

    i = 0;
    if(data->numofargs < 2)
        exportonly(data);
    else
    {
        while (data->args[i])
        {
            new = ft_split(data->args[i],'=');
            if(data->args[i][0] == '=' || (new && ft_isalnum(new[0])) || ft_isdigit(&data->args[i][0]))
                exporterror(data,new,i);
            // else
            //     exportwithargs(data,new,i);
            i++;
        }
        
    }
}

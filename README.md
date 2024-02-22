# Minishell

The minishell project requires students to build their own smaller version of shell following the established guidelines and requirements. It is the first project of the 42 cursus that is developed with another student. To make this project happen, I and Manuel ([manumart](https://github.com/manuelm-git) - check out his github as well) paired up and put our skills to the test.

**This project and Readme are still in development - everything here is subject to change so take what you see here '*with a grain of salt*'.**

## Index
I. [Usage](#usage)

II.[Features](#features)

III. [Structure](#structure)

## Usage
>In development
## Features
>In development
### Built-in Functions
>In development
## Structure
<div  align="center"> <strong>
INPUT → LEXER → SYNTAX CHECKER → PARSER → EXPANDER  → EXECUTOR
</strong> </div>

### Lexer
The lexer's function is to tokenize the received input. It does this by separating the operators from any words — adding a *space* before and after each operator ( | , < , >, <<, >>) . Afterwards, it procceds to split each word into tokens, respecting single ( ' ) and double ( " ) quotes.
<div  align="center">

`ls -l|"grep a">outfile` → `ls -l | "grep a" > outfile` →`ls`  `-l`  `|`  `"grep a"`  `>`  `outfile`

</div>

For easier understanding in the following segments, we'll classify these tokens as **operator tokens** (if they contain a token) or as **word tokens** (everything else) depending on their content.

### Syntax Checker

>In development

### Parser
>In development

The parser assigns the tokens provided by the lexer (and checked by the syntax checker) to their respective place in a struct called **data** so, later on, it can be interpreted by the executor. These structs form a linked list, with each node of the list representing a command.

```
    struct data
    {
    	char		**args;
    	int		fd[2];
    	char		**infile;
    	char		**outfile;
    	struct s_data	*next;
    	struct s_data	*prev;
    }	
```
Tokens are assigned following these rules:
 1. if a **operator token** is found and it is a redirection (< or >), the following token is added to the corresponding *infile* or *outfile* array.
 2. if a **word token** is found, it is added to the *args* array — where the first string of that array will be the command name, and all other will be the command arguments.
 3. if a **operator token** is found and it is a pipe ( | ) a new node is created and the *next* and *prev* pointers are set accordingly.
```
data1						data2
{						{
	char		**args = [ls , -l]		char		**args = ["grep a"]
	int		fd[2] = [0 , 1]			int		fd[2] = [0 , 1]
	char		**infile = NULL			char		**infile = NULL
	char		**outfile = NULL		char		**outfile = outfile
	struct s_data	*next = &data2			struct s_data	*next = NULL
	struct s_data	*prev = NULL			struct s_data	*prev = &data1
}						}	
```
### Expander
>In development

After the linked list is contructed each string in the *args* array of each node is checked for single or double quotations and for expandable arguments — arguments starting with a *$* which are not in between single quotes.
Any quoted string has its quotes removed.

```
data1						data2
{						{
	char		**args = [ls , -l]		char		**args = [grep a]
	int		fd[2] = [0 , 1]			int		fd[2] = [0 , 1]
	char		**infile = NULL			char		**infile = NULL
	char		**outfile = NULL		char		**outfile = outfile
	struct s_data	*next = &data2			struct s_data	*next = NULL
	struct s_data	*prev = NULL			struct s_data	*prev = &data1
}						}	
```

### Executor
>In development

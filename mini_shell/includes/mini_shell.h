/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:24:34 by mel-badd          #+#    #+#             */
/*   Updated: 2025/04/17 11:41:46 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
// #define TOKEN_WORD 0
// #define TOKEN_PIPE 1
// #define TOKEN_APPEND 2
// #define TOKEN_HEREDOC 3
// #define TOKEN_REDIRECT_OUT 4
// #define TOKEN_REDIRECT_IN 5
// #define TOKEN_OPEN_PAREN 6
// #define TOKEN_CLOSE_PAREN 7
// #define TOKEN_OR 8
// #define TOKEN_AND 9
// #define TOKEN_OPTION 10


	typedef  enum
	{
  		TOKEN_WORD,
    	TOKEN_PIPE,
    	TOKEN_APPEND,
    	TOKEN_HEREDOC,
    	TOKEN_REDIRECT_IN,
    	TOKEN_REDIRECT_OUT,
    	TOKEN_OPEN_PAREN,
    	TOKEN_CLOSE_PAREN,
		TOKEN_FILE,
		TOKEN_OR,
    	TOKEN_OPTION,
	}	t_type;
	typedef struct s_token {
		char *value;
		t_type type;
		struct s_token *next;
	} t_token;

	typedef enum e_error_type
	{
    	UNEXPECTED_TOKEN,
    	UNCLOSED_QUOTE,
    	UNMATCHED_PAREN,
    	EMPTY_COMMAND,
    	REDIRECTION_ERROR
	}   t_error_type;

	typedef struct s_syntax_error
	{
	    t_error_type type;
	    char         *token_value; // e.g. "|", "&&", etc.
	    int          position;     // index in input
	    char         *message;     // full error message for display
	}   t_syntax_error;

	typedef struct s_cmd
	{
		t_token *arg;
		char *cmd;
		char **option;
		char **redirection;
		int ex_status;
		struct s_cmd *next;
		// struct *node;
	}	t_cmd;

char	**ft_split(char const *s, char c);
void append_token(t_token **head, t_token *new_token);
t_token *create_token(char *value, t_type type);
// t_token *tokenize(char *input);
void print_type(t_type type);
t_type get_token_type(char *str);
// void mark_file_tokens(t_token *tokens);
void error(t_token *tokens);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *src);
void error_pipe(t_token *tokens);
size_t	ft_strlen(const char *s);
int ft_strcmp(char *s1, char *s2);
void sigint_handler(int sig);
char	*ft_strchr(const char *s, int c);
t_token *tokenize(char *input);
char *read_input(char *prompt);
void parse(void);
char	*ft_strjoin(char const *s1, char const *s2);
#endif

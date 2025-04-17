/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:38:19 by mel-badd          #+#    #+#             */
/*   Updated: 2025/04/17 11:30:03 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }
// char	*ft_strdup(const char *src)
// {
// 	int		len;
// 	int		i;
// 	char	*dest;

// 	len = ft_strlen(src);
// 	dest = malloc(len + 1);
// 	if (!dest)
// 		return (NULL);
// 	i = 0;
// 	while (src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }
// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	char	*sub;

// 	if (!s)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 		return (ft_strdup(""));
// 	if (len > ft_strlen(s) - start)
// 		len = ft_strlen(s) - start;
// 	sub = (char *)malloc (sizeof(char) * (len + 1));
// 	if (!sub)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		sub[i] = s[start + i];
// 		i++;
// 	}
// 	sub[i] = '\0';
// 	return (sub);
// }
// char	*ft_strchr(const char *s, int c)
// {
// 	char	cc;
// 	int		i;

// 	cc = (char)c;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == cc)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	if (s[i] == cc)
// 		return ((char *)&s[i]);
// 	return (NULL);
// }

// t_token *create_token(char *value, t_type type) {
// 	t_token *token = malloc(sizeof(t_token));
// 	if (!token)
// 		return NULL;
// 	token->value = strdup(value);
// 	token->type = type;
// 	token->next = NULL;
// 	return token;
// }

// void append_token(t_token **head, t_token *new_token) {
// 	if (!*head)
// 		*head = new_token;
// 	else
// 	{
// 		t_token *tmp = *head;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new_token;
// 	}
// }

// t_type get_token_type(char *str)
// {
// 	if (strcmp(str, "|") == 0)
// 		return TOKEN_PIPE;
// 	if (strcmp(str, ">>") == 0)
// 		return TOKEN_APPEND;
// 	if (strcmp(str, "||") == 0)
// 		return TOKEN_OR;
// 	if (strcmp(str, "<<") == 0)
// 		return TOKEN_HEREDOC;
// 	if (strcmp(str, "<") == 0)
// 		return TOKEN_REDIRECT_IN;
// 	if (strcmp(str, ">") == 0)
// 		return TOKEN_REDIRECT_OUT;
// 	if (strcmp(str, "(") == 0)
// 		return TOKEN_OPEN_PAREN;
// 	if (strcmp(str, ")") == 0)
// 		return TOKEN_CLOSE_PAREN;
// 	if (str[0] == '-')
// 		return TOKEN_OPTION;
// 	return TOKEN_WORD;
// }

// void mark_file_tokens(t_token *tokens)
// {
// 	while (tokens && tokens->next)
// 	{
// 		if (tokens->type == TOKEN_REDIRECT_IN ||
// 			tokens->type == TOKEN_REDIRECT_OUT ||
// 			tokens->type == TOKEN_APPEND ||
// 			tokens->type == TOKEN_HEREDOC)
// 		{
// 			if (tokens->next->type == TOKEN_WORD)
// 				tokens->next->type = TOKEN_FILE;
// 		}
// 		tokens = tokens->next;
// 	}
// }

// t_token *tokenize(char *input)
// {
// 	t_token *tokens = NULL;
// 	int i = 0;

// 	while (input[i])
// 	{
// 		if (isspace(input[i]))
// 		{
// 			i++;
// 			continue;
// 		}
// 		if (input[i] == '"' || input[i] == '\'')
// 		{
// 			char quote = input[i++];
// 			int start = i;
// 			while (input[i] && input[i] != quote)
// 				i++;
// 			char *quoted = ft_substr(input, start, i - start);
// 			append_token(&tokens, create_token(quoted, get_token_type(quoted)));
// 			free(quoted);
// 			if (input[i] == quote) i++; // skip closing quote
// 			continue;
// 		}
// 		if (ft_strchr("><|&", input[i]) && input[i] == input[i + 1])
// 		{
// 			char op[3] = {input[i], input[i + 1], '\0'};
// 			append_token(&tokens, create_token(op, get_token_type(op)));
// 			i += 2;
// 			continue;
// 		}
// 		if (ft_strchr("><|()", input[i]))
// 		{
// 			char op[2] = {input[i], '\0'};
// 			append_token(&tokens, create_token(op, get_token_type(op)));
// 			i++;
// 			continue;
// 		}
// 		int start = i;
// 		while (input[i] && !isspace(input[i]) && !ft_strchr("><|()\"\'", input[i]))
// 			i++;
// 		char *word = ft_substr(input, start, i - start);
// 		append_token(&tokens, create_token(word, get_token_type(word)));
// 		free(word);
// 	}
// 	// handle_double_redirects(&tokens);
// 	mark_file_tokens(tokens);
// 	return tokens;
// }

// void print_type(t_type type)
// {
// 	if (type == TOKEN_WORD)
// 		printf("TOKEN_WORD\n");
// 	else if (type == TOKEN_PIPE)
// 		printf("TOKEN_PIPE\n");
// 	else if (type == TOKEN_OR)
// 		printf("TOKEN_OR\n");
// 	else if (type == TOKEN_REDIRECT_IN)
// 		printf("TOKEN_REDIRECT_IN\n");
// 	else if (type == TOKEN_REDIRECT_OUT)
// 		printf("TOKEN_REDIRECT_OUT\n");
// 	else if (type == TOKEN_APPEND)
// 		printf("TOKEN_APPEND\n");
// 	else if (type == TOKEN_HEREDOC)
// 		printf("TOKEN_HEREDOC\n");
// 	else if (type == TOKEN_OPEN_PAREN)
// 		printf("TOKEN_OPEN_PAREN\n");
// 	else if (type == TOKEN_CLOSE_PAREN)
// 		printf("TOKEN_CLOSE_PAREN\n");
// 	else if (type == TOKEN_OPTION)
// 		printf("TOKEN_OPTION\n");
// 	else if (type == TOKEN_FILE)
// 		printf("TOKEN_FILE\n");
// 	// else
// 	// 	printf("UNKNOWN TOKEN\n");
// }
// void	error_pipe(t_token *tokens)
// {
// 	t_token *cur = tokens;

// 	while (cur)
// 	{
// 		if ((cur->type == TOKEN_PIPE && !cur->next) ||
// 			(cur->type == TOKEN_OR))
// 		{
// 			printf("minishell: syntax error near unexpected token '%s'\n", cur->value);
// 			return;
// 		}

// 		cur = cur->next;
// 	}
// }

// void error(t_token *tokens)
// {
//     t_token *cur = tokens;

//     while (cur)
//     {
// 		if ((cur->type == TOKEN_REDIRECT_OUT && !cur->next) ||
// 			(cur->type == TOKEN_REDIRECT_IN && !cur->next) ||
// 			(cur->type == TOKEN_APPEND && !cur->next) ||
// 			(cur->type == TOKEN_HEREDOC && !cur->next) ||
// 			(cur->type == TOKEN_APPEND && cur->next->type == TOKEN_REDIRECT_OUT) ||
// 			(cur->type == TOKEN_APPEND && cur->next->type == TOKEN_REDIRECT_IN) ||
// 			(cur->type == TOKEN_REDIRECT_IN && cur->next->type == TOKEN_APPEND) ||
// 			// (cur->type == TOKEN_HEREDOC && cur->next->type == TOKEN_REDIRECT_IN) ||
// 			(cur->type == TOKEN_HEREDOC && cur->next->type == TOKEN_HEREDOC) ||
// 			(cur->type == TOKEN_APPEND && cur->next->type == TOKEN_APPEND) ||
// 			(cur->type == TOKEN_REDIRECT_OUT && cur->next->type == TOKEN_REDIRECT_IN) ||
// 			(cur->type == TOKEN_REDIRECT_IN && cur->next->type == TOKEN_HEREDOC) ||
// 			(cur->type == TOKEN_REDIRECT_OUT && cur->next->type == TOKEN_HEREDOC) ||
// 			(cur->type == TOKEN_HEREDOC && cur->next->type == TOKEN_REDIRECT_OUT) ||
// 			(cur->type == TOKEN_REDIRECT_OUT && cur->next->type == TOKEN_REDIRECT_OUT) ||
// 			(cur->type == TOKEN_REDIRECT_IN && cur->next->type == TOKEN_REDIRECT_IN))
//         {
//             printf("minishell: syntax error near unexpected token '%s'\n", cur->value);
//             return;
//         }
//         cur = cur->next;
//     }
// }

char *read_input(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (!input)
	{
		write(1, "exit\n", 6);
		exit(0);
	}
	if (*input)
		add_history(input);
	return (input);
}

// void parse(void)
// {
// 	t_token *tokens;
// 	char	*input;

// 	input = read_input("minishell$ ");
// 	tokens = NULL;
// 	tokens = tokenize(input);
// 	mark_file_tokens(tokens);
// 	free(input);
// 	t_token *tmp = tokens;
// 	while(tmp)
// 	{
// 		printf("Value: %s\t ", tmp->value);
// 		print_type(tmp->type);
// 		tmp = tmp->next;
// 	}
// 	if (tokens->type == TOKEN_PIPE)
// 	{
// 		printf("minishell: syntax error near unexpected token '%s'\n", tokens->value);
// 		return;
// 	}
// 	error(tokens);
// 	error_pipe(tokens);
// }


void sigint_handler(int sig)
{
    (void)sig;
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    rl_catch_signals = 0;
    while (1)
	{
        parse();
		// error_handler("Error", 1);
	}
    return 0;
}

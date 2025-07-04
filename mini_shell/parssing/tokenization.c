/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:14:49 by mel-badd          #+#    #+#             */
/*   Updated: 2025/04/17 11:30:19 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

t_type get_token_type(char *str)
{
	if (strcmp(str, "|") == 0)
		return TOKEN_PIPE;
	if (strcmp(str, ">>") == 0)
		return TOKEN_APPEND;
	if (strcmp(str, "||") == 0)
		return TOKEN_OR;
	if (strcmp(str, "<<") == 0)
		return TOKEN_HEREDOC;
	if (strcmp(str, "<") == 0)
		return TOKEN_REDIRECT_IN;
	if (strcmp(str, ">") == 0)
		return TOKEN_REDIRECT_OUT;
	if (strcmp(str, "(") == 0)
		return TOKEN_OPEN_PAREN;
	if (strcmp(str, ")") == 0)
		return TOKEN_CLOSE_PAREN;
	if (str[0] == '-')
		return TOKEN_OPTION;
	return TOKEN_WORD;
}

void print_type(t_type type)
{
	if (type == TOKEN_WORD)
		printf("TOKEN_WORD\n");
	else if (type == TOKEN_PIPE)
		printf("TOKEN_PIPE\n");
	else if (type == TOKEN_OR)
		printf("TOKEN_OR\n");
	else if (type == TOKEN_REDIRECT_IN)
		printf("TOKEN_REDIRECT_IN\n");
	else if (type == TOKEN_REDIRECT_OUT)
		printf("TOKEN_REDIRECT_OUT\n");
	else if (type == TOKEN_APPEND)
		printf("TOKEN_APPEND\n");
	else if (type == TOKEN_HEREDOC)
		printf("TOKEN_HEREDOC\n");
	else if (type == TOKEN_OPEN_PAREN)
		printf("TOKEN_OPEN_PAREN\n");
	else if (type == TOKEN_CLOSE_PAREN)
		printf("TOKEN_CLOSE_PAREN\n");
	else if (type == TOKEN_OPTION)
		printf("TOKEN_OPTION\n");
	else if (type == TOKEN_FILE)
		printf("TOKEN_FILE\n");
	// else
	// 	printf("UNKNOWN TOKEN\n");
}

void mark_file_tokens(t_token *tokens)
{
	while (tokens && tokens->next)
	{
		if (tokens->type == TOKEN_REDIRECT_IN ||
			tokens->type == TOKEN_REDIRECT_OUT ||
			tokens->type == TOKEN_APPEND ||
			tokens->type == TOKEN_HEREDOC)
		{
			if (tokens->next->type == TOKEN_WORD)
				tokens->next->type = TOKEN_FILE;
		}
		tokens = tokens->next;
	}
}

t_token *tokenize(char *input)
{
	t_token *tokens = NULL;
	int i = 0;

	while (input[i])
	{
		if (isspace(input[i]))
		{
			i++;
			continue;
		}
		if (input[i] == '"' || input[i] == '\'')
		{
			char quote = input[i++];
			int start = i;
			while (input[i] && input[i] != quote)
				i++;
			char *quoted = ft_substr(input, start, i - start);
			append_token(&tokens, create_token(quoted, get_token_type(quoted)));
			free(quoted);
			if (input[i] == quote) i++; // skip closing quote
			continue;
		}
		if (ft_strchr("><|&", input[i]) && input[i] == input[i + 1])
		{
			char op[3] = {input[i], input[i + 1], '\0'};
			append_token(&tokens, create_token(op, get_token_type(op)));
			i += 2;
			continue;
		}
		if (ft_strchr("><|()", input[i]))
		{
			char op[2] = {input[i], '\0'};
			append_token(&tokens, create_token(op, get_token_type(op)));
			i++;
			continue;
		}
		int start = i;
		while (input[i] && !isspace(input[i]) && !ft_strchr("><|()\"\'", input[i]))
			i++;
		char *word = ft_substr(input, start, i - start);
		append_token(&tokens, create_token(word, get_token_type(word)));
		free(word);
	}
	// handle_double_redirects(&tokens);
	mark_file_tokens(tokens);
	return tokens;
}

void parse(void)
{
	t_token *tokens;
	char	*input;

	input = read_input("minishell$ ");
	tokens = NULL;
	tokens = tokenize(input);
	mark_file_tokens(tokens);
	free(input);
	t_token *tmp = tokens;
	while(tmp)
	{
		printf("Value: %s\t ", tmp->value);
		print_type(tmp->type);
		tmp = tmp->next;
	}
	if (tokens->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", tokens->value);
		return;
	}
	error(tokens);
	error_pipe(tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:14:49 by mel-badd          #+#    #+#             */
/*   Updated: 2025/05/23 23:42:28 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	add_word(t_gc *gc, char *input, t_token **head, int i)
{
	int		start;
	char	*tmp;
	char	quote;
	t_token	*new_token;
	t_quote_type quote_type = NO_QUOTE;

	start = i;
	if (input[i] == '\'' || input[i] == '"')
	{
		quote = input[i++];
		if (quote == '\'')
			quote_type = SINGLE_QUOTE;
		else
			quote_type = DOUBLE_QUOTE;
		while (input[i] && input[i] != quote)
			i++;
		if (!input[i])
			return (ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2), -1);
		i++; // skip closing quote
	}
	else
	{
		while (input[i] && !ft_issspace(input[i]) && !redir_pipe(input[i]))
		{
			if (input[i] == '\'' || input[i] == '"')
			{
				quote = input[i++];
				if (quote == '\'')
					quote_type = SINGLE_QUOTE;
				else if (quote == '"' && quote_type != SINGLE_QUOTE)
					quote_type = DOUBLE_QUOTE;
				while (input[i] && input[i] != quote)
					i++;
				if (!input[i])
					return (ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2), -1);
				i++;
			}
			else
				i++;
		}
	}

	tmp = gc_substr(gc, input, start, i - start);
	if (!tmp)
		return (-1);

	new_token = create_token(gc, tmp, TOKEN_WORD);
	if (!new_token)
		return (-1);
	new_token->quote_type = quote_type;
	new_token->expand = (quote_type != SINGLE_QUOTE); // expand فقط إلا ماكانش single quote
	append_token(head, new_token);
	return (i);
}


static int	is_ambiguous(t_ctx *ctx, t_token *target)
{
	char	*expanded;

	expanded = NULL;
	if (target->value[0] == '$')
	{
		expand_heredoc(ctx, target);
		if (!expanded || ft_strcmp(expanded, "") == 0)
		{
			printf("minishell: %s: ambiguous redirect\n", target->value);
			return (1);
		}
	}
	return (0);
}

int	check_ambiguous_redirection(t_ctx *ctx, t_token *tokens)
{
	t_token	*cur;
	t_token	*target;

	cur = tokens;
	while (cur)
	{
		if (cur->type == TOKEN_REDIRECT_IN
			|| cur->type == TOKEN_REDIRECT_OUT
			|| cur->type == TOKEN_APPEND
			|| cur->type == TOKEN_HEREDOC)
		{
			target = cur->next;
			while (target && target->type == TOKEN_SPACE)
				target = target->next;
			if (target && target->type == TOKEN_FILE)
				if (is_ambiguous(ctx, target))
					return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	count_pipes(t_token *tokens, t_ctx *ctx)
{
	t_token	*cur;
	int		count;

	cur = tokens;
	count = 0;
	while (cur)
	{
		if (cur->type == TOKEN_PIPE)
			count++;
		cur = cur->next;
	}
	ctx->numcmd = count + 1;
	return (count);
}

t_token	*prepare_tokens(char *input, t_ctx *ctx, t_gc *gc, t_env *env)
{
	t_token	*tokens;
	int		i;

	i = 0;
	ctx->env = env;
	if (!input)
		return (NULL);
	tokens = tokenize2(gc, input);
	if (!tokens)
		return (NULL);
	i = count_pipes(tokens, ctx);
	if (i > 0)
		ctx->cmd->ex_status = 0;
	mark_file_tokens(tokens);
	if (!error(gc, tokens, ctx))
		return (NULL);
	ctx->gc = gc;
	if (!check_ambiguous_redirection(ctx, tokens))
		return (ctx->cmd->ex_status = 1, NULL);
	remove_quotes_token_list(gc, tokens);
	tokens = expand(ctx, tokens, ctx->cmd);
	if (!tokens)
		return (NULL);
	return (tokens);
}
// void print_type(t_type type)
// {
// 	switch (type)
// 	{
// 		case TOKEN_WORD:
// 			printf("WORD\n");
// 			break;
// 		case TOKEN_PIPE:
// 			printf("PIPE\n");
// 			break;
// 		case TOKEN_REDIRECT_IN:
// 			printf("REDIRECT_IN\n");
// 			break;
// 		case TOKEN_REDIRECT_OUT:
// 			printf("REDIRECT_OUT\n");
// 			break;
// 		case TOKEN_APPEND:
// 			printf("APPEND\n");
// 			break;
// 		case TOKEN_HEREDOC:
// 			printf("HEREDOC\n");
// 			break;
// 		case TOKEN_FILE:
// 			printf("FILE\n");
// 			break;
// 		case TOKEN_SPACE:
// 			printf("SPACE\n");
// 			break;
// 		default:
// 			printf("UNKNOWN TYPE\n");
// 			break;
// 	}
// }
t_cmd	*parse(t_gc *gc, t_env *env, t_heredoc *heredoc, t_cmd **cmd_1)
{
	t_token			*tokens;
	char			*input;
	char			*copy;
	t_cmd			*new_cmd;
	t_ctx			ctx;

	ctx.heredoc = heredoc;
	ctx.cmd = *cmd_1;
	input = read_input("minishell$ ");
	if (!input)
		return (NULL);
	if (g_sig == 1)
	{
		g_sig = 0;
		ctx.cmd->ex_status = 1;
	}
	copy = gc_malloc(gc, ft_strlen(input) + 1);
	if (!copy)
		return (NULL);
	(ft_strcpy(copy, input), free(input));
	tokens = prepare_tokens(copy, &ctx, gc, env);
	if (!tokens)
		return (gc_free_all(gc), NULL);
	new_cmd = joining2(gc, tokens);
	if (!new_cmd)
		return (gc_free_all(gc), NULL);
	new_cmd->ex_status = (*cmd_1)->ex_status;
	return (new_cmd);
}

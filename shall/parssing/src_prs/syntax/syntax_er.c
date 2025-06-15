/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_er.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:15:12 by mel-badd          #+#    #+#             */
/*   Updated: 2025/06/15 14:58:47 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_pipe_at_start(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error near unexpected token '%s'\n",
			tokens->value);
		return (0);
	}
	return (1);
}

int	handle_heredoc_logic(t_gc *gc, t_token *cur, t_ctx *ctx, int *res)
{
	if (cur->type == TOKEN_HEREDOC && cur->next
		&& cur->next->type != TOKEN_APPEND
		&& cur->next->type != TOKEN_HEREDOC)
	{
		ctx->heredoc->flag_heredoc = 1;
		if (!handle_heredoc(gc, cur, ctx))
		{
			*res = 1;
			return (0);
		}
		if (ctx->abort_cmd || g_sig)
			return (0);
		return (1);
	}
	return (0);
}

void	sanitize_heredocs(t_gc *gc, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "<<") == 0)
			tmp->value = gc_strdup(gc, "<");
		tmp = tmp->next;
	}
}

int	check_basic_errors(t_gc *gc, t_token *tokens, t_ctx *ctx, int *res)
{
	t_token	*cur;

	cur = tokens;
	if (!check_pipe_at_start(tokens))
		return (0);
	while (cur)
	{
		if (!error_pipe(tokens))
			return (0);
		if (handle_heredoc_logic(gc, cur, ctx, res))
		{
			cur = cur->next;
			continue ;
		}
		if (is_redir_syntax_err(cur))
		{
			printf("minishell: syntax error near unexpected token '%s'\n",
				cur->value);
			return (0);
		}
		if (!error2(cur))
			return (0);
		cur = cur->next;
	}
	return (1);
}

int	error(t_gc *gc, t_token *tokens, t_ctx *ctx)
{
	int	res;

	res = 0;
	if (!check_basic_errors(gc, tokens, ctx, &res))
	{
		ctx->cmd->ex_status = 258;
		return (0);
	}
	if (res == 1)
	{
		ctx->cmd->ex_status = 1;
		return (0);
	}
	sanitize_heredocs(gc, tokens);
	if (ctx->heredoc->flag_heredoc == 1)
	{
		printf("here\n");
		ctx->cmd->flag_status = 1;
		ctx->cmd->ex_status = 0;
	}
	return (1);
}

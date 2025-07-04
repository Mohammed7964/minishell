/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_er2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:17:04 by mel-badd          #+#    #+#             */
/*   Updated: 2025/06/15 14:43:30 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	handle_heredoc_parent(pid_t pid, int write_fd, t_ctx *ctx)
{
	int	status;

	waitpid(pid, &status, 0);
	close(write_fd);
	if (g_sig)
		return (0);
	close(ctx->heredoc->fd);
	ctx->heredoc->fd = open(ctx->heredoc->filename, O_RDONLY);
	if (ctx->heredoc->fd < 0)
		return (0);
	ctx->heredoc->flag_heredoc = 1;
	ctx->curr->type = TOKEN_REDIRECT_IN;
	if (ctx->delim->value)
		ctx->delim->value = ctx->heredoc->filename;
	return (1);
}

int	check_delim_validity(t_token *delim, t_heredoc *heredoc)
{
	if (!delim || delim->type != TOKEN_FILE)
	{
		heredoc->fd = -1;
		return (0);
	}
	return (1);
}

int	fork_and_handle(t_gc *gc, t_ctx *ctx)
{
	pid_t	pid;
	int		status;

	close(ctx->fd);
	ctx->fd = open_heredoc_file(gc, ctx->heredoc);
	if (ctx->fd < 0)
		return (0);
	g_sig = 0;
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(gc, ctx);
	else
	{
		signal(SIGINT, heredoc_sigint_main_handler);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(ctx->fd);
			g_sig = 1;
			return (0);
		}
		if (!handle_heredoc_parent(pid, ctx->fd, ctx))
		{
			close(ctx->fd);
			return (0);
		}
	}
	close(ctx->fd);
	return (1);
}

int	handle_heredoc(t_gc *gc, t_token *start, t_ctx *ctx)
{
	ctx->curr = start;
	while (ctx->curr)
	{
		if (ctx->curr->type == TOKEN_HEREDOC)
		{
			if (g_sig)
				return (0);
			ctx->delim = ctx->curr->next;
			if (!check_delim_validity(ctx->delim, ctx->heredoc))
				return (0);
			if (!fork_and_handle(gc, ctx))
				return (0);
			if (g_sig)
				return (0);
		}
		ctx->curr = ctx->curr->next;
	}
	return (1);
}

int	is_redir_syntax_err(t_token *cur)
{
	int	t;
	int	n;

	t = cur->type;
	n = -1;
	if (!cur->next)
		return (t == TOKEN_REDIRECT_IN || t == TOKEN_REDIRECT_OUT
			|| t == TOKEN_APPEND || t == TOKEN_HEREDOC);
	n = cur->next->type;
	if (t == TOKEN_PIPE && cur->next->type == TOKEN_PIPE)
		return (1);
	if (t == TOKEN_HEREDOC && !cur->next)
		return (1);
	if ((t == TOKEN_REDIRECT_IN || t == TOKEN_REDIRECT_OUT
			|| t == TOKEN_APPEND || t == TOKEN_HEREDOC)
		&& (n == TOKEN_REDIRECT_IN || n == TOKEN_REDIRECT_OUT
			|| n == TOKEN_APPEND || n == TOKEN_HEREDOC || n == TOKEN_PIPE))
		return (1);
	return (0);
}

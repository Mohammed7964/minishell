/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_er3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:19:04 by mel-badd          #+#    #+#             */
/*   Updated: 2025/06/15 05:51:21 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*handle_quoted_delim(t_gc *gc, char *raw, int n, int len)
{
	char	*d;
	int		rest_len;
	int		keep;

	keep = n - (n % 2);
	if (keep <= 0)
		return (gc_strdup(gc, raw + n));
	rest_len = len - n;
	d = gc_malloc(gc, keep + rest_len + 1);
	if (!d)
		return (NULL);
	ft_memset(d, '$', keep);
	ft_strncpy(d + keep, raw + n, rest_len + 1);
	return (d);
}

static char	*compute_heredoc_delim(t_gc *gc, char *raw, int b_flag)
{
	int		len;
	int		flag;
	int		n;

	flag = 0;
	n = count(raw, &flag, &b_flag);
	len = ft_strlen(raw);
	if (flag)
		return (handle_quoted_delim(gc, raw, n, len));
	return (raw);
}

void	handle_heredoc_child(t_gc *gc, t_ctx *ctx)
{
	t_ctx	input;
	char	*raw;
	char	*real_delim;
	char	*orig;
	int		b_flag ;

	b_flag = 0;
	signal(SIGINT, SIG_DFL);
	input.gc = gc;
	input.env = ctx->env;
	input.fd = ctx->fd;
	input.cmd = ctx->cmd;
	input.exit_status = ctx->cmd->ex_status;
	orig = gc_strdup(gc, ctx->delim->value);
	remove_quotes3_token(gc, ctx->delim, &b_flag);
	raw = ctx->delim->value;
	real_delim = compute_heredoc_delim(gc, raw, b_flag);
	input.delimeter = real_delim;
	input.expand_flag = !(ft_strchr(orig, '\'') || ft_strchr(orig, '"'));
	if (input.fd < 0)
		exit(1);
	read_and_write_heredoc(&input);
	exit(0);
}

void	read_and_write_heredoc(t_ctx *ctx)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (is_end_of_heredoc(line, ctx->delimeter))
		{
			free(line);
			break ;
		}
		if (should_expand_line(line, ctx->expand_flag))
			write_expanded_line(ctx, line);
		else
		{
			write(ctx->fd, line, ft_strlen(line));
			write(ctx->fd, "\n", 1);
		}
		free(line);
	}
}

int	open_heredoc_file(t_gc *gc, t_heredoc *heredoc)
{
	int	fd;

	heredoc->filename = make_heredoc_filename(gc);
	if (!heredoc->filename)
		return (-1);
	close(heredoc->fd);
	fd = open(heredoc->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell: heredoc");
		return (-1);
	}
	return (fd);
}

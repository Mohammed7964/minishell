/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:19:36 by mel-badd          #+#    #+#             */
/*   Updated: 2025/04/17 11:19:57 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	error_pipe(t_token *tokens)
{
	t_token *cur = tokens;

	while (cur)
	{
		if ((cur->type == TOKEN_PIPE && !cur->next) ||
			(cur->type == TOKEN_OR))
		{
			printf("minishell: syntax error near unexpected token '%s'\n", cur->value);
			return;
		}

		cur = cur->next;
	}
}

void error(t_token *tokens)
{
    t_token *cur = tokens;

    while (cur)
    {
		if ((cur->type == TOKEN_REDIRECT_OUT && !cur->next) ||
			(cur->type == TOKEN_REDIRECT_IN && !cur->next) ||
			(cur->type == TOKEN_APPEND && !cur->next) ||
			(cur->type == TOKEN_HEREDOC && !cur->next) ||
			(cur->type == TOKEN_APPEND && cur->next->type == TOKEN_REDIRECT_OUT) ||
			(cur->type == TOKEN_APPEND && cur->next->type == TOKEN_REDIRECT_IN) ||
			(cur->type == TOKEN_REDIRECT_IN && cur->next->type == TOKEN_APPEND) ||
			// (cur->type == TOKEN_HEREDOC && cur->next->type == TOKEN_REDIRECT_IN) ||
			(cur->type == TOKEN_HEREDOC && cur->next->type == TOKEN_HEREDOC) ||
			(cur->type == TOKEN_APPEND && cur->next->type == TOKEN_APPEND) ||
			(cur->type == TOKEN_REDIRECT_OUT && cur->next->type == TOKEN_REDIRECT_IN) ||
			(cur->type == TOKEN_REDIRECT_IN && cur->next->type == TOKEN_HEREDOC) ||
			(cur->type == TOKEN_REDIRECT_OUT && cur->next->type == TOKEN_HEREDOC) ||
			(cur->type == TOKEN_HEREDOC && cur->next->type == TOKEN_REDIRECT_OUT) ||
			(cur->type == TOKEN_REDIRECT_OUT && cur->next->type == TOKEN_REDIRECT_OUT) ||
			(cur->type == TOKEN_REDIRECT_IN && cur->next->type == TOKEN_REDIRECT_IN))
        {
            printf("minishell: syntax error near unexpected token '%s'\n", cur->value);
            return;
        }
        cur = cur->next;
    }
}

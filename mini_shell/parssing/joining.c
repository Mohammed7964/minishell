/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joining.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:33:09 by mel-badd          #+#    #+#             */
/*   Updated: 2025/04/17 11:42:36 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	joining(t_token *tokens)
{
	t_token *cur = tokens;
	t_cmd *word = NULL;

	while (cur)
	{
		if (cur->type == TOKEN_WORD && word)
		{
			word->cmd = ft_strjoin(word->cmd, cur->value);
			word->next = cur->next;
			free(cur->value);
			free(cur);
			cur = word->next;
		}
		else
		{
			word = cur;
			cur = cur->next;
		}
	}
}

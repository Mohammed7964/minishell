/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:58:43 by mel-badd          #+#    #+#             */
/*   Updated: 2025/06/15 17:20:47 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_escaped_quote(char *str, int i)
{
	return (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '"'
			|| str[i + 1] == '\\'));
}

int	handle_quoted_content(char *str, int i, char *res, int *j)
{
	char	quote;

	quote = str[i++];
	while (str[i] && str[i] != quote)
		res[(*j)++] = str[i++];
	if (str[i] == quote)
		i++;
	return (i);
}

void remove_quotes_token_list(t_gc *gc, t_token *tk)
{
	char *stripped;

	while (tk)
	{
		if (tk->value)
		{
			size_t len = ft_strlen(tk->value);
			if (len >= 2 && tk->value[0] == '\'' && tk->value[len - 1] == '\'')
			{
				tk->quote_type = SINGLE_QUOTE;
				tk->expand = 0; // لا توسعة داخل single quotes
			}
			else if (len >= 2 && tk->value[0] == '"' && tk->value[len - 1] == '"')
			{
				tk->quote_type = DOUBLE_QUOTE;
				tk->expand = 1; // توسعة داخل double quotes
			}
			else
			{
				tk->quote_type = NO_QUOTE;
				tk->expand = 1; // توسعة خارج quotes
			}
			stripped = strip_quotes(gc, tk->value);
			tk->value = stripped;
		}
		tk = tk->next;
	}
}




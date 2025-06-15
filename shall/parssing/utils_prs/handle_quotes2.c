/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 05:55:23 by mel-badd          #+#    #+#             */
/*   Updated: 2025/06/15 12:24:23 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	write_and_advance(char *res, char c, size_t *j)
{
	res[*j] = c;
	(*j)++;
	return (1);
}

static size_t	process_quote_logic(char *str, size_t i, char *res, size_t *j)
{
	if (is_empty_quotes(str, i) && str[i + 2] == ' ')
		return (write_and_advance(res, ' ', j) + 1);
	if (is_escaped_quote(str, i))
	{
		return (write_and_advance(res, str[i + 1], j) + 1);
	}
	if (str[i] == '\'' || str[i] == '"')
		return (handle_quoted_content(str, i, res, (int *)j) - i);
	return (write_and_advance(res, str[i], j));
}

char	*strip_quotes(t_gc *gc, char *str)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	advance;

	if (!str)
		return (NULL);
	res = gc_malloc(gc, ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		advance = process_quote_logic(str, i, res, &j);
		i += advance;
	}
	res[j] = '\0';
	return (res);
}

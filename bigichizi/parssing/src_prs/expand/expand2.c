/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:42:26 by mel-badd          #+#    #+#             */
/*   Updated: 2025/06/15 17:34:09 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*expand_value(t_ctx *ctx, char *value, t_cmd *cmd)
{
	t_dynstr	ds;
	char		*src;
	int			s;
	int			d;
	char		tmp[2];

	s = 0;
	d = 0;
	src = value;
	ctx->s = &s;
	ctx->d = &d;
	dyn_str_init(&ds);
		printf("src is -> %s\n", src);
	while (*src)
	{
		// if ((*src == '\'' && !(*ctx->d)) || (*src == '"' && !(*ctx->s)))
		// 	handle_quotes(ctx, *src++);
		if (*src == '$' && !(*ctx->s))
			handle_dollar(ctx, &src, &ds, cmd);
		else
		{
			tmp[0] = *src++;
			dyn_str_append(ctx->gc, &ds, tmp, 1);
		}
	}
	return (dyn_str_finalize(ctx->gc, &ds));
}

t_token	*add_expanded_tokens(t_gc *gc, char *value, t_token **cur)
{
	t_token	*new_tks;
	t_token	*next;

	new_tks = tokenize1(gc, value);
	while (new_tks)
	{
		next = new_tks->next;
		new_tks->next = NULL;
		*cur = new_tks;
		cur = &new_tks->next;
		new_tks = next;
	}
	return (*cur);
}
char *clean_input_before_expand(t_gc *gc, char *input)
{
    if (!input)
        return NULL;

    if (input[0] == '$' && ((input[1] == '"' && input[2] == '"') || (input[1] == '\'' && input[2] == '\'')))
    {
        // نرجعو نسخة جديدة من النص بلا $ الأول
        // يعني ندوزو فقط من input+1 (نمسحو $)
		printf("input is -> %s\n", input + 2);
        return gc_strdup(gc, input + 1);
    }
    // غير نرجعو النص كيف ما هو
    return gc_strdup(gc, input);
}

void	handle_expansion(t_ctx *ctx, t_token **cur, t_token *tk, t_cmd *cmd)
{
	char *cleaned_value = clean_input_before_expand(ctx->gc, tk->value);
	char	*exp;
	t_token	*tmp;
	t_token	*last;

	exp = expand_value(ctx, cleaned_value, cmd);
	printf("exp is -> %s\n", exp);
	tmp = tokenize1(ctx->gc, exp);
	last = *cur;
	while (tmp)
	{
		if (last)
			last->next = tmp;
		last = tmp;
		tmp = tmp->next;
	}
	*cur = last;
}
void print_type(t_type type)
{
	switch (type)
	{
		case TOKEN_WORD:
			printf("WORD\n");
			break;
		case TOKEN_PIPE:
			printf("PIPE\n");
			break;
		case TOKEN_REDIRECT_IN:
			printf("REDIRECT_IN\n");
			break;
		case TOKEN_REDIRECT_OUT:
			printf("REDIRECT_OUT\n");
			break;
		case TOKEN_APPEND:
			printf("APPEND\n");
			break;
		case TOKEN_HEREDOC:
			printf("HEREDOC\n");
			break;
		case TOKEN_FILE:
			printf("FILE\n");
			break;
		case TOKEN_SPACE:
			printf("SPACE\n");
			break;
		default:
			printf("UNKNOWN TYPE\n");
			break;
	}
}
t_token	*expand(t_ctx *ctx, t_token *tk, t_cmd *cmd)
{
	t_token	head;
	t_token	*cur;
	t_token	*next;

	head.next = NULL;
	cur = &head;
	while (tk)
	{
		next = tk->next;
		tk->next = NULL;
		if (tk->type == TOKEN_WORD && ft_strchr(tk->value, '$') && tk->expand)
		{
			handle_expansion(ctx, &cur, tk, cmd);
		}
		else
		{
			cur->next = tk;
			cur = cur->next;
		}
		tk = next;
	}
	return (head.next);
}

char	*append_to1_result1(t_gc *gc, char *result, char *str, size_t *total)
{
	size_t	len;
	char	*new_result;

	len = ft_strlen(str);
	new_result = gc_malloc(gc, *total + len + 1);
	if (!new_result)
		return (NULL);
	if (result)
		ft_memcpy(new_result, result, *total);
	ft_memcpy(new_result + *total, str, len);
	*total += len;
	new_result[*total] = '\0';
	free(result);
	return (new_result);
}

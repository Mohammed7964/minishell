/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 05:20:20 by mel-badd          #+#    #+#             */
/*   Updated: 2025/06/15 16:54:50 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	count_dolar(char **src)
{
	int	count;

	count = 0;
	while (**src == '$')
	{
		count++;
		(*src)++;
	}
	return (count);
}

static void	append_dollar_pairs(t_gc *gc, t_dynstr *ds, int count)
{
	int	pairs;

	if (count < 2)
		return ;
	pairs = count / 2;
	while (pairs-- > 0)
		dyn_str_append(gc, ds, "$", 1);
}

void	handle_dollar(t_ctx *ctx, char **src, t_dynstr *ds, t_cmd *cmd)
{
	int		count;
	char	*val;

	printf("here in handle_dollar with src: %s\n", *src);
	count = count_dolar(src);
	if (count == 1 && **src == '"')
		return ;
	append_dollar_pairs(ctx->gc, ds, count);
	if (count % 2 == 1)
	{
		if (**src && (ft_isalpha(**src) || **src == '_' || **src == '?'))
		{
			val = get_var_value(ctx->gc, src, ctx->env, cmd);
			if (val)
				dyn_str_append(ctx->gc, ds, val, ft_strlen(val));
		}
		else
			dyn_str_append(ctx->gc, ds, "$", 1);
	}
}

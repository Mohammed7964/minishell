/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:44:14 by mel-badd          #+#    #+#             */
/*   Updated: 2025/06/15 16:49:43 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	handle_quotes(t_ctx *ctx, char c)
{
	if (c == '\'' && !(*ctx->d))
	{
		if (*ctx->s)
			*ctx->s = 0;
		else
			*ctx->s = 1;
	}
	else if (c == '"' && !(*ctx->s))
	{
		if (*ctx->d)
			*ctx->d = 0;
		else
			*ctx->d = 1;
	}
}


char	*get_var_name(t_gc *gc, char **src)
{
	char	var[256];
	int		i;

	i = 0;
	if (**src == '?')
	{
		(*src)++;
		return (gc_strdup(gc, "?"));
	}
	while (**src && (ft_isalnum(**src) || **src == '_') && i < 255)
		var[i++] = *((*src)++);
	var[i] = '\0';
	if (!*var)
		return (NULL);
	return (gc_strdup(gc, var));
}

char	*get_var_value(t_gc *gc, char **src, t_env *env, t_cmd *cmd)
{
	char	*var;
	char	*val;

	var = get_var_name(gc, src);
	if (!var)
		return (NULL);
	if (ft_strcmp(var, "?") == 0)
	{
		return (gc_itoa(gc, cmd->ex_status));
	}
	val = find_env(env, var);
	return (gc_strdup(gc, val));
}

void	append_dollars(t_gc *gc, t_dynstr *ds, int count)
{
	while (count--)
		dyn_str_append(gc, ds, "$", 1);
}

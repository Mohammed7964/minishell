/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:59:21 by omaezzem          #+#    #+#             */
/*   Updated: 2025/06/12 11:10:25 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_invalid(char *invalid_str)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(invalid_str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	check_args(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (!ft_isalnum(args[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_var(t_env **env, char *var_name)
{
	t_env	*curr;
	t_env	*prev;
	t_env	*to_free;

	if (!env || !*env || !var_name)
		return ;
	prev = NULL;
	curr = *env;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->var, var_name) == 0)
		{
			to_free = curr;
			if (prev == NULL)
				*env = curr->next;
			else
				prev->next = curr->next;
			(free(to_free->var), free(to_free->val), free(to_free));
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void	remove_exp_var(t_exp **exp, char *var_name)
{
	t_exp	*curr;
	t_exp	*prev;
	t_exp	*to_free;

	if (!exp || !*exp || !var_name)
		return ;
	prev = NULL;
	curr = *exp;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->vr, var_name) == 0)
		{
			to_free = curr;
			if (prev == NULL)
				*exp = curr->next;
			else
				prev->next = curr->next;
			(free(to_free->vr), free(to_free->vl), free(to_free));
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(t_exp **exp, t_env **env, char **args)
{
	int	k;

	if (!args || len_arg(args) < 2)
		return (1);
	k = 1;
	while (args[k])
	{
		if (!args[k])
		{
			k++;
			continue ;
		}
		if (!check_args(args[k]))
			unset_invalid(args[k]);
		else
		{
			if (env)
				remove_env_var(env, args[k]);
			if (exp)
				remove_exp_var(exp, args[k]);
		}
		k++;
	}
	return (0);
}

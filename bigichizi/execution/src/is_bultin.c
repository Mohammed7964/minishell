/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bultin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 19:51:16 by omaezzem          #+#    #+#             */
/*   Updated: 2025/06/15 14:58:46 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_exit_status(int status, t_cmd *data)
{
	if (data->flg == 1)
		data->ex_status = 1;
	else if (WIFEXITED(status))
		data->ex_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->ex_status = 128 + WTERMSIG(status);
	else
		data->ex_status = 1;
	return (data->ex_status);
}

int	notpipe(t_cmd *data)
{
	if (!data || !data->cmd)
		return (0);
	if (!data->next)
		return (1);
	return (0);
}

int	ft_builtins(t_env **env, t_exp **exp, t_cmd *data, int herdcfd)
{
	if (data->files && data->redirection && notpipe(data))
		ft_do_redirections(data->files, data->redirection, herdcfd, data);
	if (ft_strcmp(data->cmd[0], "echo") == 0)
		return ((data->ex_status = ft_echo(&data->cmd[0])), 1);
	else if (ft_strcmp(data->cmd[0], "cd") == 0)
		return ((data->ex_status = ft_cd(*env, data->cmd, *exp)), 1);
	else if (ft_strcmp(data->cmd[0], "pwd") == 0)
		return (data->ex_status = ft_pwd(*env), 1);
	else if (ft_strcmp(data->cmd[0], "export") == 0)
		return (data->ex_status = ft_export(*exp, *env, data->cmd), 1);
	else if (ft_strcmp(data->cmd[0], "env") == 0)
		return (data->ex_status = builtin_env(env, data->cmd), 1);
	else if (ft_strcmp(data->cmd[0], "exit") == 0)
		return (ft_exit(data, data->cmd), 1);
	else if (ft_strcmp(data->cmd[0], "unset") == 0)
		return (data->ex_status = ft_unset(exp, env, data->cmd), 1);
	else
		return (0);
}

int	is_builtin(char *args)
{
	if (args)
	{
		if (!ft_strcmp(args, "echo")
			|| !ft_strcmp(args, "export")
			|| !ft_strcmp(args, "env")
			|| !ft_strcmp(args, "unset")
			|| !ft_strcmp(args, "exit")
			|| !ft_strcmp(args, "pwd")
			|| !ft_strcmp(args, "cd"))
			return (1);
	}
	return (0);
}

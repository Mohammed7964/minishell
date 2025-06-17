/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:17:45 by omaezzem          #+#    #+#             */
/*   Updated: 2025/06/15 17:10:39 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// Make sig volatile and use proper type for signal handling
int g_sig = 0;

char *read_input(char *prompt)
{
	char	*input;

	input = readline(prompt);
	if (!input)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (*input)
		add_history(input);
	return (input);
}

void sigint_handler(int sig_num)
{
	(void)sig_num;
	g_sig = 1;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	while_one(t_env **env, t_exp **exp, t_gc *gc, t_cmd **cmd)
{
	t_ctx   ctx;

	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		ctx.env = *env;
		ctx.exp = *exp;
		gc_init(gc);
		t_heredoc *heredoc = gc_malloc(gc, sizeof(t_heredoc));
		t_cmd *parsed_cmd = parse(gc, *env, heredoc, cmd);
		if (!parsed_cmd)
		{
			gc_free_all(gc);
			continue;
		}
		parsed_cmd->flag_status = (*cmd)->flag_status;
		ft_execute(&ctx, &parsed_cmd, (*cmd)->envp, heredoc);
		(*cmd)->ex_status = parsed_cmd->ex_status;
		dup2(STDERR_FILENO, STDOUT_FILENO);
		gc_free_all(gc);
	}
}

void    f()
{
	system("leaks minishell");
}

int main(int ac, char **av, char **envp)
{
	t_gc gc;
	t_cmd *cmd;
	t_env *env;
	t_exp *exp;

	(void)av;
	env = NULL;
	exp = NULL;
	cmd = NULL;
	if (ac > 1)
		return (write(2, "minishell: too many arguments\n", 31) ,1);
	env = ft_create_env(envp, &env);
	exp = ft_create_env_export(envp, &exp);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	cmd->ex_status = 0;
	cmd->flg = 0;
	cmd->envp = envp;
	while_one(&env, &exp, &gc, &cmd);
	free(cmd);
	ft_env_clear(&env);
	ft_exp_clear(&exp);
	return (0);
}

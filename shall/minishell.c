/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 11:17:45 by omaezzem          #+#    #+#             */
/*   Updated: 2025/06/15 15:44:05 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_sig;

char	*read_input(char *prompt)
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

static int	init_env(t_env **env, t_exp **exp, char **envp)
{
	t_exp	*head;

	head = NULL;
	*exp = head;
	*env = ft_create_env(envp, env);
	*exp = ft_create_env_export(envp, exp);
	return (0);
}

static void	setup_loop_signals_and_ctx(t_ctx *ctx, t_env *env,
	t_exp **exp, t_gc *gc)
{
	g_sig = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	ctx->env = env;
	ctx->exp = *exp;
	gc_init(gc);
}

static int	minishell_loop(t_ctx *ctx, t_gc *gc, t_env *env, t_exp **exp)
{
	t_cmd		*cmd;
	t_cmd		*parsed_cmd;
	t_heredoc	*heredoc;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	cmd->ex_status = 0;
	cmd->flg = 0;
	while (1)
	{
		setup_loop_signals_and_ctx(ctx, env, exp, gc);
		heredoc = gc_malloc(gc, sizeof(t_heredoc));
		parsed_cmd = parse(gc, env, heredoc, &cmd);
		if (!parsed_cmd)
		{
			gc_free_all(gc);
			continue ;
		}
		parsed_cmd->flag_status = cmd->flag_status;
		ft_execute(ctx, &parsed_cmd, NULL, heredoc);
		cmd->ex_status = parsed_cmd->ex_status;
		(dup2(STDERR_FILENO, STDOUT_FILENO), gc_free_all(gc));
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_ctx	ctx;
	t_gc	gc;
	t_env	*env;
	t_exp	*exp;

	(void)av;
	if (ac > 1)
		return (write(2, "minishell: too many arguments\n", 31), 1);
	init_env(&env, &exp, envp);
	minishell_loop(&ctx, &gc, env, &exp);
	ft_env_clear(&env);
	ft_exp_clear(&exp);
	return (0);
}

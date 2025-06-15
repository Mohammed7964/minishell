/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 05:08:53 by mel-badd          #+#    #+#             */
/*   Updated: 2025/06/15 05:11:13 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	heredoc_sigint_main_handler(int sig)
{
	(void)sig;
	g_sig = 1;
	write(1, "\n", 1);
}

void	heredoc_sigint_child_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	write(1, "\n", 1);
	exit(1);
}

int	check_status(int status)
{
	status = WEXITSTATUS(status);
	if (status == 1)
		return (7);
	return (0);
}

void	signals_heredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

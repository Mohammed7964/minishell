/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:09:44 by omaezzem          #+#    #+#             */
/*   Updated: 2025/06/13 20:45:23 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_len_redirections(char **redirections)
{
	int	i;

	i = 0;
	while (redirections[i])
	{
		i++;
	}
	return (i);
}

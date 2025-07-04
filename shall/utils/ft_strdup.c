/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:21:54 by omaezzem          #+#    #+#             */
/*   Updated: 2025/05/12 15:40:39 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup(char *s)
{
	int		i;
	char	*d;

	i = 0;
	d = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (d == NULL)
		return (0);
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
char *gc_strdup(t_gc *gc, char *s)
{
	int i = 0;
	char *d;

	if (s == NULL)
		return NULL;
	d = gc_malloc(gc, (ft_strlen(s) + 1) * sizeof(char));
	if (d == NULL)
		return NULL;
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return d;
}

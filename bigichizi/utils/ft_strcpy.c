/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-badd <mel-badd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:53:37 by mel-badd          #+#    #+#             */
/*   Updated: 2025/06/14 20:54:16 by mel-badd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *ft_strcpy(char *s1, char *s2)
{
      int i;

      i = 0;
      while (s2[i])
      {
          s1[i] = s2[i]; // so this will make s1 = to whatever s2 is looping through the string
          i++;
      }
      s1[i] = s2[i];  // now that we are finsihing looping though s1[i] will equal s2[i]
      return (s1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorig <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:33:00 by cdorig            #+#    #+#             */
/*   Updated: 2025/02/13 15:33:00 by cdorig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Extract the variable name from the command
 *
 * @param str The command
 * @return char* The variable name
 */
char	*extract_var(char *str, t_data *data)
{
	int		i;
	char	*var;

	i = 0;
	while (str[i] == '=')
		i++;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (str[i] == '+')
		i++;
	var = ft_substr(str, 0, ++i);
	if (!var)
		clean_exit(data, "Malloc: var_utils:33", 2, EXIT_FAILURE);
	return (var);
}

/**
 * @brief Extract the content from the command
 *
 * @param str The command
 * @return char* The content
 */
char	*extract_content(char *str, char *var, t_data *data)
{
	int		i;
	char	*content;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (str[i] == '+')
		i++;
	if (i == (int)ft_strlen(str))
		content = ft_strdup("");
	else
		content = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	if (!content)
	{
		free_and_null(var);
		clean_exit(data, "Malloc: var_utils:60", 2, EXIT_FAILURE);
	}
	return (content);
}

/**
 * @brief Trim the plus sign from the variable name
 *
 * @param var The variable name
 * @return char* The trimmed variable name
 */
char	*trim_plus(char *var, char *content, t_data *data)
{
	int		i;
	char	*tmp;
	char	*new;

	i = 0;
	while (var[i] && var[i] != '+')
		i++;
	tmp = ft_substr(var, 0, i);
	free_and_null(var);
	if (!tmp)
	{
		free_and_null(content);
		clean_exit(data, "Malloc: var_utils:85", 2, EXIT_FAILURE);
	}
	new = ft_strjoin(tmp, "=");
	free_and_null(tmp);
	if (!new)
	{
		free_and_null(content);
		clean_exit(data, "Malloc: var_utils:92", 2, EXIT_FAILURE);
	}
	return (new);
}

/**
 * @brief Join the existing content with the new content
 *
 * @param var The variable name
 * @param content The new content
 * @return char* The new content
 */
char	*join_content(char *var, char *content, t_data *data)
{
	char	*existing;
	char	*new;
	int		pos;

	pos = find_env_var(var, data->env);
	if (pos == get_env_len(data->env))
		return (content);
	existing = ft_strtrim(data->env[pos], var);
	if (!existing)
	{
		free_and_null(var);
		free_and_null(content);
		clean_exit(data, "Malloc: var_utils:115", 2, EXIT_FAILURE);
	}
	new = ft_strjoin(existing, content);
	free_and_null(existing);
	free_and_null(content);
	if (!new)
	{
		free_and_null(var);
		clean_exit(data, "Malloc: var_utils:123", 2, EXIT_FAILURE);
	}
	return (new);
}

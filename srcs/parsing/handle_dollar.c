/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:34:01 by jbarbey           #+#    #+#             */
/*   Updated: 2025/01/28 21:12:30 by jbarbey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Get the environement variable name found after a dollar sign
 *
 * @param t A pointer to the first character after the dollar sign
 * @param ret A pointer in which to store the potential variable name
 * @return int Returns 0 on success and 1 on fail
 */
static int	get_potential_env_var(char *t, char **ret)
{
	char	*start;

	if (*t == '?')
		*ret = ft_substr(t, 0, 1);
	else
	{
		start = t;
		while (*t && (ft_isalnum(*t) || *t == '_'))
			t++;
		*ret = ft_substr(start, 0, t - start);
	}
	if (!*ret)
		return (1);
	return (0);
}

/**
 * @brief Modified version of the function used during initialization
 *
 * @param i A pointer in which to store the found index
 * @param var The string to search for in the env
 * @param enp The env
 * @return int Returns 0 or positive value on success and -1 on fail
 */
static int	mod_find_env_var(int *i, char *var, char **enp)
{
	int	v_l;

	*i = 0;
	v_l = ft_strlen(var);
	while (enp[*i])
	{
		if (!ft_strncmp(enp[*i], var, v_l) && enp[*i][v_l] == '=')
			return (*i);
		(*i)++;
	}
	return (-1);
}

/**
 * @brief Get the content of the env variable
 *
 * @param ret A pointer to store the content in
 * @param to_f Old ret string to free
 * @param enp The env
 * @param err The value of the last exit code passed throuh itoa
 * @return int Returns 0 on success and 1 on fail
 */
static int	get_env_var_content(char **ret, char *to_f, char **enp, char *err)
{
	int		i;
	int		j;

	if (**ret == '?' && err)
		*ret = ft_substr(err, 0, ft_strlen(err));
	else if (mod_find_env_var(&i, *ret, enp) != -1)
	{
		j = 0;
		while (enp[i][j] && enp[i][j] != '=')
			j++;
		j++;
		*ret = ft_strdup(&enp[i][j]);
	}
	else
		*ret = ft_strdup("");
	free_and_null(to_f);
	if (err)
		free_and_null(err);
	if (!*ret)
		return (1);
	return (0);
}

/**
 * @brief Replace the dollar sign + variable name in string by it's content
 *
 * @param s Old string to store result in
 * @param s2 Content to replace dollar sign with
 * @param s3 Pointer to the first character after the variable name
 * @return int Returns 0 on success and 1 on fail
 */
static int	replace_dollar_with_content(char **s, char *s2, char *s3)
{
	char	*ret;
	char	*t;

	if (*s3 == '?')
		s3++;
	else
	{
		while (*s3 && (ft_isalnum(*s3) || *s3 == '_'))
			s3++;
	}
	ret = ft_strjoin(*s, s2);
	free_and_null(s2);
	if (!ret)
		return (1);
	t = ret;
	ret = ft_strjoin(ret, s3);
	free_and_null(t);
	if (!ret)
		return (1);
	free_and_null(*s);
	*s = ret;
	return (0);
}

/**
 * @brief Handles the dollar sign and replaces it by relevant content
 *
 * @param word The command array
 * @param enp The env
 * @return int Returns 0 on success and 1 on fail
 */
int	handle_dollar(char **word, char **enp)
{
	char	*t;
	char	*ret;

	t = ft_strchr(*word, '$');
	while (t && (is_in_single_quotes(*word, t)
			|| (!ft_isalpha(*(t + 1)) && *(t + 1) != '_' && *(t + 1) != '?')))
		t = ft_strchr(t + 1, '$');
	if (t)
	{
		if (get_potential_env_var(t + 1, &ret))
			return (1);
		if (get_env_var_content(&ret, ret, enp, ft_itoa(getset_exit_code(-1))))
			return (1);
		*t = '\0';
		if (replace_dollar_with_content(word, ret, t + 1))
			return (1);
		handle_dollar(word, enp);
	}
	return (0);
}

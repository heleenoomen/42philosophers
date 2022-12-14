/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:45:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/13 18:43:03 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* allocates size bytes of memory on the heap. If allocation fails, sets
 * error to MALLOC_ERR. Returns a pointer to the allocated block
 */
void	*malloc_set_err(size_t size, t_err *error)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		*error = MALLOC_ERR;
	return (ret);
}

/* helper function for ft_atoui. Returns true if, for some reason, error was
 * already set. Returns also true when there is an obvious error: the string
 * is a NULL string or is empty, or starts with '0' (numbers with leading
 * zeros are not accepted). Returns false if no obvious error is found
 */
static bool	ph_atoui_check_error(char *s, t_err *error, short type)
{
	if (*error)
		return (true);
	if (s == NULL || s[0] == '\0' || (s[0] == '0' && s[1] != '\0'))
	{
		if (type == N_PH)
			*error = INV_PH;
		else if (type == N_MEALS)
			*error = INV_ME;
		else
			*error = INV_TIME;
		return (true);
	}
	return (false);
}

/* converts string to unsigned int. Sets error when there is an obvious
 * error (check_error returns true), when any non numeric characters are found
 * or when the number is too high (higher than INT_MAX, or higher than PH_MAX
 * for the number of philosophers).
 */
unsigned int	ph_atoui(char *s, t_err *error, short type)
{
	unsigned int	nbr;
	bool			inv;

	if (ph_atoui_check_error(s, error, type))
		return (0);
	nbr = 0;
	inv = false;
	while (*s)
	{
		if ((*s < '0' || *s > '9'))
			inv = true;
		nbr = (10 * nbr) + *s - '0';
		if (type == N_PH && (inv || nbr > PH_MAX))
			*error = INV_PH;
		else if (type == N_MEALS && (inv || nbr > INT_MAX))
			*error = INV_ME;
		else if ((inv || nbr > INT_MAX))
			*error = INV_TIME;
		if (*error)
			return (0);
		s++;
	}
	return (nbr);
}

/* returns 0 if both strings are equal, returns the difference between the
 * first non equal character otherwise (s1[n] - s2[n] or s2[n] - s1[n])
 * returns 0 if both strings are NULL.
 */
int	my_strcmp(char *s1, char *s2)
{
	int	i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return (0 - *s2);
	if (s2 == NULL)
		return (*s1);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

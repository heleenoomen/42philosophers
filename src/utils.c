/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:45:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/07 12:38:51 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t size, t_err *error)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		*error = MALLOC_ERR; 
	return (ret);
}


unsigned int	ft_atoui(char *s, t_err *error, short type)
{
	unsigned long int	nbr;
	bool				inv;

	if (*error)
		return (0);
	nbr = 0;
	inv = false;
	while (*s)
	{
		if ((*s < '0' || *s > '9'))
			inv = true;
		nbr = (10 * nbr) + *s - '0';
		if (type == PH && (inv || nbr > PH_MAX))
			*error = INV_PH;
		else if (type == ME && (inv || nbr > INT_MAX))
			*error = INV_ME;
		else if ((inv || nbr > UINT_MAX))
			*error = INV_TIME;
		if (*error)
			return (0);
		s++;
	}
	return ((unsigned int) nbr);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

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


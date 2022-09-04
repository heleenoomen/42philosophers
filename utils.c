/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 09:45:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/04 10:58:22 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t size, char *error)
{
	void	*ret;

	ret = malloc(size);
	if (ret == NULL)
		error = MALLOC_ERR; 
	return (ret);
}

unsigned int	ft_atoui(char *s, char *error, short type)
{
	unsigned long int	nbr;
	bool				inv;

	if (error)
		return (0);
	nbr = 0;
	inv = false;
	while (*s)
	{
		if ((*s < '0' || *s > '9'))
			inv = true;
		nbr = (10 * nbr) + *s - '0';
		if (type == PH && (inv || nbr > PH_MAX))
			error = INV_PH;
		else if (type == ME && (inv || nbr > INT_MAX))
			error = INV_ME;
		else if ((inv || nbr > UINT_MAX))
			error = INV_T;
		if (error)
			return (0);
		s++;
	}
	return ((unsigned int) nbr);
}


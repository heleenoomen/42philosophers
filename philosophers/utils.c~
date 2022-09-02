/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 utils.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: hoomen <hoomen@student.42heilbronn.de>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2022/09/01 14:54:21 by hoomen			   #+#	  #+#			  */
/*	 Updated: 2022/09/01 14:59:57 by hoomen			  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "philo.h"

/* mark U (utils) */

/* returns the lenght of a string s
 * terminating nul byte is not counted
 * returns 0 for NULL string
 */
size_t	ft_strlen(char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

/* writes string s to filedescriptor fd
 * does nothing if s is a NULL string
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(fd));
}

/* writes an error message to standard error
 * returns with ret value
 */
int	putstr_return(char *message, int ret)
{
	ft_putstr_fd(message, 2);
	return (ret);
}

/* converts a string to a signed long integer of positive
 * value.
 * returns -1 when s contains non numeric characters
 * returns -1 as well when nbr overflows long int max
 */
long	ft_atoul(char *s)
{
	long	nbr;

	nbr = 0;
	while (s)
	{
		if (*s < '0' || *s > '9')
			return (-1);
		nbr = (nbr * 10) + *s - '0';
		if (nbr < 0)
			return (-1);
		s++;
	}
	return (nbr);
}



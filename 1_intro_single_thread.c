#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


/* nb, compile with -pthread
 */

/* a thread executes a function. In this case a very simple function, "routine"
 */
 
void	*routine()
{
	printf("Test from threads\n");
	return (NULL);
}


/* int	pthread_create(pthread_t *newthread, const_pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
 * 2nd argument is attributes for the thread. You can pass NULL if no attributes and it sets it up with default
 * attribute.
 * 3rd argument is pointer to function
 * 4th argument is the arguments passed to the routine
 */

/* wait for thread to finish its execution
 * pthread_join(pthread_t thread, void **thread_result)
 * this is the wait function for threads.
 * 2nd argument stores the result of the thread. You can pass NULL if it is not of interest
 */

int	main(int argc, char *argv[])
{
	pthread_t	t1;  /*place where API can store info about the thread*/

	pthread_create(&t1, NULL, &routine, NULL); 
	pthread_join(t1, NULL);
	return (0);
}


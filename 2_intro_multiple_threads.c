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
	sleep(3); 						/*with this test you can see that the threads run in parallel */
	printf("Ending thread\n"); 
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	t1;  /*place where API can store info about the thread*/
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
	{
	   return 1 ;	/* error checking. On linux for example, it is possible to prevent
													   programs from creating threads */
	}
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
	   return 2;	
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	return (0);
}


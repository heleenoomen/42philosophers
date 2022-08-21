#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* two threads that listen for mail from all over the globe */
int	mails = 0;

/* mutex: a lock. */
int	lock = 0;

/* one way to try to protect our program form race conditions would be something like this: */
//void	*routine()
//{
//	for (int i = 0; i < 100000; i++) 
//	{
//		while (lock == 1);  // check if lock is locked and wait until it is unlocked //
//		lock = 1; 			// lock it again while we are busy //
//		mails++;			
//		lock = 0;			// unlock at the end
//	}
//	return (NULL);
//}

/* BUT: Posix thread has already something implemented that is much safer than this method! */

pthread_mutex_t	mutex; /* before using, this has to be initialized */

void	*routine()
{
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	t1;
	pthread_t	t2;
	
	pthread_mutex_init(&mutex, NULL); /* it takes a pointer to the pthread_mutex variable an attributes. NULL
										gives the default attributes. This function allocates memory that you
									   	have to free with pthread_mutex_destroy at the end	*/
	if (pthread_create(&t1, NULL, (void *)&routine, NULL) != 0)
	{
	   return 1 ;	
	}
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
	   return 2;	
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	printf("Number of mails: %d\n", mails);
	pthread_mutex_destroy(&mutex); /* free the memory the pthread_mutex_init has allocated */
	return (0);
}

/* locking and unlocking with mutexes is protecting operations from other threads executing at the same time 
 * No one can execute the "mail++" line of code because there is a mutex around it.
 * This same code also works with more (3, 4, 5 etc.) threads 
 *
 * Mutexes slow down the program (because other threads have to wait) and if you protect everything with mutexes
 * it makes no sense, you might as well have used just one single thread!
 * 
 * Race conditions will only occur on multi core processors. (On single core they are very very rare).
 *


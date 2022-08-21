#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* two threads that listen for mail from all over the globe */
int	mails = 0;

void	*routine()
{
	for (int i = 0; i < 100000; i++) /* for big numbers, this will not add up! So here we got out: 113030
										instead of the expected 200.000 */
		mails++;
		/* behind the scenes: read the value in mails,
		 * 						increment the value
		 * 						write it back to memory
		 *
		 * 						these are the three operations being done
		 */ 						
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
	printf("Number of mails: %d\n", mails);
	return (0);
}


/* mails incrementation behind the scenes:
 *					t1	t2
 * //read mails		23	24
 * //increment		23	24
 * //write mails	24	25
 *
 * this is the expected behavior. But:
 * 					t1	t2
 * //read mails		29	23  >> while t2 was paused after reading the value, t1 incremented 6 times 
 * //increment		29	24		before t2 resumes. Now we go back from 30 to 24!
 * //write mails	30	24		now correct results are not guaranteed anymore.
 *
 *
 * // you can use gcc -S to make the assembly code. For the routine it will look something like this:
 *
 * 		.L3:
 * 			movl	mails(%rip), %eax	>>	movl means move. From memory to eax, that is a cpu register
 * 			addl	$1, %eax			>>	add one				
 * 			movl	%eax, mails(%rip)	>>	move the value back to where it belongs
 * 			addl	$1, -4(%rbp)
 *
 * // so three operations for one variable incrementation "mails++" !
 *
 * This creates so called "race conditions". They happen more when there are a lot of iterations per thread.
 * This is because, between the creation of the first thread and the second thread, small numbers of iterations
 * are going to be finished already. But they can happen always, when some thread get paused for some reason. 

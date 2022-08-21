#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/* both run in parallel (or can run in parallel) */

/* threads happen within the same process, they share the same address space and have access
 * to the same variables */

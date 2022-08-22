#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	printf("size_t = %lu\n", sizeof(size_t));
	printf("ulong  = %lu\n", sizeof(unsigned long));
	printf("size_t max = %lu\n", (size_t) -1);
	printf("ulong max = %lu\n", (unsigned long) -1);
	return (0);
}

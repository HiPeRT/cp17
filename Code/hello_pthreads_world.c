#include <stdio.h>
#include <pthread.h>

#define NTHREADS 16

void * fun(void * arg)
{
	printf("Hello World!\n");
} //  pthread_end called implicitly

int main()
{
	pthread_t myid[NTHREADS];
	pthread_attr_t attr;
	void * retval;
	int i;
	
	for (i=0; i<NTHREADS; i++)
	{
		pthread_attr_init(&attr);
		pthread_create(
			&myid[i],
			&attr,
			fun,
			(void *) 0x0
			);
		pthread_attr_destroy(&attr);
	}
		
	// Join...
	for (i=0; i<NTHREADS; i++)
		pthread_join(myid[i], &retval);
	
	return 0;
}

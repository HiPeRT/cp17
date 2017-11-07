#include <stdio.h>
#include <omp.h>

int main()
{
	int myid = omp_get_thread_num();
	int thrdnum = omp_get_num_threads();
	printf("Hello sequential world! I am Thread #%d out of %d\n", myid, thrdnum);
	
	# In bash:
	# $ export OMP_NUM_THREADS=16
	omp_set_num_threads(64);
	
	#pragma omp parallel num_threads(8)
	{
		// These will interleave on stdout
		printf("Hello parallel world!\n");
		printf("I am Thread #%d out of %d\n", omp_get_thread_num(), omp_get_num_threads());
		
		// This won't
		//printf("Hello parallel world! I am Thread #%d out of %d\n", omp_get_thread_num(), omp_get_num_threads());
		
	} // end of parreg
	
	printf("Hello sequential world! I am Thread #%d out of %d\n", myid, thrdnum);
	
	return 0;
}

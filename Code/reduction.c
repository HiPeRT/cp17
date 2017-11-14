#include <stdio.h>
#include <omp.h>


int main()
{
	int a = 11;
	
	printf("\n[Thread %d] Before parreg: a is %d\n\n", omp_get_thread_num(), a);
	
	#pragma omp parallel reduction(+:a) num_threads(4)
	{
		a += 2;
		printf("[Thread %d] Inside parreg: a is %d\n", omp_get_thread_num(), a);
	}
	
	printf("\n[Thread %d] After parreg: a is %d\n\n", omp_get_thread_num(), a);
	
	return 0;
}
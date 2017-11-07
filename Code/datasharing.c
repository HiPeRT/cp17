#include <stdio.h>
#include <omp.h>

int main()
{
	int a = 1, b = 2, c = 3;
	
	printf("\n[Thread %d] Before parreg: a is %d, b is %d, c is %d\n\n", omp_get_thread_num(), a, b, c);
	
	#pragma omp parallel num_threads(4) firstprivate(a) private(b) shared(c)
	{
		int myid = omp_get_thread_num();
		if(myid == 0)
		{
			a = 4;
			b = 5;
			c = 6;
		}
				
		printf("[Thread %d] Inside parreg: a is %d, b is %d, c is %d\n", myid, a, b, c);
	}
	
	printf("\n[Thread %d] After parreg: a is %d, b is %d, c is %d\n\n", omp_get_thread_num(), a, b, c);
	
	return 0;
}
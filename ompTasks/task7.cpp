#include <iostream>
#include <omp.h>

int main7()
{
	srand(time(0));
	int a[12], b[12], c[12];

	omp_set_num_threads(3);

#pragma omp parallel for schedule(static,3)
	for (int i = 0; i < 12; i++)
	{
		a[i] = rand() % 10 + 1;
		b[i] = rand() % 10 + 1;
		printf("iter = %d, thread id = %d out of %d b[%d] = %d a[%d] = %d \n", i, omp_get_thread_num(), omp_get_num_threads(), i, b[i], i, a[i]);
	}


	omp_set_num_threads(4);
#pragma omp parallel for schedule(dynamic,2)
	for (int i = 0; i < 12; i++)
	{
		c[i] = a[i] + b[i];
		printf("iter = %d, thread id = %d, out of %d c[%d] = %d\n", i, omp_get_thread_num(), omp_get_num_threads(), i, c[i]);
	}

    return EXIT_SUCCESS;
}

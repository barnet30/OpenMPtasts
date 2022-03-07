#include <iostream>
#include <omp.h>

int main1()
{
	omp_set_num_threads(8);
#pragma omp parallel
	{
		printf("id = %d out of %d Hello world!\n", omp_get_thread_num(), omp_get_num_threads());
	}

	return EXIT_SUCCESS;
}

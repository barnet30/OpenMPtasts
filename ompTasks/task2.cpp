#include <iostream>
#include <omp.h>

int main2()
{
    omp_set_num_threads(3);

#pragma omp parallel if(omp_get_max_threads() > 2)
    {
        printf("id thread = %d, out of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    omp_set_num_threads(2);

#pragma omp parallel if(omp_get_max_threads() > 2)
    {
        printf("id thread = %d, out of %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

	return EXIT_SUCCESS;
}

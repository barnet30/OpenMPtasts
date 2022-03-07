#include <iostream>
#include <omp.h>

int main3()
{
    int a = 0, b = 0;
    printf("before first area: a = %d, b = %d;\n", a, b);

#pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        a = 0;
        a += omp_get_thread_num();
        b += omp_get_thread_num();
        printf("in first area:  %d thread, a = %d, b = %d\n", omp_get_thread_num(), a, b);
    }
    printf("after fisrt area: a = %d, b = %d\n", a, b);
#pragma omp parallel num_threads(4) shared(a) private(b)
    {
        b = 0;
        a -= omp_get_thread_num();
        b -= omp_get_thread_num();
        printf("in second area:  %d, a = %d, b = %d\n", omp_get_thread_num(), a, b);
    }
    printf("after second area: a = %d, b = %d\n", a, b);

    return EXIT_SUCCESS;
}

#include <iostream>
#include <omp.h>

int main6()
{
    srand(time(0));
    int a[100];

    for (int i = 0; i < 100; ++i)
    {
        a[i] = rand() % 100 + 1;
    }

    double avg = 0;
#pragma omp parallel for reduction(+:avg)
    for (int i = 0; i < 100; i++) {
        avg += a[i];
    }

    avg /= 100;
    printf("with reduction average = %.2lf\n", avg);

    //without reduction we writing into avg, without atomic operation. Threads might rewrite value, which changed in order thread. it`s dangerous operation.
    //reduction save operation, because operator(+) will be execute atfer for directive.

#pragma omp parallel for 
    for (int i = 0; i < 100; i++) {
        avg += a[i];
    }

    avg /= 100;
    printf("average = %.2lf\n", avg);

	return EXIT_SUCCESS;
}

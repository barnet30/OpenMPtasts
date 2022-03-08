#include <iostream>
#include <omp.h>

#define PRINT printf("id = %d out of %d Hello world!\n", omp_get_thread_num(), omp_get_num_threads());

void method1()
{
    printf("Method 1\n");
#pragma omp parallel
	{
#pragma omp barrier
        {
            if (omp_get_thread_num() == 7)
                PRINT
        }
#pragma omp barrier
        {
            if (omp_get_thread_num() == 6)
                PRINT
        }
#pragma omp barrier
        {
            if (omp_get_thread_num() == 5)
                PRINT
        }
#pragma omp barrier
        {
            if (omp_get_thread_num() == 4)
                PRINT
        }
#pragma omp barrier
        {
            if (omp_get_thread_num() == 3)
                PRINT
        }
#pragma omp barrier
        {
            if (omp_get_thread_num() == 2)
                PRINT
        }
#pragma omp barrier
        {
            if (omp_get_thread_num() == 1)
                PRINT
        }
#pragma omp barrier
        {
            if (omp_get_thread_num() == 0)
                PRINT
        }
	}
    return;
}

void method2()
{
    printf("Method 2\n");
    int i;
#pragma omp parallel private (i)
    {
#pragma omp for ordered 
        for (i = 7; i >= 0; i--)
        {
#pragma omp ordered 
            {
                printf("id = %d out of %d Hello world!\n", 7 - omp_get_thread_num(), omp_get_num_threads());
            }
        }
    }
}

void method3()
{
    printf("Method 3\n");
#pragma omp parallel 
    {
        int n = omp_get_num_threads();
        for (int i = 7; i >= 0; i--)
        {
#pragma omp barrier
            {
                if (i == omp_get_thread_num())
                {
#pragma omp critical
                    PRINT
                }
            }
        }
    }
    return;
}

void method4()
{
    printf("Method 4\n");
    int i = 7;
#pragma omp parallel 
    {
        bool check = true;
        while (check)
        {
            if (omp_get_thread_num() == i)
#pragma parallel critical
            {
                PRINT
                --i;
            }
            if (i < 0)
                check = false;
        }
    }
}

void method5()
{
    printf("Method 5\n");
    omp_lock_t my_lock;


    omp_init_lock(&my_lock);
    int i = 7;
#pragma omp parallel shared(my_lock, i)
    {
        while (i != -1) {

            omp_set_lock(&my_lock);
            if (omp_get_thread_num() == i)
            {
#pragma omp critical
                {
                    PRINT
                    --i;
                }
            }
            omp_unset_lock(&my_lock);
        }
    }
    omp_destroy_lock(&my_lock);
    return;
}

int main()
{
	omp_set_num_threads(8);
    method1();
    method2();
    method3();
    method4();
    method5();

	return EXIT_SUCCESS;
}

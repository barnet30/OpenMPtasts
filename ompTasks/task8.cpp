#include <iostream>
#include <omp.h>


const int arr_size = 16000;

int a[arr_size];
double b[arr_size];

double parallel_for_schedule_static(int chunk_size)
{

    double start_time, end_time;
    start_time = omp_get_wtime();

#pragma omp parallel for schedule(static, chunk_size)              
    for (int i = 0; i < arr_size; ++i)
    {
        a[i] = double(i + 1);
    }
#pragma omp parallel for schedule(static, chunk_size)              
    for (int i = 1; i < arr_size - 1; ++i)
    {
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
    }

    end_time = omp_get_wtime();
    return end_time - start_time;

}


double parallel_for_schedule_dynamic(int chunk_size)
{

    double start_time, end_time;
    start_time = omp_get_wtime();

#pragma omp parallel for schedule(dynamic, chunk_size)              
    for (int i = 0; i < arr_size; ++i)
    {
        a[i] = double(i + 1);
    }
#pragma omp parallel for schedule(dynamic, chunk_size)              
    for (int i = 1; i < arr_size - 1; ++i)
    {
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
    }

    end_time = omp_get_wtime();
    return end_time - start_time;

}

double parallel_for_schedule_guided(int chunk_size)
{
    double start_time, end_time;
    start_time = omp_get_wtime();

#pragma omp parallel for schedule(guided, chunk_size)              
    for (int i = 0; i < arr_size; ++i)
    {
        a[i] = double(i + 1);
    }
#pragma omp parallel for schedule(guided, chunk_size)              
    for (int i = 1; i < arr_size - 1; ++i)
    {
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
    }

    end_time = omp_get_wtime();
    return end_time - start_time;

}

double parallel_for_schedule_runtime()
{
    double start_time, end_time;
    start_time = omp_get_wtime();

#pragma omp parallel for schedule(runtime)              
    for (int i = 0; i < arr_size; ++i)
    {
        a[i] = double(i + 1);
    }
#pragma omp parallel for schedule(runtime)              
    for (int i = 1; i < arr_size - 1; ++i)
    {
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
    }

    end_time = omp_get_wtime();
    return end_time - start_time;

}

int main8()
{
    omp_set_num_threads(8);
   	srand(time(0));

    int chunk_size;
    for (chunk_size = 1; chunk_size < 100;chunk_size += 1)
    {
        printf("STATIC, chunk size = %d, time: %.4f msec\n", chunk_size, 1000 * parallel_for_schedule_static(chunk_size));
        printf("DYNAMIC, chunk size = %d, time: %.4f msec\n", chunk_size, 1000 * parallel_for_schedule_dynamic(chunk_size));
        printf("GUIDED, chunk size = %d, time: %.4f msec\n", chunk_size, 1000 * parallel_for_schedule_guided(chunk_size));
        printf("RUNTIME, chunk size = %d, time: %.4f msec\n\n", chunk_size, 1000 * parallel_for_schedule_runtime());
    }
    

	return EXIT_SUCCESS;
}

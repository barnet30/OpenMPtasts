#include <iostream>
#include <omp.h>

const int better_time_const = INT_MAX;
const int max_chunk_size = 20;
const int chunk_step = 4;
const int matrix_size_const = 200;
const int matrix_step = 20;

static int matrix_size_barrier = 0;
static bool matrix_value_barrier_has_value = false;

double Mult_Matrix_Vector(int** matr, int* vec, int n, int* res) {
    res = new int[n];
    double start_time, end_time;
    start_time = omp_get_wtime();

    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
        for (int j = 0; j < n; j++)
            res[i] += matr[i][j] * vec[j];
    }
    end_time = omp_get_wtime();
    return end_time - start_time;
}

double Mult_Matrix_Vector_Parallel_Static(int** matr, int* vec, int n, int* res, int chunk_size) {
    res = new int[n];
    double start_time, end_time;
    start_time = omp_get_wtime();

#pragma omp parallel for schedule(static,chunk_size)
    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
        for (int j = 0; j < n; j++)
            res[i] += matr[i][j] * vec[j];
    }
    end_time = omp_get_wtime();
    return end_time - start_time;
}

double Mult_Matrix_Vector_Parallel_Dynamic(int** matr, int* vec, int n, int* res, int chunk_size) {
    res = new int[n];
    double start_time, end_time;
    start_time = omp_get_wtime();

#pragma omp parallel for schedule(static,chunk_size)
    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
        for (int j = 0; j < n; j++)
            res[i] += matr[i][j] * vec[j];
    }
    end_time = omp_get_wtime();
    return end_time - start_time;
}

double Mult_Matrix_Vector_Parallel_Guided(int** matr, int* vec, int n, int* res, int chunk_size) {
    res = new int[n];
    double start_time, end_time;
    start_time = omp_get_wtime();

#pragma omp parallel for schedule(static,chunk_size)
    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
        for (int j = 0; j < n; j++)
            res[i] += matr[i][j] * vec[j];
    }
    end_time = omp_get_wtime();
    return end_time - start_time;
}

double Mult_Matrix_Vector_Parallel_Runtime(int** matr, int* vec, int n, int* res, int chunk_size) {
    res = new int[n];
    double start_time, end_time;
    start_time = omp_get_wtime();

#pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
        for (int j = 0; j < n; j++)
            res[i] += matr[i][j] * vec[j];
    }

    end_time = omp_get_wtime();
    return end_time - start_time;
}

enum option {
    NULLOPT = -1,
    STATIC = 1,
    DYNAMIC = 2,
    GUIDED = 3,
    RUNTIME = 4,
    NONPARALLEL = 5
};

double check_better_time(double& better_time, double time, option& better_option, option opt) {
    if (better_time > time)
    {
        better_time = time;
        better_option = opt;
    }
    return time;
}

void check_options(int n)
{
    int** matr = new int* [n];
    for (int i = 0; i < n; i++)
        matr[i] = new int[n];

    int* vec = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matr[i][j] = rand() % 10 - 5;
    for (int i = 0; i < n; i++)
        vec[i] = rand() % 10 - 5;

    int* res = new int[n];

    int better_opt_count[5] = { 0, 0, 0, 0, 0 }; //5 nonparallel

    for (int chunk_size = chunk_step; chunk_size < max_chunk_size; chunk_size += chunk_step)
    {
        double time_non_parallel = 0.0;
        double better_time = (double)better_time_const;
        option better_opt = NULLOPT;

        printf("\Static, time: %.4f msec\n", 1000 * check_better_time(better_time,
            Mult_Matrix_Vector_Parallel_Static(matr, vec, n, res, chunk_size), better_opt, STATIC));
        printf("\Dynamic, time: %.4f msec\n", 1000 * check_better_time(better_time,
            Mult_Matrix_Vector_Parallel_Dynamic(matr, vec, n, res, chunk_size), better_opt, DYNAMIC));
        printf("\Guided, time: %.4f msec\n", 1000 * check_better_time(better_time,
            Mult_Matrix_Vector_Parallel_Guided(matr, vec, n, res, chunk_size), better_opt, GUIDED));
        printf("\Runtime, time: %.4f msec\n", 1000 * check_better_time(better_time,
            Mult_Matrix_Vector_Parallel_Runtime(matr, vec, n, res, chunk_size), better_opt, RUNTIME));

        time_non_parallel = Mult_Matrix_Vector(matr, vec, n, res);
        printf("\Non parallel, time: %.4f msec\n", 1000 * check_better_time(better_time, time_non_parallel, better_opt, NONPARALLEL));         \


            printf("BETTER OPTION %d, BETTER TIME %.4f msec, CHUNK_SIZE = %d\n\n", better_opt, 1000 * better_time, chunk_size);

        if (better_opt != NONPARALLEL && !matrix_value_barrier_has_value)
        {
            matrix_size_barrier = n;
            matrix_value_barrier_has_value = true;
        }

        better_opt_count[better_opt - 1] ++;
    }
    printf("BETTER Options count:\nSTATIC: %d\nDYNAMIC: %d\nGUIDED: %d\nRUNTIME: %d\nNONPARALLEL: %d\n",
        better_opt_count[STATIC - 1], better_opt_count[DYNAMIC - 1], better_opt_count[GUIDED - 1], better_opt_count[RUNTIME - 1], better_opt_count[NONPARALLEL - 1]);


    printf("MATRIX SIZE: %d\n", n);
    printf("MATRIX VALUE BARRIER: %d\n", matrix_size_barrier);
    delete[]res;
    delete[]vec;
    for (int i = 0; i < n; i++)
        delete[] matr[i];
    delete[]matr;

	return;
}

int main()
{
    srand(time(0));
    omp_set_num_threads(8);

    for (int matrix_size = matrix_step; matrix_size < matrix_size_const + 1; matrix_size += matrix_step)
    { 
        check_options(matrix_size); 
    }


    return EXIT_SUCCESS;
}
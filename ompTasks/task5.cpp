#include <iostream>
#include <omp.h>

int main5()
{
	srand(time(0));
	int arr[6][8];

	for (int i = 0; i < 6; ++i)
		for (int j = 0; j < 8; ++j)
		{
			arr[i][j] = rand() % 100 + 1;
		}


#pragma omp parallel sections
	{
#pragma omp section
		{
			int sum = 0, k = 0;
			for (int i = 0; i < 6; ++i)
				for (int j = 0; j < 8; ++j)
				{
					sum += arr[i][j];
					k++;
				}
			printf("section - 1 thread id = %d, average = %.2lf\n", omp_get_thread_num(), float(sum) / k);
		}
#pragma omp section
		{
			int max = arr[0][0], min = arr[0][0];
			for (int i = 0; i < 6; ++i)
				for (int j = 0; j < 8; ++j)
				{
					if (arr[i][j] > max)
					{
						max = arr[i][j];
					}
					if (arr[i][j] < min)
					{
						min = arr[i][j];
					}
				}
			printf("section - 2 thread id = %d, min = %d, max = %d\n", omp_get_thread_num(), min, max);
		}
#pragma omp section
		{
			int count = 0;
			for (int i = 0; i < 6; ++i)
				for (int j = 0; j < 8; ++j)
				{
					if (arr[i][j] % 3 == 0)
						count++;
				}
			printf("section - 3 thread id = %d, count = %d\n", omp_get_thread_num(), count);
		}
	}

	return EXIT_SUCCESS;
}

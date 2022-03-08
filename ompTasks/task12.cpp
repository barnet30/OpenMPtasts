#include <iostream>
#include <omp.h>

const int N = 60;

int main12()
{
	int arr[N];
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		{
			arr[i] = rand() % 500 + 1;
			printf("%d ", arr[i]);
		}
		if ((i+1) % 10 == 0)
		{
			printf("\n"); 
		}
	}
	printf("\n");


	int max = arr[0];
	omp_set_num_threads(4);
#pragma omp parallel shared(max)
	{
#pragma omp parallel for 
		for (int i = 0; i < N; ++i)
		{
			if (arr[i] % 7 == 0 && max < arr[i])
#pragma omp critical
				{
					if (arr[i] % 7 == 0 && max < arr[i])
					{
						max = arr[i];
					}
				}
		}
	}

	printf("Max which multiples of 7 = %d", max);

	return EXIT_SUCCESS;
}

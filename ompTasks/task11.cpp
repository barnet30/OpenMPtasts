#include <iostream>
#include <omp.h>

const int N = 30;

int main11()
{
	int arr[N];

	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		{
			arr[i] = rand() % 90 + 10;
			printf("%d ", arr[i]);
		}
		if ((i + 1) % 5 == 0)
		{
			printf("\n");
		}
	}

	int count = 0;
#pragma omp parallel for shared(count) 
	for (int i = 0; i < N; ++i)
	{
		if (arr[i] % 9 == 0)
#pragma omp atomic
			count++;
	}
	printf("\n number of multiples of 9 = %d\n", count);


	return EXIT_SUCCESS;
}

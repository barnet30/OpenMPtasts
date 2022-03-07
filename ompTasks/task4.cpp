#include <iostream>
#include <omp.h>

int main4()
{
	srand(time(0));
	int a[10], b[10];

	for (int i = 0; i < 10; ++i)
	{
		a[i] = rand() % 100 + 1;
		b[i] = rand() % 100 + 1;
	}
	omp_set_num_threads(2);

#pragma omp parallel 
	{
		int current_thread = omp_get_thread_num();

		if (current_thread == 0)
		{
			int min = a[0];
			for (int i = 1; i < 10; ++i)
			{
				if (a[i] < min)
					min = a[i];
			}
			printf("thread id =  %d\n", current_thread);
			printf("min a = %d \n", min);
		}
		if (current_thread == 1)
		{
			int max = a[0];
			for (int i = 1; i < 10; ++i)
			{
				if (a[i] > max)
					max = a[i];
			}
			printf("thread id = %d\n", current_thread);
			printf("max b = %d \n", max);
		}
	}


    return EXIT_SUCCESS;
}

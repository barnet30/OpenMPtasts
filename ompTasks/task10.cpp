#include <iostream>
#include <omp.h>


const int n = 6;
const int m = 8;

int main10()
{
	int d[n][m];
	srand(time(NULL));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			d[i][j] = rand() % 100 + 1;
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	int min = d[0][0];
	int max = d[0][0];

#pragma omp parallel for 
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (d[i][j] > max || d[i][j] < min)
#pragma omp critical
			{
				if (d[i][j] > max) max = d[i][j];
				else if (d[i][j] < min) min = d[i][j];
			}
		}
	}
	printf("max is %d, min is %d\n", max, min);

	return EXIT_SUCCESS;
}

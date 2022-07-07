#include <stdlib.h>
#include <stdio.h>

int	main()
{
	const int ARRAY_SIZE=" ";
	long double *p = (long double *)malloc(sizeof(long double) * ARRAY_SIZE);
	if (p == NULL)
	{
		printf("Error\n");
		exit(-1);
	}
	printf("ok\n");
	return (0);
}

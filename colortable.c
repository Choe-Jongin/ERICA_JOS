#include <stdio.h>

int main()
{
	for( int i = 20 ; i < 60 ; ++i)
	{
		for( int j = 20 ; j < 60 ; ++j)
		{
			printf("#\033[%d;%dm", i, j);
		}
		printf("\n");
	}

	printf("# \033[%d;%dm",37,40);

	return 0;
}

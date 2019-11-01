#include <stdio.h>

int main()
{
	
	printf("   ");
	for( int i = 20 ; i < 60 ; ++i)
		printf("%d ",i);
	printf("\n");	
	for( int i = 20 ; i < 60 ; ++i)
	{
		printf("%d",i);
		for( int j = 20 ; j < 60 ; ++j)
		{
			printf(" # \033[%d;%dm", i, j);
		}
		
		printf("\033[%d;%dm",0,0);
		printf("\n");
	}


	printf("\033[%d;%dm",0,0);
	return 0;
}

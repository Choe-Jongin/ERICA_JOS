#include <stdio.h>

int main()
{
	int margin = 1;
	int textmin = 30-margin;
	int textmax = 37+margin;
	int backgroundmin = 40-margin;
	int backgroundmax = 48+margin;	
	printf("   ");
	for( int i = backgroundmin ; i <= backgroundmax ; ++i)
		printf("%d ",i);
	printf("\n");	
	for( int i = textmin ; i <= textmax ; ++i)
	{
		printf("%d",i);
		for( int j = backgroundmin ; j < backgroundmax ; ++j)
		{
			printf("\033[%d;%dm", i, j);
			printf(" # ");
		}
		
		printf("\033[%d;%dm",0,0);
		printf("\n");
	}


	printf("\033[%d;%dm",0,0);
	return 0;
}

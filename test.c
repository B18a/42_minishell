#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int number_is_big(int i, int *j)
{
	if(i > 0)
	{
		printf("I IS |%i|\n",i);
		(*j)--;
		return(1);
	}
	return(0);
}

int main(void)
{
	int i = 5;

	while(number_is_big(i, &i));
}
